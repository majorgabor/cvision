cmake_minimum_required(VERSION 3.10.2)

project( filtering )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( smoothing smoothing.cpp )
add_executable( saltpepper salt_pepper.cpp )
add_executable( gaussianpyramid gaussian_pyramid.cpp )
add_executable( threshold threshold.cpp )
add_executable( colorfilter color_filter.cpp )
add_executable( queen queen.cpp )

target_link_libraries( smoothing ${OpenCV_LIBS})
target_link_libraries( saltpepper ${OpenCV_LIBS})
target_link_libraries( gaussianpyramid ${OpenCV_LIBS})
target_link_libraries( threshold ${OpenCV_LIBS})
target_link_libraries( colorfilter ${OpenCV_LIBS})
target_link_libraries( queen ${OpenCV_LIBS})