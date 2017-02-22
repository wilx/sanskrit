cmake_minimum_required (VERSION 2.8.4)
project (skt)

set (SKT_DEBUG_LEVEL "0" CACHE STRING "SKT debug level")

add_definitions (-DDEBUG=${SKT_DEBUG_LEVEL})
if (MSVC)
  add_definitions (-D_CRT_SECURE_NO_WARNINGS=1)
endif (MSVC)

add_executable(skt skt.c)
