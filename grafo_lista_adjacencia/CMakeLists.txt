cmake_minimum_required(VERSION 3.6)
project(grafo_lista_adjacencia)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    include/Arco.h
    include/Auxiliares.h
    include/Dijkstra.h
    include/Grafo.h
    include/GrafoHash.h
    include/GrafoLista.h
    include/Hashing.h
    include/Lista.h
    include/MenuTrabalho.h
    include/No.h
    include/NoHash.h
    include/NoLista.h
    src/Arco.cpp
    src/Grafo.cpp
    src/GrafoHash.cpp
    src/GrafoLista.cpp
    src/main.cpp
    src/MenuTrabalho.cpp
    src/No.cpp
    src/NoHash.cpp
    src/NoLista.cpp)

add_executable(grafo_lista_adjacencia ${SOURCE_FILES})