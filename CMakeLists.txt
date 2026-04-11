cmake_minimum_required(VERSION 4.1)
project(SistemaPIM)

set(CMAKE_CXX_STANDARD 20)

add_executable(SistemaPIM main.cpp
        Equipo.cpp
        Equipo.h
        Incidencia.cpp
        Incidencia.h
        EquipoComputo.cpp
        EquipoComputo.h)
