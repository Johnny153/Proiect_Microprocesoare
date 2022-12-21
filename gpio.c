#include "gpio.h"

#define SEG_1 (1)// PORT C
#define SEG_2 (2)// PORT C
#define SEG_3 (4)// PORT D
#define SEG_4 (12)// PORT A
#define SEG_5 (4)// PORT A
#define SEG_6 (5)// PORT A
#define SEG_7 (8)// PORT C
#define SEG_8 (9)// PORT C



void BCD_Init(void){
	// Activarea semnalului de ceas pentru a putea folosi GPIO
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	// Utilizarea GPIO impune selectarea variantei de multiplexare cu valorea 1
	PORTC->PCR[SEG_1] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[SEG_1] |= PORT_PCR_MUX(1);
	GPIOC->PDDR |= (1<<SEG_1);
	GPIOC->PCOR |= (1<<SEG_1);
	
	PORTC->PCR[SEG_2] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[SEG_2] |= PORT_PCR_MUX(1);
	GPIOC->PDDR |= (1<<SEG_2);
	GPIOC->PCOR |= (1<<SEG_2);
	
	PORTD->PCR[SEG_3] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[SEG_3] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1<<SEG_3);
	GPIOD->PCOR |= (1<<SEG_3);
	
	PORTA->PCR[SEG_4] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[SEG_4] |= PORT_PCR_MUX(1);
	GPIOA->PDDR |= (1<<SEG_4);
	GPIOA->PCOR |= (1<<SEG_4);
	
	PORTA->PCR[SEG_5] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[SEG_5] |= PORT_PCR_MUX(1);
	GPIOA->PDDR |= (1<<SEG_5);
	GPIOA->PCOR |= (1<<SEG_5);
	
	PORTA->PCR[SEG_6] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[SEG_6] |= PORT_PCR_MUX(1);
	GPIOA->PDDR |= (1<<SEG_6);
	GPIOA->PCOR |= (1<<SEG_6);
	
	PORTC->PCR[SEG_7] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[SEG_7] |= PORT_PCR_MUX(1);
	GPIOC->PDDR |= (1<<SEG_7);
	GPIOC->PSOR |= (1<<SEG_7);
	
	PORTC->PCR[SEG_8] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[SEG_8] |= PORT_PCR_MUX(1);
	GPIOC->PDDR |= (1<<SEG_8);
	GPIOC->PCOR |= (1<<SEG_8);
}
