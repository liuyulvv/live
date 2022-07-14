cmake_minimum_required(VERSION 3.15)

project(app LANGUAGES CXX VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} ${SRC})
add_library(sub::app ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
    ../net/src
    ../event/src
    ../util/src
)
target_link_libraries(${PROJECT_NAME}
    sub::event
    sub::net
    sub::util
)