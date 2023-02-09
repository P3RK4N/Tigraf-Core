cmake_minimum_required(VERSION 3.25)

add_library(glad)

#Adding includes to this target and main target
target_include_directories(glad PUBLIC include)

#Adding all files in folder to project
file(GLOB_RECURSE sources *.cpp *.c *.h *.hpp)
target_sources(glad PRIVATE "${sources}")
