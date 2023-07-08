# min version
cmake_minimum_required(VERSION 3.12)

# include sdk
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/tools/CMakeLists.txt)

# set name and c/c++ standard
project(tft_controller C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# create pico-sdk subdir
pico_sdk_init()

# set main file
add_executable(${PROJECT_NAME}
    main.c
)

# Create C header file with the name <pio program>.pio.h
pico_generate_pio_header(${PROJECT_NAME}  
        ${CMAKE_CURRENT_LIST_DIR}/blink.pio
)

# create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# lin to pico_stdlib
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_pio
    hardware_dma
    hardware_irq
)

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)