cmake_minimum_required(VERSION 3.15)

project(tests LANGUAGES CXX VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ../event/src
    ../net/src
    ../util/src
    ../app/src
    ../rtmp/src
)

file(GLOB tests RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

foreach(mainfile IN LISTS tests)
    get_filename_component(testname ${mainfile} NAME_WE)
    add_executable(${testname} ${mainfile} ${SRC})
    target_link_libraries(${testname}
        sub::event
        sub::net
        sub::util
        sub::app
        sub::rtmp
    )
endforeach()