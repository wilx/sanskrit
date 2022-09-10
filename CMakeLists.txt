cmake_minimum_required (VERSION 2.8.12)
project (skt)
set (skt_version "2.2.3")

set (SKT_DEBUG_LEVEL "0" CACHE STRING "SKT debug level")

add_definitions (-DDEBUG=${SKT_DEBUG_LEVEL})
if (MSVC)
  add_definitions (-D_CRT_SECURE_NO_WARNINGS=1)
endif (MSVC)

if (APPLE)
  add_executable(skt MACOSX_BUNDLE skt.c)
  set_target_properties(skt PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_BUNDLE_NAME skt
    MACOSX_BUNDLE_BUNDLE_VERSION "${skt_version}"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${skt_version}"
  )
else (APPLE)
  add_executable(skt skt.c)
endif (APPLE)
set_target_properties(skt PROPERTIES
  VERSION "${skt_version}"
)

enable_testing()
add_test(NAME "skt"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/skt" "${CMAKE_CURRENT_SOURCE_DIR}/sktdoc.skt" "${CMAKE_CURRENT_BINARY_DIR}/sktdoc.tex")
