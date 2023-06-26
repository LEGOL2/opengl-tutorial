cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME opengl-tutorial)
set(VERSION 0.1.0)
set(CMAKE_CXX_STANDARD_REQURED TRUE)
set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME} VERSION ${VERSION})

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(application)

add_subdirectory(glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glew/build/cmake)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)
add_compile_definitions(GLEW_STATIC)
target_link_libraries(${PROJECT_NAME} PRIVATE glew_s)

add_subdirectory(shaders)
