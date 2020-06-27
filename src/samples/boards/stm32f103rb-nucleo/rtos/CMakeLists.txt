project(rtos_samples C CXX ASM)
include(Utils)
set(EEL_FREERTOS_MEMORY_MANAGEMENT "HEAP4")

find_package(EelHal COMPONENTS gpio uart REQUIRED)
find_package(FreeRTOS REQUIRED)
find_package(EelUtils REQUIRED)
find_package(OpenOCD REQUIRED)

add_rtos_sample(simple_task simple_task.cpp config/stm32f1xx_it.c config/stm32f1xx_hal_msp.c)
add_rtos_sample(sender_receiver_tasks sender_receiver_tasks.cpp config/stm32f1xx_it.c config/stm32f1xx_hal_msp.c)
add_rtos_sample(os_object_test os_object_test.cpp config/stm32f1xx_it.c config/stm32f1xx_hal_msp.c)
add_rtos_sample(mailbox_test mailbox_test.cpp config/stm32f1xx_it.c config/stm32f1xx_hal_msp.c)
add_rtos_sample(semaphore_test semaphore_test.cpp config/stm32f1xx_it.c config/stm32f1xx_hal_msp.c)
