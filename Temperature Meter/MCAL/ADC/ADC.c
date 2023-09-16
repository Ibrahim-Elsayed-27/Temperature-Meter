/*
 * ADC.c
 *
 * Created: 9/9/2023 2:15:02 AM
 *  Author: himah
 */ 


#include "ADC.h"
#include <avr/interrupt.h>

static void (*adc_callback) (void) = NULL;

void adc_init(){
	/*AREF is the refrence voltage*/
	CLR_BIT(ADMUX_REG,REFS0);
	CLR_BIT(ADMUX_REG,REFS1);
	/*ENABLE ADC*/
	SET_BIT(ADCSRA_REG,ADEN);
	/*No Left Adjustment*/
	CLR_BIT(ADMUX_REG,ADLAR);
	/*ADJUST PRESCALAR 64*/
	CLR_BIT(ADCSRA_REG,ADPS0);
	SET_BIT(ADCSRA_REG,ADPS1);
	SET_BIT(ADCSRA_REG,ADPS2);
	
	#if defined INTERRUPT_ENABLE
	SET_BIT(SREG_REG,I_BIT);
	SET_BIT(ADCSRA_REG,ADIE);
	#endif
	
	

}
uint16 adc_read(uint8 mux){
	/*MUX Channel Selection*/
	ADMUX_REG &= 0b11100000;
	ADMUX_REG |= mux;
	/*start conversion*/
	SET_BIT(ADCSRA_REG,ADSC);
	/*wait for conversion*/
	while(GET_BIT(ADCSRA_REG,ADIF) == 0);
	SET_BIT(ADCSRA_REG,ADIF);
	/*Return data*/
	uint16 return_data = (ADCL_REG);
	return_data |= (ADCH_REG <<8);
	
	return return_data; 
}

void adc_interrupt_start(){
		/*start conversion*/
		SET_BIT(ADCSRA_REG,ADSC);
}

void adc_set_callback( void (*callback) (void) ){
	adc_callback = callback;
}

ISR(ADC_vect){
	adc_callback();
}