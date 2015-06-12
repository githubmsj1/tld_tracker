cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(tld_tracker)

find_package(Boost 1.5 REQUIRED)
#find_package(Eigen3 REQUIRED)

# OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# OpenCV
find_package(OpenCV 3.0 REQUIRED
             NO_DEFAULT_PATH
             PATHS "/opt/opencv3"
             #PATHS "/opt/OpenCV_2.4.5_build"
             )
include_directories(${OpenCV_INCLUDE_DIRS})
MESSAGE("OpenCV_LIBS = ${OpenCV_LIBS}")
#MESSAGE("OpenCV_INCLUDES = ${OpenCV_INCLUDE_DIRS}")
MESSAGE("OpenCV_INSTALL_PATH = ${OpenCV_INSTALL_PATH}")
MESSAGE("OpenCV_VERSION = ${OpenCV_VERSION}")

set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE "Release")

add_definitions(-std=c++11
                "-Wall" # enable all warnings
)

set(tld_tracker_sources main.cpp tld_tracker.cpp)
set(tld_tracker_headers tld_tracker.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${tld_tracker_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

add_executable(tld_tracker ${tld_tracker_sources} ${tld_tracker_headers})

target_link_libraries(tld_tracker ${OpenCV_LIBS} ${Boost_LIBRARIES})
