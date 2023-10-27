set(CMAKE_SYSTEM_NAME Generic-ELF)
set(CMAKE_SYSTEM_PROCESSOR armhf)
set(CMAKE_CROSSCOMPILING TRUE)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_AR arm-none-eabi-gcc-ar)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_RANLIB arm-none-eabi-gcc-ranlib)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
set(CORO_PLATFORM STM32F4XX)

set(ARM_COMPILE_FLAGS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -ffunction-sections
    -fdata-sections
    -specs=nosys.specs)

add_compile_options(${ARM_COMPILE_FLAGS} -fno-strict-aliasing -fno-builtin)
add_link_options(${ARM_COMPILE_FLAGS} -Wl,--gc-sections
                 -Wl,--print-memory-usage)
