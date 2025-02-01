cmake_minimum_required(VERSION 3.8)

# Prevent in-source builds (stay out of the source directory)
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} AND NOT DEFINED WITH_IN_SOURCE_BUILD)
  message(FATAL_ERROR
      "CMake generation for Nyx is not allowed within the source directory!"
    "\nRemove the CMakeCache.txt and CMakeFiles directories and build out-of-source."
    "\nExample:"
    "\n mkdir build && cd build && cmake .."
  )
endif()

project(Nyx LANGUAGES CXX CUDA)

enable_testing()

# Set default CMake build type if not defined
if(NOT DEFINED CMAKE_BUILD_TYPE_INIT)
  set(CMAKE_BUILD_TYPE_INIT "Release")
endif()
mark_as_advanced(CMAKE_BUILD_TYPE_INIT)

# Set compile definitions based on the build configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:Debug>:NYX_DEBUG>
)

# -----------------------------------------------------------------------------
# Set Platform-Specific Defines
# -----------------------------------------------------------------------------
if(WIN32)
    add_definitions(-DNYX_PLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DNYX_PLATFORM_MACOS)
elseif(UNIX)
    add_definitions(-DNYX_PLATFORM_LINUX)
endif()

# -----------------------------------------------------------------------------
# Set up Installation Directories
# -----------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(source)
add_subdirectory(examples)
