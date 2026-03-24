cmake_minimum_required(VERSION 3.20)
project(Shooter)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

file(GLOB SOURCES "src/*.cpp")

add_executable(game ${SOURCES})

target_include_directories(game PRIVATE ${RAYLIB_INCLUDE_DIRS})
target_link_directories(game PRIVATE ${RAYLIB_LIBRARY_DIRS})
target_link_libraries(game ${RAYLIB_LIBRARIES})

if(APPLE)
    target_link_libraries(game
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
endif()