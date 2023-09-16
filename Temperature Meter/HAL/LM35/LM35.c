/*
 * LM35.c
 *
 * Created: 9/11/2023 11:38:09 PM
 *  Author: himah
 */ 

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/ADC/ADC.h"
#include "LM35.h"

void lm35_init(uint8 pin1, uint8 pin2){
	#if defined POSITIVE_ONLY
	pin_init(PORT_A ,pin1,INPUT);
	
	#else if defined NEGATIVE_POSITVE
	pin_init(PORT_A ,pin1,INPUT);
	pin_init(PORT_A ,pin2,INPUT);
	#endif
	adc_init();
}
uint16 lm35_read(uint8 mux){
	uint16 lm35_temp_value;
	lm35_temp_value = (adc_read(mux) * (REFRENCE_VOLTAGE / 1024) * 100);

	return lm35_temp_value;
}