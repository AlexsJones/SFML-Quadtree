cmake_minimum_required(VERSION 2.8)
project(quads)


add_executable(quads main.cpp Object.cpp quadtree.cpp)

target_link_libraries(quads -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio GL GLU GLEW )
