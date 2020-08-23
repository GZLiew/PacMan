cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

# Note: update this to your new project's name and version
project(PacMan 
  VERSION 1.0
  LANGUAGES C CXX
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
  NAME glm
  GITHUB_REPOSITORY g-truc/glm
  VERSION 0.9.9.8
  GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
)

CPMAddPackage(
  NAME SDL2
  VERSION 2.0.12
  URL https://libsdl.org/release/SDL2-2.0.12.zip
)
if (SDL2_ADDED)
  add_library(SDL2::SDL2 ALIAS SDL2)
endif()

CPMAddPackage(
  NAME freetype
  GIT_REPOSITORY https://github.com/aseprite/freetype2.git
  GIT_TAG VER-2-10-0
  VERSION 2.10.0
)
if (freetype_ADDED)
  add_library(Freetype::Freetype ALIAS freetype)
endif()


CPMAddPackage(
  NAME SDL2_ttf
  VERSION 2.0.15
  URL https://libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.zip
)

#if(openal_ADDED)
  #set_target_properties(openal PROPERTIES COMPILE_OPTIONS "-fpermissive")
#endif()

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

target_include_directories(PacMan PUBLIC ${SDL2_ttf_SOURCE_DIR})
target_include_directories(PacMan PUBLIC ${SDL2_SOURCE_DIR}/include)
target_include_directories(PacMan PUBLIC ${openal_SOURCE_DIR}/include)
target_include_directories(PacMan PUBLIC ${glm_SOURCE_DIR})

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