cmake_minimum_required(VERSION 3.15)

project(live VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(event)
add_subdirectory(net)
add_subdirectory(util)
add_subdirectory(test)
add_subdirectory(app)