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

project(Nyx LANGUAGES CXX)

enable_testing()

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
# Compiler options
# -----------------------------------------------------------------------------
# General setup for all compilers (GCC, Clang, MSVC)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /permissive-")  # Set warnings for MSVC
    message(STATUS "Configuring for MSVC")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    message(STATUS "Configuring for GCC/CLANG")
endif()

# Debug Mode (For Clang/GCC and MSVC)
set(CMAKE_BUILD_TYPE Debug)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug")
    
    if(MSVC)
        # MSVC-specific debug flags
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /D_DEBUG /DDEBUG /EHsc")
        set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
    else()
        # Clang/GCC debug flags
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0 -D_DEBUG -DDEBUG -fno-omit-frame-pointer -D_GLIBCXX_DEBUG")
        set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g3")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")  # Debugging symbols
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG -DDEBUG -fno-omit-frame-pointer")  # Increase debug info
    endif()
endif()

# Release Mode (For Clang/GCC and MSVC)
set(CMAKE_BUILD_TYPE Release)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release")
    
    if(MSVC)
        # MSVC-specific release flags
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG /MT /EHsc /GL")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    else()
        # Clang/GCC release flags
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -fno-rtti -fno-exceptions -flto -funroll-loops")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -fno-exceptions -fno-rtti -flto -funroll-loops")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")  # Remove debugging code
    endif()
endif()

# -----------------------------------------------------------------------------
# Set up Installation Directories
# -----------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Set output directories for library and executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # Static libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # Shared libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # Executables

option(BUILD_TEST "Enable building the test suite" OFF)
option(NYX_LOCAL_BUILD "Enable native flags" OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(source)
add_subdirectory(test)


if(NOT NYX_DEPLOY)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native")
endif()

# Install executable
install(TARGETS math
    RUNTIME DESTINATION bin        # For executables
    LIBRARY DESTINATION lib        # For shared libraries (.so, .dylib)
    ARCHIVE DESTINATION lib        # For static libraries (.a)
)

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Optionally install documentation, licenses, etc.
install(FILES README.md LICENSE DESTINATION .)

set(CMAKE_INSTALL_PREFIX install)