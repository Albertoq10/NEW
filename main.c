#include <stdio.h>
#include <stdint.h>
#include "bits.h"
//#include "bits.h"
#include "MK64F12.h"

void delay(uint16_t delay);
/*
 * @brief   Application entry point.
 */
int main(void) {
	/**Variable to capture the input value*/
	uint32_t input_value = 0;

	/**Activating the GPIOB, GPIOC and GPIOE clock gating*/
	SIM->SCGC5 = 0x2E00;
	/**Pin control configuration of GPIOB pin22 and pin21 as GPIO*/
	PORTB->PCR[21] = 0x00000100;
	PORTB->PCR[22] = 0x00000100;
	/**Pin control configuration of GPIOC pin6 as GPIO with is pull-up resistor enabled*/
	PORTC->PCR[6] = 0x00000103;
	/**Pin control configuration of GPIOE pin26 as GPIO*/
	PORTE->PCR[26] = 0x00000100;
	/**Assigns a safe value to the output pin21 of the GPIOB*/
	GPIOB->PDOR = 0x00200000;
	/**Assigns a safe value to the output pin22 of the GPIOB*/
	GPIOB->PDOR |= 0x00400000;
	/**Assigns a safe value to the output pin26 of the GPIOE*/
	GPIOE->PDOR |= 0x04000000;

	GPIOC->PDDR &=~(0x40);//un cero en el bit 6
	/**Configures GPIOB pin21 as output*/
	GPIOB->PDDR = 0x00200000;
	/**Configures GPIOB pin22 as output*/
	GPIOB->PDDR |= 0x00400000;
	/**Configures GPIOE pin26 as output*/
	GPIOE->PDDR |= 0x04000000;

    while(1) {
    	/**Reads all the GPIOC*/
		input_value = GPIOC->PDIR;
		/**Masks the GPIOC in the bit of interest*/
		input_value = input_value & 0x40;
		/**Note that the comparison is not inputValur == False, because it is safer if we switch the arguments*/
		if(FALSE == input_value)
		{
			GPIOB->PDOR |= 0x00200000;/**Blue led off*/
			delay(65000);
			GPIOB->PDOR |= 0x00400000;/**Read led off*/
			delay(65000);
			GPIOE->PDOR |= 0x4000000;/**Green led off*/
			delay(65000);
			GPIOB->PDOR &= ~(0x00200000);/**Blue led on*/
			delay(65000);
			GPIOB->PDOR &= ~(0x00400000);/**Read led on*/
			delay(65000);
			GPIOE->PDOR &= ~(0x4000000);/**Green led on*/
			delay(65000);
			GPIOB->PDOR |= 0x00200000;/**Blue led off*/
			delay(65000);
			GPIOB->PDOR |= 0x00400000;/**Read led off*/
			delay(65000);
			GPIOE->PDOR |= 0x4000000;/**Green led off*/
			delay(65000);
		}
    }
    return 0 ;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
void delay(uint16_t delay)
{
	volatile uint16_t j, i;

	for(j = delay; j > 0; j--)
	{
		__asm("nop");

	}
}
