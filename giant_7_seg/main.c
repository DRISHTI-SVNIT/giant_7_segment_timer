/*
 * giant_7_seg.c
 *
 * Created: 28-03-2017 20:26:56
 * Author : mehulbhai
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include "USART_32.h"
#include <avr/interrupt.h>

enum {min1,min2,sec1,sec2};

volatile int desired_day,desired_hour,desired_minute = 30,desired_second = 0;
volatile int current_day,current_hour,current_minute = 0,current_second = 0;
volatile int count_day,count_hour,count_minute,count_second;
volatile int day,hour,minute,second;

void set_7seg_num(int segment,uint8_t numb);

void get_needed_time(void)
{
	count_day = desired_day - current_day;
	count_hour = desired_hour - count_hour;
	if (count_hour < 0)
	{
		count_hour = count_hour + 60;
		count_day = count_day - 1;
	}
	count_minute = desired_minute - current_minute;
	if (count_minute < 0)
	{
		count_minute = count_minute + 60;
		count_hour = count_hour - 1;
	}
	count_second = desired_second - current_second;
	if (count_second < 0)
	{
		count_second = count_second + 60;
		count_minute = count_minute - 1;
	}
	day = count_day;
	hour = count_hour;
	minute = count_minute;
	second = count_second;
}

int main(void)
{
	DDRA = 0XFF; 
	DDRB = 0XFF;
	DDRC |= (1<<PINC2)|(1<<PINC3)|(1<<PINC4)|(1<<PINC5)|(1<<PINC6)|(1<<PINC7);
	DDRD |= (1<<PIND2)|(1<<PIND3)|(1<<PIND4)|(1<<PIND5)|(1<<PIND6)|(1<<PIND7);
    
	USART_Init(12);//4800 baud rate
	
	//TCCR1B |= (1<<WGM12)|(1<<CS10)|(1<<CS11);
	//TIMSK |= (1<<OCIE1A);
	//OCR1A = 15624;
	//sei();
	get_needed_time();
	set_7seg_num(sec1,second/10);
	set_7seg_num(sec2,second%10);
	set_7seg_num(min1,second/10);
	set_7seg_num(min2,second%10);
	
    while (1) 
    {
		set_7seg_num(min1,0);
		_delay_ms(1500);
		set_7seg_num(min1,1);
		_delay_ms(1500);
		set_7seg_num(min1,2);
		_delay_ms(1500);
		set_7seg_num(min1,3);
		_delay_ms(1500);
		set_7seg_num(min1,4);
		_delay_ms(1500);
		set_7seg_num(min1,5);
		_delay_ms(1500);
		set_7seg_num(min1,6);
		_delay_ms(1500);
		set_7seg_num(min1,7);
		_delay_ms(1500);
		set_7seg_num(min1,8);
		_delay_ms(1500);
		set_7seg_num(min1,9);
		_delay_ms(1500);
	}
}

ISR(TIMER1_COMPA_vect)
{
	second--;
	set_7seg_num(sec1,second/10);
	set_7seg_num(sec2,second%10);
	if (second <= 0)
	{
		second = 60;
		minute --;
		set_7seg_num(min1,second/10);
		set_7seg_num(min2,second%10);
	}
	if (minute <= 0)
	{
		minute = 60;
		hour--;
	}
}

void set_7seg_num(int segment,uint8_t numb)
{
	switch(segment)
	{
		case min1:
		{
			switch(numb)
			{
				case 0:
				PORTB |= (1<<PINB1)|(1<<PINB2)|(1<<PINB3)|(1<<PINB4)|(1<<PINB5)|(1<<PINB6);
				PORTB &= ~(1<<PINB0);
				break;
				
				case 1:
				PORTB |= (1<<PINB4)|(1<<PINB5);
				PORTB &= ~((1<<PINB1)|(1<<PINB2)|(1<<PINB3)|(1<<PINB6)|(1<<PINB0));
				break;
				
				case 2:
				PORTB |= ((1<<PINB2)|(1<<PINB3)|(1<<PINB5)|(1<<PINB6)|(1<<PINB0));
				PORTB &= ~((1<<PINB1)|(1<<PINB4));
				break;
				
				case 3:
				PORTB |= (1<<PINB3)|(1<<PINB4)|(1<<PINB5)|(1<<PINB6)|(1<<PINB0);
				PORTB &= ~((1<<PINB1)|(1<<PINB2));
				break;
				
				case 4:
				PORTB |= (1<<PINB1)|(1<<PINB4)|(1<<PINB5)|(1<<PINB0);
				PORTB &= ~((1<<PINB2)|(1<<PINB3)|(1<<PINB6));
				break;
				
				case 5:
				PORTB |= (1<<PINB1)|(1<<PINB3)|(1<<PINB4)|(1<<PINB6)|(1<<PINB0);
				PORTB &= ~((1<<PINB2)|(1<<PINB5));
				break;
				
				case 6:
				PORTB |= (1<<PINB1)|(1<<PINB2)|(1<<PINB3)|(1<<PINB4)|(1<<PINB6)|(1<<PINB0);
				PORTB &= ~((1<<PINB5));
				break;
				
				case 7:
				PORTB |= (1<<PINB4)|(1<<PINB5)|(1<<PINB6);
				PORTB &= ~((1<<PINB1)|(1<<PINB2)|(1<<PINB3)|(1<<PINB0));
				break;
				
				case 8:
				PORTB |= (1<<PINB1)|(1<<PINB2)|(1<<PINB3)|(1<<PINB4)|(1<<PINB5)|(1<<PINB6)|(1<<PINB0);
				break;
				
				case 9:
				PORTB |= (1<<PINB1)|(1<<PINB4)|(1<<PINB5)|(1<<PINB6)|(1<<PINB0);
				PORTB &= ~((1<<PINB2)|(1<<PINB3));
				break;
			}
			break;
		}
		
		case min2:
		{
			switch(numb)
			{
				case 0:
				PORTD |= (1<<PIND2)|(1<<PIND3)|(1<<PIND4)|(1<<PIND5)|(1<<PIND6)|(1<<PIND7);
				PORTB &= ~(1<<PINB7);
				break;
				
				case 1:
				PORTD |= (1<<PIND5)|(1<<PIND6);
				PORTD &= ~((1<<PIND2)|(1<<PIND3)|(1<<PIND4)|(1<<PIND7));
				PORTB &= ~(1<<PINB7);
				break;
				
				case 2:
				PORTD |= ((1<<PIND3)|(1<<PIND4)|(1<<PIND6)|(1<<PIND7));
				PORTD &= ~((1<<PIND2)|(1<<PIND5));
				PORTB |= (1<<PINB7);
				break;
				
				case 3:
				PORTD |= (1<<PIND4)|(1<<PIND5)|(1<<PIND6)|(1<<PIND7);
				PORTD &= ~((1<<PIND2)|(1<<PIND3));
				PORTB |= (1<<PINB7);
				break;
				
				case 4:
				PORTD |= (1<<PIND2)|(1<<PIND5)|(1<<PIND6);
				PORTD &= ~((1<<PIND3)|(1<<PIND4)|(1<<PIND7));
				PORTB |= (1<<PINB7);
				break;
				
				case 5:
				PORTD |= (1<<PIND2)|(1<<PIND4)|(1<<PIND5)|(1<<PIND7);
				PORTD &= ~((1<<PIND3)|(1<<PIND6));
				PORTB |= (1<<PINB7);
				break;
				
				case 6:
				PORTD |= (1<<PIND2)|(1<<PIND3)|(1<<PIND4)|(1<<PIND5)|(1<<PIND7);
				PORTD &= ~((1<<PIND6));
				PORTB |= (1<<PINB7);
				break;
				
				case 7:
				PORTD |= (1<<PIND5)|(1<<PIND6)|(1<<PIND7);
				PORTD &= ~((1<<PIND2)|(1<<PIND3)|(1<<PIND4));
				PORTB &= ~(1<<PINB7);
				break;
				
				case 8:
				PORTD |= (1<<PIND2)|(1<<PIND3)|(1<<PIND4)|(1<<PIND5)|(1<<PIND6)|(1<<PIND7);
				PORTB |= (1<<PINB7);
				break;
				
				case 9:
				PORTD |= (1<<PIND2)|(1<<PIND5)|(1<<PIND6)|(1<<PIND7);
				PORTD &= ~((1<<PIND3)|(1<<PIND4));
				PORTB |= (1<<PINB7);
				break;
		}
		break;
		
	}
		case sec1:
		{
			switch(numb)
			{
				case 0:
				PORTA |= (1<<PINA7);
				PORTC |= (1<<PINC3)|(1<<PINC4)|(1<<PINC5)|(1<<PINC6)|(1<<PINC7);
				PORTC &= ~(1<<PINC2);
				break;
				
				case 1:
				PORTA &= ~(1<<PINA7);
				PORTC |= (1<<PINC6)|(1<<PINC7);
				PORTC &= ~((1<<PINC3)|(1<<PINC4)|(1<<PINC5));
				PORTC &= ~(1<<PINC2);
				break;
				
				case 2:
				PORTA |= (1<<PINA7);
				PORTC |= ((1<<PINC4)|(1<<PINC5)|(1<<PINC7));
				PORTC &= ~((1<<PINC3)|(1<<PINC6));
				PORTC |= (1<<PINC2);
				break;
				
				case 3:
				PORTA |= (1<<PINA7);
				PORTC |= (1<<PINC5)|(1<<PINC6)|(1<<PINC7);
				PORTC &= ~((1<<PINC3)|(1<<PINC4));
				PORTC |= (1<<PINC2);
				break;
				
				case 4:
				PORTA &= ~(1<<PINA7);
				PORTC |= (1<<PINC3)|(1<<PINC6)|(1<<PINC7)|(1<<PINC2);
				PORTC &= ~((1<<PINC4)|(1<<PINC5));
				PORTC |= (1<<PINC2);
				break;
				
				case 5:
				PORTA |= (1<<PINA7);
				PORTC |= (1<<PINC3)|(1<<PINC5)|(1<<PINC6);
				PORTC &= ~((1<<PINC4)|(1<<PINC7));
				PORTC |= (1<<PINC2);
				break;
				
				case 6:
				PORTA |= (1<<PINA7);
				PORTC |= (1<<PINC3)|(1<<PINC4)|(1<<PINC5)|(1<<PINC6);
				PORTC &= ~((1<<PINC7));
				PORTC |= (1<<PINC2);
				break;
				
				case 7:
				PORTA |= (1<<PINA7);
				PORTC |= (1<<PINC6)|(1<<PINC7);
				PORTC &= ~((1<<PINC3)|(1<<PINC4)|(1<<PINC5));
				PORTC &= ~(1<<PINC2);
				break;
				
				case 8:
				PORTA |= (1<<PINA7);
				PORTC |= (1<<PINC3)|(1<<PINC4)|(1<<PINC5)|(1<<PINC6)|(1<<PINC7);
				PORTC |= (1<<PINC2);
				break;
				
				case 9:
				PORTA |= (1<<PINA7);
				PORTC |= (1<<PINC3)|(1<<PINC6)|(1<<PINC7);
				PORTC &= ~((1<<PINC4)|(1<<PINC5));
				PORTC |= (1<<PINC2);
				break;
			}
			break;
		}
			case sec2:
			{
				switch(numb)
				{
				case 0:
				PORTA |= (1<<PINA5)|(1<<PINA4)|(1<<PINA3)|(1<<PINA2)|(1<<PINA1)|(1<<PINA0);
				PORTA &= ~(1<<PINA6);
				break;
				
				case 1:
				PORTA |= (1<<PINA4)|(1<<PINA1);
				PORTA &= ~((1<<PINA5)|(1<<PINA4)|(1<<PINA3)|(1<<PINA0)|(1<<PINA6));
				break;
				
				case 2:
				PORTA |= ((1<<PINA4)|(1<<PINA3)|(1<<PINA1)|(1<<PINA0)|(1<<PINA6));
				PORTA &= ~((1<<PINA5)|(1<<PINA2));
				break;
				
				case 3:
				PORTA |= (1<<PINA3)|(1<<PINA2)|(1<<PINA1)|(1<<PINA0)|(1<<PINA6);
				PORTA &= ~((1<<PINA5)|(1<<PINA4));
				break;
				
				case 4:
				PORTA |= (1<<PINA5)|(1<<PINA2)|(1<<PINA1)|(1<<PINA6);
				PORTA &= ~((1<<PINA4)|(1<<PINA3)|(1<<PINA0));
				break;
				
				case 5:
				PORTA |= (1<<PINA5)|(1<<PINA3)|(1<<PINA2)|(1<<PINA0)|(1<<PINA6);
				PORTA &= ~((1<<PINA4)|(1<<PINA1));
				break;
				
				case 6:
				PORTA |= (1<<PINA5)|(1<<PINA4)|(1<<PINA3)|(1<<PINA2)|(1<<PINA0)|(1<<PINA6);
				PORTA &= ~((1<<PINA1));
				break;
				
				case 7:
				PORTA |= (1<<PINA2)|(1<<PINA1)|(1<<PINA0);
				PORTA &= ~((1<<PINA5)|(1<<PINA4)|(1<<PINA3)|(1<<PINA6));
				break;
				
				case 8:
				PORTA |= (1<<PINA5)|(1<<PINA4)|(1<<PINA3)|(1<<PINA2)|(1<<PINA1)|(1<<PINA0)|(1<<PINA6);
				break;
				
				case 9:
				PORTA |= (1<<PINA5)|(1<<PINA2)|(1<<PINA1)|(1<<PINA0)|(1<<PINA6);
				PORTA &= ~((1<<PINA4)|(1<<PINA3));
				break;
			}
			break;
			}
		}
}