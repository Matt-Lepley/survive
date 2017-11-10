cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_BUILD_TYPE Debug)

project("Survive")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Survive_SOURCE_DIR}/cmake/")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
src/player.cpp
src/survive.cpp
src/game.cpp
src/graphics.cpp
src/bullet.cpp
)

include_directories(
${SDL2_INCLUDE_DIRS}
${SDL2IMAGE_INCLUDE_DIR}
${SDL2TTF_INCLUDE_DIR}
headers
)
add_executable(survive ${SOURCES})


target_link_libraries(
survive
${SDL2_LIBRARIES}
${SDL2IMAGE_LIBRARIES}
${SDL2TTF_LIBRARIES}
)
