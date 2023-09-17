/*
 * Temperature Meter.c
 *
 * Created: 9/11/2023 11:20:10 PM
 * Author : himah
 */ 


#include "HAL/LCD/LCD.h"
#include "HAL/LED/LED.h"
#include "HAL/LM35/LM35.h"
#include "HAL/KEYPAD/keypad.h"

#define  F_CPU 8000000UL
#include <util/delay.h>

#define RED_PIN  PIN5

void reset_thresh();
void thresh_comp(uint16 temp,uint16 temp_thresh);
volatile uint16 temp_thresh = 256;
int main(void)
{
    lcd_init();
	keypad_init();

	
	lm35_init(PIN0,PIN2,reset_thresh);
	led_init(PORT_A,PIN5);
	
	uint16 temp;
	uint8 char1,char2,char3;
    while (1) 
    {
			lcd_clear_screen();
			lcd_send_string("Temp(c)=");
			temp = lm35_read(16);
			thresh_comp(temp , temp_thresh);
			if (temp>=100){
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



void reset_thresh(){
	_delay_ms(200);
	lcd_clear_screen();
	uint8 read_arr[3]={0};
	uint8 iter=0;
	uint8 read_value;
	lcd_send_string("New thresh(c):");
	lcd_move_cursor(2,1);
	read_value = keypad_read();
	_delay_ms(200);
	while(read_value != '=' && iter<3){
		if (read_value != 0xff){
			read_arr[iter] = read_value;
			lcd_send_char(read_value);
			iter++; 
		}
		read_value = keypad_read();
		_delay_ms(200);
		
	}
	if (read_arr[0] == '-'){
		if (iter == 3){
			temp_thresh = (read_arr[1]-48)*10 + (read_arr[2]-48);
		}else{
			temp_thresh = read_arr[1]-48;
		}
		temp_thresh = 100 - temp_thresh;
	}else{
		if (iter == 3){
			temp_thresh = (read_arr[0]-48)*100 + (read_arr[1]-48)*10 + (read_arr[2]-48) ;
		}else if(iter == 2){
			temp_thresh = (read_arr[0]-48)*10 +(read_arr[1]-48) ;
		}else{
			temp_thresh = read_arr[0]-48 ;
		}
		temp_thresh += 100;
	}
}


void thresh_comp(uint16 temp,uint16 temp_thresh){
		if (temp_thresh>100){
			if(temp > temp_thresh){
				led_on(PORT_A,RED_PIN);
			}
			else{
				led_off(PORT_A,RED_PIN);
			}
		}
		else{
			if(temp < temp_thresh){
				led_on(PORT_A,RED_PIN);
			}
			else{
				led_off(PORT_A,RED_PIN);
			}
		}
	}