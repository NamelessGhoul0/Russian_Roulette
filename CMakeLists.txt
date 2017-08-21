cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(Russian_Roulette)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "RR")
set(VITA_TITLEID  "ROULETTE0")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Isrc/Nogg -Isrc/Media")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

include_directories(
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(Russian_Roulette
  src/main.c
  src/audio.cpp
)

target_link_libraries(Russian_Roulette
  vita2d
  SceDisplay_stub
  SceGxm_stub
  SceSysmodule_stub
  SceCtrl_stub
  SceAudio_stub
  ScePgf_stub
  SceCommonDialog_stub
  soloud
  pthread
  freetype
  png
  z
  m
)

vita_create_self(Russian_Roulette.self Russian_Roulette)
vita_create_vpk(Russian_Roulette.vpk ${VITA_TITLEID} Russian_Roulette.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg0.png sce_sys/livearea/contents/bg0.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE res/gun.png gun.png
  FILE res/9mm.ogg 9mm.ogg
)
