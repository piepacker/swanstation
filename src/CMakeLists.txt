if(BUILD_LIBRETRO_CORE)
  add_definitions("-DLIBRETRO=1")
endif()

add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(scmversion)
add_subdirectory(frontend-common)

if(NOT BUILD_LIBRETRO_CORE AND NOT ANDROID)
  add_subdirectory(common-tests)
  if(WIN32)
    add_subdirectory(updater)
  endif()
endif()

if(BUILD_NOGUI_FRONTEND)
  add_subdirectory(duckstation-nogui)
endif()

if(BUILD_QT_FRONTEND)
  add_subdirectory(duckstation-qt)
endif()

if(BUILD_LIBRETRO_CORE)
  add_subdirectory(duckstation-libretro)
endif()

if(BUILD_REGTEST)
  add_subdirectory(duckstation-regtest)
endif()

# HLE BIOS HACKING
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    add_definitions(/FI"fi-platform-defines.h" /FI"fi-printf-redirect.h")
else()
    add_definitions(-include fi-platform-defines.h -include fi-printf-redirect.h)
endif()
