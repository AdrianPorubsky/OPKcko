cmake_minimum_required(VERSION 3.14)
project(untitled)
find_package(OpenCV REQUIRED)


set(CMAKE_CXX_STANDARD 20)

add_executable(untitled
        cv2.cpp
        shapes.cpp
        mainik.cpp
    )
target_link_libraries(untitled ${OpenCV_LIBS})
