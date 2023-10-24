cmake_minimum_required(VERSION 3.16)

project(
    stm_lvgl

)
SET(stm_lvgl_dir ${CMAKE_CURRENT_SOURCE_DIR})

set(CXX_PROPERTIES
    C_STANDARD
    11
    C_STANDARD_REQUIRED
    ON
    C_EXTENSIONS
    OFF
    CXX_STANDARD
    20
    CXX_STANDARD_REQUIRED
    ON
    CXX_EXTENSIONS
    OFF
)

INCLUDE_DIRECTORIES(
    ${stm_lvgl_dir}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${stm_lvgl_dir}/Drivers/CMSIS/Include
    ${stm_lvgl_dir}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    ${stm_lvgl_dir}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${stm_lvgl_dir}/Drivers/STM32F4xx_HAL_Driver/Src
    ${stm_lvgl_dir}/lvgl
    ${stm_lvgl_dir}/Core/Inc
    ${stm_lvgl_dir}/Core/Src
)
add_executable(debug ${stm_lvgl_dir}/Core/Src/main.c)