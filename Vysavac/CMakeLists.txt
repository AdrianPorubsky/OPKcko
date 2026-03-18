cmake_minimum_required(VERSION 3.20)
project(RobotSimulator)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(RobotSimulator
        main.cpp
        Environment.cpp
        Lidar.cpp
        Robot.cpp
        Canvas.cpp
)

target_link_libraries(RobotSimulator ${OpenCV_LIBS})