#include "Uart.h"
#include "Pit.h"
#include "gpio.h"
#include "ADC.h"


extern uint32_t timer_value;
extern int led_state;
extern int pct_state;
extern int semn;



int main() {
	
	UART0_Init(115200);
	BCD_Init();
	PIT_Init();
	adcInit();
	while(1){}
}
