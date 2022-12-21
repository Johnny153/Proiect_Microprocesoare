#include "Pit.h"
#include "Uart.h"
#include "ADC.h"

#define SEG_1 (1)// PORT C
#define SEG_2 (2)// PORT C
#define SEG_3 (4)// PORT D
#define SEG_4 (12)// PORT A
#define SEG_5 (4)// PORT A
#define SEG_6 (5)// PORT A
#define SEG_7 (8)// PORT C
#define SEG_8 (9)// PORT C

static int led_state=0;
static int semn=1;
static int pct_state=0;
static int switch_pin=2;
static int counter=1;

void UTILS_PrintCounter(uint16_t count){ 
	uint8_t Digit1=count /1000; 
	uint8_t Digit2=count %1000 /100; 
	uint8_t Digit3=count %100 /10; 
	uint8_t Digit4=count %10;  
	UART0_Transmit(Digit1+48);
	UART0_Transmit(Digit2+48);
	UART0_Transmit(Digit3+48);
	UART0_Transmit(Digit4+48);
} 

void PIT_Init(void) {
	
	// Activarea semnalului de ceas pentru perifericul PIT
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	// Utilizarea semnalului de ceas pentru tabloul de timere
	PIT_MCR &= ~PIT_MCR_MDIS_MASK;
	// Oprirea decrementarii valorilor numaratoarelor in modul debug
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	// Setarea valorii numaratorului de pe canalul 0 la o perioada de 1 secunda
	PIT->CHANNEL[0].LDVAL = 0x9FFFFF;
	
  // Activarea întreruperilor pe canalul 0
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	// Activarea timerului de pe canalul 0
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	
	// Setarea valorii numaratorului de pe canalul 1 la o perioada de 0.1 secunde
	PIT->CHANNEL[1].LDVAL = 0xFFFFF;
	
	// Activara întreruperilor pe canalul 1
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;
	// Activarea timerului de pe canalul 1
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;
	
	
	
	// Activarea întreruperii mascabile si setarea prioritatii
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn,5);
	NVIC_EnableIRQ(PIT_IRQn);
}

void PIT_IRQHandler(void) {
	
	if(PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		if(print_buffer==1)
			semn*=-1;
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		
	if(counter==change_counter)
	{
		if(led_state == 0) {
		GPIOC->PSOR |= (1<<SEG_1);
		GPIOC->PCOR |= (1<<SEG_2);
		GPIOD->PCOR |= (1<<SEG_3);
		GPIOA->PSOR |= (1<<SEG_4);
		GPIOA->PSOR |= (1<<SEG_5);
		GPIOA->PSOR |= (1<<SEG_6);
		GPIOC->PSOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
		if(semn==-1)
			led_state=9;
	} else if (led_state == 1) {
		GPIOC->PCOR |= (1<<SEG_1);
		GPIOC->PCOR |= (1<<SEG_2);
		GPIOD->PSOR |= (1<<SEG_3);
		GPIOA->PCOR |= (1<<SEG_4);
		GPIOA->PCOR |= (1<<SEG_5);
		GPIOA->PSOR |= (1<<SEG_6);
		GPIOC->PCOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
	} else if (led_state == 2) {
		GPIOC->PCOR |= (1<<SEG_1);
		GPIOC->PCOR |= (1<<SEG_2);
		GPIOD->PCOR |= (1<<SEG_3);
		GPIOA->PCOR |= (1<<SEG_4);
		GPIOA->PSOR |= (1<<SEG_5);
		GPIOA->PSOR |= (1<<SEG_6);
		GPIOC->PCOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
	} else if (led_state == 3) {
		GPIOC->PSOR |= (1<<SEG_1);
		GPIOC->PCOR |= (1<<SEG_2);
		GPIOD->PCOR |= (1<<SEG_3);
		GPIOA->PSOR |= (1<<SEG_4);
		GPIOA->PSOR |= (1<<SEG_5);
		GPIOA->PCOR |= (1<<SEG_6);
		GPIOC->PCOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
	} else if (led_state == 4) {
		GPIOC->PCOR |= (1<<SEG_1);
		GPIOC->PSOR |= (1<<SEG_2);
		GPIOD->PCOR |= (1<<SEG_3);
		GPIOA->PCOR |= (1<<SEG_4);
		GPIOA->PSOR |= (1<<SEG_5);
		GPIOA->PCOR |= (1<<SEG_6);
		GPIOC->PCOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
	} else if (led_state == 5) {
		GPIOC->PCOR |= (1<<SEG_1);
		GPIOC->PSOR |= (1<<SEG_2);
		GPIOD->PCOR |= (1<<SEG_3);
		GPIOA->PCOR |= (1<<SEG_4);
		GPIOA->PCOR |= (1<<SEG_5);
		GPIOA->PCOR |= (1<<SEG_6);
		GPIOC->PCOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
	} else if (led_state == 6) {
		GPIOC->PCOR |= (1<<SEG_1);
		GPIOC->PCOR |= (1<<SEG_2);
		GPIOD->PCOR |= (1<<SEG_3);
		GPIOA->PSOR |= (1<<SEG_4);
		GPIOA->PSOR |= (1<<SEG_5);
		GPIOA->PSOR |= (1<<SEG_6);
		GPIOC->PSOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
	} else if (led_state == 7) {
		GPIOC->PCOR |= (1<<SEG_1);
		GPIOC->PCOR |= (1<<SEG_2);
		GPIOD->PCOR |= (1<<SEG_3);
		GPIOA->PCOR |= (1<<SEG_4);
		GPIOA->PCOR |= (1<<SEG_5);
		GPIOA->PCOR |= (1<<SEG_6);
		GPIOC->PCOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
	} else if(led_state==8){
		GPIOC->PCOR |= (1<<SEG_1);
		GPIOC->PCOR |= (1<<SEG_2);
		GPIOD->PCOR |= (1<<SEG_3);
		GPIOA->PCOR |= (1<<SEG_4);
		GPIOA->PSOR |= (1<<SEG_5);
		GPIOA->PCOR |= (1<<SEG_6);
		GPIOC->PCOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
	} else if(led_state==9){
		GPIOC->PCOR |= (1<<SEG_1);
		GPIOC->PCOR |= (1<<SEG_2);
		GPIOD->PCOR |= (1<<SEG_3);
		GPIOA->PCOR |= (1<<SEG_4);
		GPIOA->PCOR |= (1<<SEG_5);
		GPIOA->PCOR |= (1<<SEG_6);
		GPIOC->PSOR |= (1<<SEG_7);
		led_state=(semn+led_state)%10;
	}
	counter=1;
}
	else if(counter<change_counter){
		counter++;}
	else {
		counter=1;
	}
	print_buffer=0;
}

	if(PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK) {
		if(switch_pin==2){	
			UART0_Transmit(2);
			UART0_Transmit(0x0D);
			UART0_Transmit(0x0A);
			adcRead(adcSelect(2));
			switch_pin=3;
		}
		else if(switch_pin==3){
			UART0_Transmit(3);
			UART0_Transmit(0x0D);
			UART0_Transmit(0x0A);
			adcRead(adcSelect(3));
			switch_pin=2;
		}
		UTILS_PrintCounter(ADC0->R[0]);
		UART0_Transmit(0x0D);
		UART0_Transmit(0x0A);
		PIT->CHANNEL[1].TFLG &= PIT_TFLG_TIF_MASK;
		if(pct_state==0){
			GPIOC->PSOR |= (1<<SEG_8);
			pct_state = 1;
		}else if(pct_state==1){
			GPIOC->PCOR |= (1<<SEG_8);
			pct_state = 0;
		}
	}
}
