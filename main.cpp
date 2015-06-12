#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking/tracker.hpp>

#include <boost/timer.hpp>

#define EVER (;;)
#define VERBOSE true

void readme();
void mouseClickCallback(int event, int x, int y, int flags, void* userdata);
void setCalibration();
void undistortImage(const cv::Mat& _image, cv::Mat& _undistortedImage, int _lr);

int main(int argc, char** argv)
{
    if(argc <= 1)
    {
        std::cout<< " --(!) Error reading files " << std::endl;
        readme();

        return -1;
    }

    cv::VideoCapture cap(argv[1]); // open the video file

    if (!cap.isOpened())
    {
        readme();
        return -1;
    }

    cap.set(CV_CAP_PROP_POS_MSEC, 2*1000);

    cv::Mat frame;
    cv::Rect2d *rect(new cv::Rect2d);

    cv::Ptr<cv::TrackerTLD> tracker = cv::TrackerTLD::createTracker();

    // do once
    cap >> frame; // get a new frame from camera

    cv::VideoWriter writer("./out.avi",                // output file name
                           CV_FOURCC('M','J','P','G'), // output codec
                           15.0,                       // fps
                           cv::Size(frame.cols, frame.rows));

    cv::imshow("Draw Rect", frame);
    cv::setMouseCallback("Draw Rect", mouseClickCallback,
                         reinterpret_cast<void*>(rect));
                         //0);

    cv::waitKey();

    if (rect->area() == 0.0)
        return -1;

    tracker->init(frame, *rect);

    double fps = 1.0;

    for EVER
    {
        boost::timer t;

        cap >> frame;

        if (frame.empty() ) // repeat video file
        {
            break;
            //cap.set(CV_CAP_PROP_POS_AVI_RATIO, 0);
            //continue;
        }

        // tld tracker here
        if (tracker->update(frame, *rect))
            cv::rectangle(frame, *rect, cv::Scalar(255, 0, 0 ), 2, 1);

        fps = 1.0/t.elapsed();
        std::string fps_s(std::to_string(fps));
        fps_s.erase(4);
        fps_s.append(" fps");

        cv::putText(frame, fps_s.c_str(),
                    cv::Point2f(5,frame.rows-5),
                    cv::FONT_HERSHEY_PLAIN, 1.5,  cv::Scalar(0,0,255,255));

        cv::imshow("TrackerTLD", frame);

        if (writer.isOpened())
            writer.write(frame);

        char c = cv::waitKey(10);
        if (27 == c) // returns -1 when no key is pressed
            break;
    }

    writer.release();
    cap.release();

    return 0;
}

/** @function readme */
void readme()
{
    std::cout << " Usage: ./tld_tracker <video file>" << std::endl;
}

void mouseClickCallback(int event, int x, int y, int flags, void* userdata)
{
    cv::Rect2d * p =
            reinterpret_cast<cv::Rect2d*>(userdata);

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        std::cout << "Left button down - position (" << x << ", " << y << ")" << std::endl;
        p->x = x;
        p->y = y;
    }
    else if (event == cv::EVENT_LBUTTONUP)
    {
        std::cout << "Left button up   - position (" << x << ", " << y << ")" << std::endl;
        p->width =  std::abs(x - p->x);
        p->height = std::abs(y - p->y);
        cv::destroyWindow("Draw Rect");
    }
}
