CMSIS Cortex-M3 migration

Files from STM32F10x Standard Peripherals Library V3.5.0 / 08-April-2011:
- STM32F10x_StdPeriph_Lib/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h (V3.5.0 11-March-2011)
- STM32F10x_StdPeriph_Lib/Libraries/CMSIS/CM3/CoreSupport/core_cm3.h ( V1.30 30. October 2009)

Copy stm32f10x.h and core_cm3.h into ./lib/includes
in stm32f10x.h:
uncomment line 68 : #define STM32F10X_MD
comment line 479  : // #include "system_stm32f10x.h"

Remove the files ./lib/includes/scb.h and nr_stddef.h

Remove duplicate definitions:
nr_lib.h  core_cm3 definitions (SCB_Type, SysTick_Type, ...) sys.h def.
nvic.h (nvic_reg_map, NVIC_BASE)
nr_stddef.h (nvic_irq_num)

Modifications:
systick.h:
	comment #include <nr_stddef.h> and all functions except systick_uptime() and systick_get_count()
	replace #include <nr_stddef.h> by #include <stm32f10x.h>
	replace all uint32 by uint32_t
	// Cycle per microsecond at 72MHz
	in systick_get_count():
		replace SYSTICK_BASE->CNT by SysTick->VAL

delay.h:
	replace #include <nr_stddef.h> by #include <stm32f10x.h>
	add #include <nr_lib.h>
	replace all uint32 by uint32_t
	remove void delay(unsigned long ms) and void delayMicroseconds(uint32_t us)
	in micros():
		replace "SYSTICK_RELOAD_VAL + 1" by SYSTICK_RELOAD_VAL
		
systick.c:
	replace all uint32 by uint32_t

nvic.h:
	Add #include "stm32f10x.h" into nvic.h
	comment : void nvic_irq_set_priority(nvic_irq_num irqn, uint8 priority);
	comment : void nvic_sys_reset();
	
	comment : nvic_globalirq_enable() function
	add comment : use void __enable_irq(); from core_cm3.h
	comment : nvic_globalirq_disable() function
	add comment : use void __disable_irq(); from core_cm3.h

	comment : static inline void nvic_irq_enable(nvic_irq_num irq_num) function
	add comment : use void NVIC_EnableIRQ(IRQn_Type IRQn); from core_cm3.h
	comment : static inline void nvic_irq_disable(nvic_irq_num irq_num) function
	add comment : use void NVIC_DisableIRQ(IRQn_Type IRQn); from core_cm3.h
nvic.c:
	comment : #include <scb.h>
	replace all uint32 by uint32_t
	comment : void nvic_irq_set_priority(nvic_irq_num irqn, uint8 priority) function
	add comment : use void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority); from core_cm3.h
	comment : void nvic_sys_reset() function
	add comment : use void NVIC_SystemReset(); from core_cm3.h
	move STM32_NR_INTERRUPTS from nr_stddef.h to nvic.c
	in nvic_init():
		replace nvic_irq_set_priority((nvic_irq_num)i, 0xF);
		by NVIC_SetPriority((IRQn_Type)i, 0xF);
		replace nvic_irq_set_priority(NVIC_SYSTICK, 0xF);
		by NVIC_SetPriority(SysTick_IRQn, 0xF);

nvic.c:
	replace systick_init(SYSTICK_RELOAD_VAL);
	by SysTick_Config(SystemCoreClock / 1000);

nr_lib.h:
	add SYSCLK_FREQ_72MHz from system_stm32f10x.c (115)
	add #define CYCLES_PER_MICROSECOND		72
	add #define SYSTICK_RELOAD_VAL			SYSCLK_FREQ_72MHz / 1000
	move STM32_DELAY_US_MULT from nr_stddef.h to nr_lib.h

Systick usage:
see /STM32F10x_StdPeriph_Lib/Project/STM32F10x_StdPeriph_Examples/SysTick/TimeBase/main.c

https://sourceforge.net/p/libopencm3/mailman/libopencm3-devel/thread/20131216033941.GX9039@home.lan/
