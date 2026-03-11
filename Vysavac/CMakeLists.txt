cmake_minimum_required(VERSION 3.20)
project(RobotSimulator)

set(CMAKE_CXX_STANDARD 17)

# Nájdenie OpenCV [cite: 15, 16]
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Pridanie všetkých potrebných súborov [cite: 87]
add_executable(RobotSimulator
        main.cpp
        Environment.cpp
)

# Prepojenie s knižnicou OpenCV [cite: 15]
target_link_libraries(RobotSimulator ${OpenCV_LIBS})