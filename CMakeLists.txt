# Fix behavior of CMAKE_C_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()
# Fix FindDoxygen.
if (POLICY CMP0069)
  cmake_policy(SET CMP0069 NEW)
endif ()

cmake_minimum_required (VERSION 3.9.0)
project (skt LANGUAGES C)

set (SKT_DEBUG_LEVEL "0" CACHE STRING "SKT debug level")

add_definitions (-DDEBUG=${SKT_DEBUG_LEVEL})
if (MSVC)
  add_definitions (-D_CRT_SECURE_NO_WARNINGS=1)
endif (MSVC)

add_executable (skt skt.c buf.c)
add_executable (skt.orig skt.orig.c)

if (MSVC)
  target_compile_options (skt PRIVATE /W4 /WX)
else (MSVC)
  target_compile_options (skt PRIVATE -Wall -Wextra -pedantic)
  target_compile_options (skt PRIVATE -Wno-misleading-indentation -Wno-implicit-fallthrough)
endif (MSVC)

set_property (TARGET skt PROPERTY C_STANDARD 99)
set_property (TARGET skt.orig PROPERTY C_STANDARD 99)

# Optional IPO. Do not use IPO if it's not supported by compiler.
include (CheckIPOSupported)
check_ipo_supported (RESULT ipo_result)
if (ipo_result)
  set_property (TARGET skt PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()
