cmake_minimum_required(VERSION 3.8.0)
cmake_policy(SET CMP0069 NEW)
project(OpenGL)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(ASSIMP_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_BLEND_IMPORTER ON CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    add_compile_options(/arch:AVX2)
elseif(CMAKE_COMPILER_IS_GNUCXX)
    if(CMAKE_BUILD_TYPE EQUAL "Debug")
        set(CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG")
        set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    endif()
endif()

file(COPY ${CMAKE_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_BINARY_DIR}/Debug)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/stb)
add_subdirectory(dependencies/assimp)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw stb glad OpenGL::GL assimp)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm")