cmake_minimum_required(VERSION 3.5)
project(Practice)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp field.cpp field.h yinyen.h yinyen.cpp)
add_executable(Practice ${SOURCE_FILES})
target_link_libraries(Practice -lsfml-graphics -lsfml-window -lsfml-system -lglut)