#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_exti.h"
#include "usart.h"
#include "gpio.h"

int main(void) {
	ledInit();
	usartInit();
	initPulsioximeter();
	printf("Hello\r");
	while (1) {
		printf("BPM: %u ", getBPM());
		printf("SpO2: %u\r", getOxygenSaturation());
		delay_us(100000 / 6);
	}
}

void EXTI2_3_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
		readPulsioximeter();
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

