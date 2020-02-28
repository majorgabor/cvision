cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_LIBRARY(LibsModule 
    calibration.cpp
)

project( calibration )
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( calibration main.cpp )

target_link_libraries( LibsModule ${OpenCV_LIBS})
target_link_libraries( calibration LibsModule)
target_link_libraries( calibration stdc++fs)