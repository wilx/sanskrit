cmake_minimum_required (VERSION 2.8.12)
project (skt)
set (skt_version "2.2.3")

set (SKT_DEBUG_LEVEL "0" CACHE STRING "SKT debug level")

add_definitions (-DDEBUG=${SKT_DEBUG_LEVEL})
if (MSVC)
  add_definitions (-D_CRT_SECURE_NO_WARNINGS=1)
endif (MSVC)

add_executable(skt skt.c)
set_target_properties(skt PROPERTIES
  VERSION "${skt_version}"
)

enable_testing()
add_test(NAME "skt"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/skt" "${CMAKE_CURRENT_SOURCE_DIR}/sktdoc.skt" "${CMAKE_CURRENT_BINARY_DIR}/sktdoc.tex")
