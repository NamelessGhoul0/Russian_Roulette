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
  src/Nogg/src/util/memory.c
  src/Nogg/src/util/float-to-int16.c
  src/Nogg/src/util/decode-frame.c
  src/Nogg/src/decode/stb_vorbis.c
  src/Nogg/src/decode/setup.c
  src/Nogg/src/decode/seek.c
  src/Nogg/src/decode/packet.c
  src/Nogg/src/decode/io.c
  src/Nogg/src/decode/decode.c
  src/Nogg/src/decode/crc32.c
  src/Nogg/src/api/version.c
  src/Nogg/src/api/seek-tell.c
  src/Nogg/src/api/read-int16.c
  src/Nogg/src/api/read-float.c
  src/Nogg/src/api/open-file.c
  src/Nogg/src/api/open-callbacks.c
  src/Nogg/src/api/open-buffer.c
  src/Nogg/src/api/info.c
  src/Nogg/src/api/close.c
  src/Media/WavFile.c
  src/Media/FileBuffer.c
  src/Media/Audio.c
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
