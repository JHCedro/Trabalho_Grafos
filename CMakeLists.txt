cmake_minimum_required(VERSION 3.6)
project(grafo_lista_adjacencia)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    include/Grafo/Arco.h
    include/Grafo/Auxiliares.h
    include/Grafo/Dijkstra.h
    include/Grafo/Grafo.h
    include/Grafo/GrafoHash.h
    include/Grafo/GrafoLista.h
    include/Grafo/Hashing.h
    include/Grafo/Lista.h
    include/Grafo/MenuTrabalho.h
    include/Grafo/No.h
    include/Grafo/NoHash.h
    include/Grafo/NoLista.h
    include/Grafo/Testes.h
    include/Auxiliares.hpp
    include/Circulo.h
    src/Grafo/Arco.cpp
    src/Grafo/Grafo.cpp
    src/Grafo/GrafoHash.cpp
    src/Grafo/GrafoLista.cpp
    #    src/Grafo/main.cpp
    src/Grafo/MenuTrabalho.cpp
    src/Grafo/No.cpp
    src/Grafo/NoHash.cpp
    src/Grafo/NoLista.cpp
    src/main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(include include/Grafo ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

add_executable(grafo_lista_adjacencia ${SOURCE_FILES})
target_link_libraries(grafo_lista_adjacencia ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})