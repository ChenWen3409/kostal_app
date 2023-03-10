cmake_minimum_required(VERSION 3.5)

# ===================================================================
# PROJECT SETUP
# ===================================================================
project(flexiv_app_guis)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
# C++14 required
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===================================================================
# PROJECT OPTIONS FOR APP
# ===================================================================
option(BUILD_APP_KOSTAL_QT_GUI "Build kostal GUI app" OFF)
option(BUILD_APP_EXAMPLE_RDK_CLIENT "Build example rdk client app" OFF)
option(BUILD_APP_KOSTAL_RDK_CLIENT "Build kostal rdk client app" OFF)

# set default build type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

# exclude Anaconda directories from search
if(DEFINED ENV{CONDA_PREFIX})
  set(h5_ignore_path
    $ENV{CONDA_PREFIX}/bin $ENV{CONDA_PREFIX}/lib $ENV{CONDA_PREFIX}/include
    $ENV{CONDA_PREFIX}/Library/bin $ENV{CONDA_PREFIX}/Library/lib $ENV{CONDA_PREFIX}/Library/include
  )
  list(APPEND CMAKE_IGNORE_PATH ${h5_ignore_path})
endif()

# ===================================================================
# PROJECT CONFIG
# ===================================================================
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tools/set_default_build_type.cmake)
set_default_build_type()

# create a header file that defines the library version and git version
# this will replace @varable@ with the cmake value ${variable}
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tools/FlexivGitVersion.cmake)
FlexivGitVersion()

set(flexiv_app_guis_resources_path ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# this will replace @varable@ with the cmake value ${variable}
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/flexiv/app_guis/config.h"
)

# ===================================================================
# PROJECT DEPENDENCIES
# ===================================================================
# set flexiv_thirdparty2 directory
set(flexiv_thirdparty2_path "" CACHE PATH "flexiv_thirdparty2 path")

if(NOT EXISTS "${flexiv_thirdparty2_path}")
    message(FATAL_ERROR "flexiv_thirdparty2_path=${flexiv_thirdparty2_path} does not exist.")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FvrUseFlexivThirdParty2.cmake)
FvrUseFlexivThirdParty2()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# flexiv dependencies
if(NOT TARGET flexiv::flexiv_middleware2)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flexiv_middleware2)
endif()

# ===================================================================
# PROJECT LIBRARIES
# ===================================================================
# Create an INTERFACE library with no source file to compile
add_library(${PROJECT_NAME} INTERFACE)

# Create an alias of the library using flexiv namespace,
# to imitate the install target which uses flexiv namespace.
add_library(flexiv::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} INTERFACE
    flexiv::flexiv_middleware2
    Qt5::Widgets
)

# ===================================================================
# PROJECT APPS
# ===================================================================
# Add all app-level CMake projects as subdirectories,
if(${BUILD_APP_KOSTAL_QT_GUI})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/app/kostal_qt_gui)
endif()

if(${BUILD_APP_EXAMPLE_RDK_CLIENT})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/app/example_rdk_client)
endif()

if(${BUILD_APP_KOSTAL_RDK_CLIENT})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/app/kostal_rdk_client)
endif()
