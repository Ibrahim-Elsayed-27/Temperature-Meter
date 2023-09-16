/*
 * ADC.h
 *
 * Created: 9/9/2023 2:14:54 AM
 *  Author: himah
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "../../Std_Macros.h"




#define ADMUX_REG    *((volatile uint8*) 0x27)
#define ADCSRA_REG   *((volatile uint8*) 0x26)
#define ADCH_REG     *((volatile uint8*) 0x25)
#define ADCL_REG     *((volatile uint8*) 0x24)
#define SFIOR_REG    *((volatile uint8*) 0x50)
#define SREG_REG *((volatile uint8*) 0x5F)


/*ADMUX BITS*/
#define ADLAR 5
#define REFS0 6
#define REFS1 7



/*ADCSRA BITS*/
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE  3
#define ADIF  4
#define ADSC  6
#define ADEN  7


/*SREG BITS*/
#define I_BIT 7


void adc_init();
uint16 adc_read(uint8 mux);
void adc_interrupt_start();
void adc_set_callback( void (*callback) (void) );



#endif /* ADC_H_ */