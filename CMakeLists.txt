cmake_minimum_required(VERSION 3.27.9)
project(demon1125-optimizer VERSION 1.1.0)

find_package(Geode REQUIRED)

file(GLOB_RECURSE SRC "src/*.cpp")
setup_geode_mod(${CMAKE_PROJECT_NAME} ${SRC})
