cmake_minimum_required(VERSION 3.21)
project(cvAssignment)

set(CMAKE_CXX_STANDARD 20)
set(OpenCV_DIR PATH D:/opencv/build/x64/vc15/bin)
include_directories( D:/opencv/build/include  D:/opencv/build/include/opencv2 )
add_executable(cvAssignment main.cpp histogram.cpp writer.cpp geometry.cpp   Hough.cpp HoughP.cpp
      edgeGeo.cpp  contour.cpp absProc.cpp genProc.cpp imageOps.cpp sequence.cpp results.cpp )
target_link_libraries( cvAssignment D:/opencv/build/x64/vc15/lib/opencv_world454.lib )
