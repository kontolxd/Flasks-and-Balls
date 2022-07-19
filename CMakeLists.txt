cmake_minimum_required(VERSION 3.5)

project(ballsandflasks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ballsandflasks main.cpp
flask.h flask.cpp)

target_link_libraries(ballsandflasks sfml-graphics sfml-window sfml-system sfml-audio)

FILE(COPY flask.png DESTINATION "${CMAKE_BINARY_DIR}")
