cmake_minimum_required(VERSION 3.16)

project(BoidsLearning)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(BoidsLearning

    src/main.cpp
    src/Boid.cpp
    src/Vector2.cpp

)

target_include_directories(BoidsLearning

    PRIVATE

    include

)

target_link_libraries(BoidsLearning

    sfml-graphics
    sfml-window
    sfml-system

)