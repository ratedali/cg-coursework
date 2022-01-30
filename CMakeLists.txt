cmake_minimum_required(VERSION 2.8)

project(OpenGL)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_C_FLAGS, "-Wall -Werror")
set(CMAKE_CXX_FLAGS, "-Wall -Werror -std=c++17")

set(OpenGL_GL_PREFERENCE,  "LEGACY")

add_library(init ${PROJECT_SOURCE_DIR}/init.cpp)

link_libraries(OpenGL GLU glut init)

add_executable(main ${PROJECT_SOURCE_DIR}/main.cpp)
add_executable(testing ${PROJECT_SOURCE_DIR}/testing/main.cpp)

add_executable(assignment1 ${PROJECT_SOURCE_DIR}/assignment1/main.cpp)

foreach(c A;B;C1;C2;C3)
    add_executable(assignment2${c} ${PROJECT_SOURCE_DIR}/assignment2/part${c}.cpp)
endforeach()

foreach(c A;B;)
    add_executable(assignment3${c} ${PROJECT_SOURCE_DIR}/assignment3/part${c}.cpp)
endforeach()
