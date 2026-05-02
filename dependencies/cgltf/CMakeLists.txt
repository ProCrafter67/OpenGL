cmake_minimum_required(VERSION 3.10.0)
project(cgltf)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(cgltf)
target_sources(cgltf PRIVATE ${SRCS})
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")