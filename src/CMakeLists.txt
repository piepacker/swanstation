add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(scmversion)

if(BUILD_TESTS)
  add_subdirectory(common-tests)
endif()

if(BUILD_UPDATER)
  add_subdirectory(updater)
endif()

add_subdirectory(frontend-common)

if(BUILD_NOGUI_FRONTEND)
  add_subdirectory(duckstation-nogui)
endif()

if(BUILD_QT_FRONTEND)
  add_subdirectory(duckstation-qt)
endif()

if(BUILD_LIBRETRO_CORE)
  add_subdirectory(duckstation-libretro)
endif()

