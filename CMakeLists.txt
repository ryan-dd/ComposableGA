cmake_minimum_required (VERSION 3.21)

set(EVY_VERSION 0.1.0)

project(evy 
  VERSION ${EVY_VERSION} 
  DESCRIPTION "An evolutionary algorithm toolkit" 
  LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

if(PROJECT_IS_TOP_LEVEL) 
  set(CMAKE_CXX_STANDARD 23)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(evy INTERFACE)
add_library(evy::evy ALIAS evy)

include(GNUInstallDirs)

target_include_directories( evy
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(evy INTERFACE cxx_std_23)

find_package(Boost REQUIRED) # Requires header-only boost::pfr
target_include_directories(evy INTERFACE ${Boost_INCLUDE_DIRS})

option(EVY_BUILD_TESTS "Enable building tests." OFF)
option(EVY_BUILD_EXAMPLES "Enable building examples." OFF)
option(EVY_ENABLE_INSTALL "Enable the install target" ON)

option(EVY_USE_SANITIZERS "Enable sanitizers by adding -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined flags if available." OFF)
option(EVY_USE_STATIC_ANALYZERS "Enable static analyzers" OFF)
option(EVY_DEV_MODE "Set defaults for developing." OFF)

if(EVY_DEV_MODE)
  set(EVY_USE_SANITIZERS ON)
  set(EVY_USE_STATIC_ANALYZERS ON)
  set(EVY_BUILD_TESTS ON)
  set(EVY_BUILD_EXAMPLES ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for LSP support
endif()

if(EVY_USE_SANITIZERS)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
      target_compile_options(evy INTERFACE $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined>)
      target_link_libraries(evy INTERFACE $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined>)
  else()
    message("Sanitizers are only enabled for gcc and clang")
  endif()
endif()

if(EVY_USE_STATIC_ANALYZERS)
  set(EVY_ENABLE_CPPCHECK ON) 
  set(EVY_ENABLE_INCLUDE_WHAT_YOU_USE ON)
  include(StaticAnalyzers)
endif()

#
# Install evy
#
if(EVY_ENABLE_INSTALL)
  include(CMakePackageConfigHelpers)

  install(
      TARGETS evy
      EXPORT evyTargets
  )

  install(
      EXPORT evyTargets
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/evy
      NAMESPACE evy::
  )

  configure_package_config_file(
      ${PROJECT_SOURCE_DIR}/cmake/in/evyConfig.cmake.in
      evyConfig.cmake
      INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/evy
  )

  write_basic_package_version_file(
      ${PROJECT_BINARY_DIR}/evyConfigVersion.cmake
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion
  )

  install(
      FILES
          ${PROJECT_BINARY_DIR}/evyConfig.cmake
          ${PROJECT_BINARY_DIR}/evyConfigVersion.cmake
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/evy
  )

  install( DIRECTORY ${PROJECT_SOURCE_DIR}/src/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING 
    PATTERN "*.h"
  )
endif()

if(EVY_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
