cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SpaceInvaders)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} include)

file(GLOB_RECURSE sources src/*.cpp)
add_executable(SpaceInvaders ${sources})

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
string(STRIP ${SDL2_IMAGE_LIBRARIES} SDL2_IMAGE_LIBRARIES)
target_link_libraries(SpaceInvaders ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})