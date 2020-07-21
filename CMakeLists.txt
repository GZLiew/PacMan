cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Minecraft
  LANGUAGES CXX
)

# ---- Create standalone executable ----
include_directories(include)
file(GLOB_RECURSE SOURCES source/*.cpp)
add_executable(minecraft ${SOURCES})

# --- Import tools ----

include(cmake/tools.cmake)

# ---- Dependencies ----

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME Minecraft
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
)

CPMAddPackage(
  NAME SDL2
  VERSION 2.0.12
  URL https://libsdl.org/release/SDL2-2.0.12.zip
)

# ---- Add libraries ----
set_target_properties(minecraft PROPERTIES 
  CXX_STANDARD 17 
  OUTPUT_NAME "minecraft"
)

target_link_libraries(minecraft SDL2)
