cmake_minimum_required (VERSION 3.1)
project (skt)
enable_language (CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (SKT_DEBUG_LEVEL "0" CACHE STRING "SKT debug level")

add_definitions (-DDEBUG=${SKT_DEBUG_LEVEL})
if (MSVC)
  add_definitions (-D_CRT_SECURE_NO_WARNINGS=1)
endif (MSVC)

add_executable(skt skt.cxx)
