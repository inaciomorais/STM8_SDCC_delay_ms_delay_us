﻿// A. Inácio Morais - 04/2022 
// anderson.morais@protonmail.com - Brazil
//
// SDCC and STM8FLASH - SMT8S103F3 - HSI 16 MHz
// 253 bytes | 8 kbytes

#define CLK_CKDIVR *(unsigned char*)0x50C6

#define PB_ODR *(unsigned char*)0x5005
#define PB_IDR *(unsigned char*)0x5006
#define PB_DDR *(unsigned char*)0x5007
#define PB_CR1 *(unsigned char*)0x5008
#define PB_CR2 *(unsigned char*)0x5009

#define TIM2_CR1 *(unsigned char*)0x5300
	#define CEN 0
#define TIM2_SR1 *(unsigned char*)0x5304
	#define UIF 0
#define TIM2_PSCR *(unsigned char*)0x530E
#define TIM2_ARRH *(unsigned char*)0x530F
#define TIM2_ARRL *(unsigned char*)0x5310

void delay_us(unsigned int us) 		// Reliable for delay equal to or greater than 5us only | fMASTER(HSI) = 16 MHz | SDCC
{
	unsigned char byte_msb = (us >> 8), byte_lsb = us & 0x00FF;

	TIM2_SR1 &= ~(1 << UIF); 	// Clear the update event flag
	TIM2_PSCR = 0x04; 		// 1000 MHz (16 MHz/16 -> 1 us)
	TIM2_ARRH = byte_msb;
	TIM2_ARRL = byte_lsb;
	TIM2_CR1 |= (1 << CEN);		// Enabling timer 2 counter
	while (!(TIM2_SR1 & (1 << UIF)));	// Loop until the update event flag is set
}

void delay_ms(unsigned int ms) 		// fMASTER(HSI) = 16 MHz | SDCC
{
	unsigned int i;
	for (i=0;i<ms;i++) {
		delay_us(1000);
	}
}

int main()
{
	CLK_CKDIVR = 0x00;
		  
	PB_DDR = 0x20;
	PB_CR1 = 0x20;
 

	while(1)
	{
		PB_ODR ^= 0x20;
		delay_ms(1000);
	}
}


