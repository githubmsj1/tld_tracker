# tld_tracker

Playing around with the new tracker API from OpenCV 3.0 contrib.

https://github.com/Itseez/opencv_contrib

http://docs.opencv.org/3.0-beta/modules/tracking/doc/tracking.html

|            | Genauigkeit | Geschwindigkeit | Verdeckung | Verlassen |
|------------|-------------|-----------------|------------|-----------|
| Boosting   | +           | +               | +          | --        |
| MedianFlow | +           | ++              | -          | o         |
| MIL        | ++          | o               | +          | --        |
| TLD        | --          | --              | ?          | ?         |
