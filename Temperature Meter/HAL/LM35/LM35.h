/*
 * LM35.h
 *
 * Created: 9/11/2023 11:37:57 PM
 *  Author: himah
 */ 


#ifndef LM35_H_
#define LM35_H_

#include "../../Std_Macros.h"

/*mode*/
#define NEGATIVE_POSITVE
#define REFRENCE_VOLTAGE 2.56



void lm35_init(uint8 pin1, uint8 pin2);
uint16 lm35_read(uint8 mux);



#endif /* LM35_H_ */