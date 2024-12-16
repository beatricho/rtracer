# Versione minima di CMake richiesta
cmake_minimum_required(VERSION 3.10)

# Nome del progetto e linguaggio
project(rtracer LANGUAGES C)

# Aggiungi flag del compilatore
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fcommon")

# Aggiungi i file di intestazione al progetto
set(HEADERS
    ray.h
    vec3.h
    utils.h
)

# Aggiungi i file sorgente al progetto
set(SOURCES
    main.c
    utils.c
    vec3.c
    ray.c
)

# Definisci l'eseguibile da costruire
add_executable(rtracer ${SOURCES} ${HEADERS})