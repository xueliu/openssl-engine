# -- Minimum required version
cmake_minimum_required (VERSION 3.14...3.22)

# -- Project name
project (openssl-engine)

# -- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
            FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# -- Various includes
include (GenerateExportHeader)
include (CMakePackageConfigHelpers)
include (GNUInstallDirs)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

CPMAddPackage(
        NAME googletest
        GITHUB_REPOSITORY google/googletest
        GIT_TAG release-1.10.0
        VERSION 1.10.0
        OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
)

# -- Required to build
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# -- Set cxx 11 standard default to achieve the compatibility with mtios
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)

# -- Get the OpenSSL's engine directory
if(OPENSSL_FOUND AND PKG_CONFIG_FOUND)
    pkg_get_variable(OPENSSL_ENGINE_DIR libcrypto enginesdir)
endif()

message(STATUS "OpenSSL Engine: " ${OPENSSL_ENGINE_DIR} )

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
if (NOT (${CMAKE_INSTALL_PREFIX} STREQUAL "/usr" ) )
    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS ON)

#add_subdirectory(oezgan)

add_subdirectory(dummy)

add_subdirectory(md5)

add_subdirectory(unit-tests)

add_subdirectory(examples)

add_subdirectory(sha256)
