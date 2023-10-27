project(stm_lvgl LANGUAGES C CXX ASM)


include_directories(${CMAKE_SOURCE_DIR}/Core/Inc)
include_directories(${CMAKE_SOURCE_DIR}/Core/Src)
include_directories(${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc)
include_directories(${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy)
include_directories(${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src)
include_directories(${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include)
include_directories(${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include)



add_executable(${PROJECT_NAME} 
      ${CMAKE_SOURCE_DIR}/Core/src/main.c
      ${CMAKE_SOURCE_DIR}/Core/Src/ST7789S_driver.c
      ${CMAKE_SOURCE_DIR}/Core/Src/stm32f4xx_hal_msp.c
      ${CMAKE_SOURCE_DIR}/Core/Src/stm32f4xx_it.c
      ${CMAKE_SOURCE_DIR}/Core/Src/syscalls.c
      ${CMAKE_SOURCE_DIR}/Core/Src/sysmem.c
      ${CMAKE_SOURCE_DIR}/Core/Src/system_stm32f4xx.c
      ${CMAKE_SOURCE_DIR}/Core/Src/ST7789S.c
      ${CMAKE_SOURCE_DIR}/Core/Startup/startup_stm32f413xx.s
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
      ${CMAKE_SOURCE_DIR}//Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
      ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
)

target_link_options(${PROJECT_NAME} PRIVATE -T${CMAKE_SOURCE_DIR}/STM32F413.ld)

link_directories(
      ${CMAKE_SOURCE_DIR}/lvgl
      ${CMAKE_SOURCE_DIR}/lvgl/examples)

target_link_libraries(${PROJECT_NAME} lvgl lvgl_examples)





add_custom_target(
  ${PROJECT_NAME}.hex ALL
  COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
  DEPENDS ${PROJECT_NAME}.elf)
  
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND arm-none-eabi-nm --print-size --reverse-sort --size-sort --radix=d
  "${PROJECT_NAME}.elf" > mem.txt)
