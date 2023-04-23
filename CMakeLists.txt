cmake_minimum_required(VERSION 3.25)
project(Requestor)

# Build
set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} INTERFACE)

message(STATUS ${${PROJECT_NAME}_SOURCE_DIR})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_include_directories(
        ${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)