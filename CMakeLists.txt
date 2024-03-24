cmake_minimum_required(VERSION 3.21)

set(PROJECT_NAME SDL2Tests)
set(PROJECT_DESCRIPTION "SDL2 tests")
set(CMAKE_CXX_STANDARD 23)

project(${PROJECT_NAME} DESCRIPTION ${PROJECT_DESCRIPTION})

file(
    GLOB_RECURSE
    SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/core/source/*.c
    ${CMAKE_CURRENT_LIST_DIR}/core/source/*.cpp
)

file(
    GLOB_RECURSE
    THIRD_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.c
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.cpp
)

file(
    GLOB_RECURSE
    HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/core/header/*.h
    ${CMAKE_CURRENT_LIST_DIR}/core/header/*.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/header/*.inl
)

file(
    GLOB_RECURSE
    THIRD_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.h
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.hpp
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.inl
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/core/header)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third/imgui/header)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
    ${THIRD_SOURCES}
    ${THIRD_HEADERS}
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image)