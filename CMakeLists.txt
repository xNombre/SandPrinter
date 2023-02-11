# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location (note this can come from
# environment, CMake cache etc)
set(PICO_SDK_PATH "${CMAKE_SOURCE_DIR}/pico-sdk")

set(PICO_BOARD
    pico
    CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if(PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(
    FATAL_ERROR
      "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}"
  )
endif()

project(Plotter C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(sdcard-spi/FatFs_SPI build)

file(
  GLOB_RECURSE SOURCES
  RELATIVE ${CMAKE_SOURCE_DIR}
  "src/*.cpp")
add_executable(Plotter ${SOURCES})

pico_set_program_name(Plotter "Plotter")
pico_set_program_version(Plotter "0.1")

# Enable debugging via UART/USB COM
add_compile_definitions(DEBUG_IN_SDIO)

pico_enable_stdio_uart(Plotter 1)
pico_enable_stdio_usb(Plotter 0)

target_compile_options(Plotter PRIVATE -Wno-psabi)

# Add the standard library to the build
target_link_libraries(Plotter pico_stdlib)

# Add the standard include files to the build
target_include_directories(
  Plotter
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other
                                       # standard includes, if required
)

target_include_directories(Plotter PRIVATE "src/")

# Add any user requested libraries
target_link_libraries(
  Plotter
  hardware_spi
  hardware_i2c
  hardware_dma
  hardware_timer
  hardware_clocks
  pico_double
  FatFs_SPI)

pico_add_extra_outputs(Plotter)
