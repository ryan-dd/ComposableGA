cmake_minimum_required (VERSION 3.21)

set(EVVY_VERSION 0.1.0)

project(evvy 
  VERSION ${EVVY_VERSION} 
  DESCRIPTION "An evolutionary algorithm toolkit" 
  LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

if(PROJECT_IS_TOP_LEVEL) 
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(evvy INTERFACE)
add_library(evvy::evvy ALIAS evvy)

include(GNUInstallDirs)

target_include_directories( evvy
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(evvy INTERFACE cxx_std_20)

find_package(Boost REQUIRED) # Requires header-only boost::pfr
target_include_directories(evvy INTERFACE ${Boost_INCLUDE_DIRS})

option(EVVY_ENABLE_INSTALL   "Enable the install target" ON)
option(EVVY_USE_SANITIZERS "Enable sanitizers by adding -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined flags if available." OFF)
option(EVVY_USE_STATIC_ANALYZERS "Enable static analyzers" OFF)
option(ENTT_BUILD_TESTS "Enable building tests." OFF)
option(EVVY_BUILD_EXAMPLES "Enable building tests." OFF)
option(EVVY_DEV_MODE "Set defaults for developing." OFF)

if(EVVY_DEV_MODE)
  set(EVVY_USE_SANITIZERS ON)
  set(EVVY_USE_STATIC_ANALYZERS ON)
  set(EVVY_BUILD_TESTS ON)
  set(EVVY_BUILD_EXAMPLES ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for LSP support
endif()

if(EVVY_USE_SANITIZERS)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
      target_compile_options(evvy INTERFACE $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined>)
      target_link_libraries(evvy INTERFACE $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined>)
  else()
    message("Sanitizers are only enabled for gcc and clang")
  endif()
endif()

if(EVVY_USE_STATIC_ANALYZERS)
  set(EVVY_ENABLE_CPPCHECK ON) 
  set(EVVY_ENABLE_INCLUDE_WHAT_YOU_USE ON)
  include(StaticAnalyzers)
endif()

#
# Install evvy
#
if(EVVY_ENABLE_INSTALL)
  include(CMakePackageConfigHelpers)

  install(
      TARGETS evvy
      EXPORT evvyTargets
  )

  install(
      EXPORT evvyTargets
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/evvy
      NAMESPACE evvy::
  )

  configure_package_config_file(
      ${PROJECT_SOURCE_DIR}/cmake/in/evvyConfig.cmake.in
      evvyConfig.cmake
      INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/evvy
  )

  write_basic_package_version_file(
      ${PROJECT_BINARY_DIR}/evvyConfigVersion.cmake
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion
  )

  install(
      FILES
          ${PROJECT_BINARY_DIR}/evvyConfig.cmake
          ${PROJECT_BINARY_DIR}/evvyConfigVersion.cmake
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/evvy
  )

  install( DIRECTORY ${PROJECT_SOURCE_DIR}/src/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING 
    PATTERN "*.h"
  )
endif()

if(EVVY_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
