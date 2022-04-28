cmake_minimum_required(VERSION 3.0)

project(lib_test)

add_subdirectory(banking bank)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest gtest)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp )

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/banking)

target_link_libraries(${PROJECT_NAME} PRIVATE banking --coverage)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE gmock)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
