/*
 * Temperature Meter.c
 *
 * Created: 9/11/2023 11:20:10 PM
 * Author : himah
 */ 

#include "HAL/LCD/LCD.h"
#include "HAL/LED/LED.h"
#include "HAL/LM35/LM35.h"
#define  F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
    lcd_init();
	lm35_init(PIN0,PIN2);
	led_init(PORT_A,PIN5);
	uint16 temp;
	uint8 char1,char2,char3;
    while (1) 
    {
		lcd_clear_screen();
		lcd_send_string("Temp(c)=");
		temp = lm35_read(16);
		if (temp>=100){
			led_off(PORT_A,PIN5);
			temp -= 100;
			char1 = temp/100;
			char2 = (temp%100)/10;
			char3 = (temp%100)%10;
			if (char1 != 0){
				lcd_send_char(char1+48);
			}
			if (char2 != 0){
				lcd_send_char(char2 + 48);
			}
			lcd_send_char(char3 + 48);
			
		}else{
			led_on(PORT_A,PIN5);
			temp  = 100 - temp;
			char1 = '-';
			char2 = temp/10;
			char3 = temp%10;
			lcd_send_char(char1);
			if (char2 != 0){
				lcd_send_char(char2 + 48);
			}
			lcd_send_char(char3 + 48);
		}
		
		_delay_ms(1000);
		
    }
}

