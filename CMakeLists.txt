cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

# Note: update this to your new project's name and version
project(PacMan 
  VERSION 1.0
  LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.3
)

CPMAddPackage(
  NAME SDL2
  VERSION 2.0.12
  URL https://libsdl.org/release/SDL2-2.0.12.zip
)

# ---- Add source files ----
FILE(GLOB headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.h)
FILE(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/source/**/*.cpp)

add_library(PacMan ${headers} ${sources})

set_target_properties(PacMan PROPERTIES CXX_STANDARD 17)

target_compile_options(PacMan PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

target_include_directories(PacMan
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

target_include_directories(PacMan PRIVATE ${SDL2_SOURCE_DIR}/include)

# ---- Create an installable target ----
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  DEPENDENCIES ""
)