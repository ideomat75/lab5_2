cmake_minimum_required(VERSION 3.0)

project(banking)

add_library(${PROJECT_NAME} STATIC Account.cpp Transaction.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE "--coverage")
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD 17 CMAKE_CXX_STANDARD_REQUIRED ON CMAKE_BUILD_TYPE Release)
