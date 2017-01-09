cmake_minimum_required(VERSION 3.6)
project(grafo_lista_adjacencia)

#find_package(OpenGL REQUIRED)
#find_package(GLUT)
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-unused-function -fexceptions")
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(SOURCE_FILES
        include/zlib/crc32.h
        include/zlib/crypt.h
        include/zlib/deflate.h
        include/zlib/infback9.h
        include/zlib/inffast.h
        include/zlib/inffix9.h
        include/zlib/inffixed.h
        include/zlib/inflate.h
        include/zlib/inflate9.h
        include/zlib/inftree9.h
        include/zlib/inftrees.h
        include/zlib/ioapi.h
        include/zlib/iowin32.h
        include/zlib/trees.h
        include/zlib/unzip.h
        include/zlib/zconf.h
        include/zlib/zconf.in.h
        include/zlib/zip.h
        include/zlib/zlib.h
        include/zlib/zutil.h
        src/Grafo/Arco.cpp
        src/Grafo/Arco.h
        src/Grafo/AuxTestes.hpp
        src/Grafo/Dijkstra.h
        src/Grafo/Grafo.cpp
        src/Grafo/Grafo.h
        src/Grafo/No.cpp
        src/Grafo/No.h
        src/Auxiliares.hpp
        src/Circulo.h
        src/main.cpp)

link_directories(lib)
set(LIBRARIES
        freeglut.a
        glew32.a
        glew32.dll.a
        glui32.a
        glui_linux.a
        png.a
        opengl32.a
        png12_linux32.a
        png12_linux64.a
        z.a)

set(GLUT_INCLUDE
        include/GL/freeglut.h
        include/GL/freeglut_ext.h
        include/GL/freeglut_std.h
        include/GL/glew.h
        include/GL/glui.h
        include/GL/glui_old.h
        include/GL/glut.h
        include/GL/glutf90.h)

#set(GL_INCLUDE
#        include/GL/freeglut.h
#        include/GL/freeglut_ext.h
#        include/GL/freeglut_std.h
#        include/GL/glew.h
#        include/GL/glui.h
#        include/GL/glui_old.h
#        include/GL/glut.h
#        include/GL/glutf90.h)

include_directories(include)

add_executable(grafo_lista_adjacencia ${SOURCE_FILES} ${GLUT_INCLUDE})
target_link_libraries(grafo_lista_adjacencia ${LIBRARIES})
