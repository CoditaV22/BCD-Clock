#include "stm32f0xx.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "uart.h"
#include "rtc.h"
#include "systick.h"
#include "gpio.h"


static void get_calendar(void);
static void SysTick_callback(void);
static void uart_callback(void);

uint8_t time_buffer[12] = {0};
uint8_t date_buffer[12] = {0};
uint8_t alr_set;

char key;
char alarm_time[12] = "13 : 26 : 10";

int main(void)
{
	uart2_rx_interrupt_init();
	rtc_init();
	systick_1Hz_interrupt();
	alr_set = 0;

	while(1){

	}

}

static void get_calendar(void)
{
	sprintf((char *)time_buffer , "%.2d : %.2d : %.2d" ,rtc_convert_bcd2bin(rtc_time_get_hour())
													   ,rtc_convert_bcd2bin(rtc_time_get_minute())
													   ,rtc_convert_bcd2bin(rtc_time_get_second()));
}

static void uart_callback(void)
{
	key =  USART2->RDR;

	sprintf((char *)date_buffer , "%.2d - %.2d - %.2d"     ,rtc_convert_bcd2bin(rtc_date_get_day())
														   ,rtc_convert_bcd2bin(rtc_date_get_month())
														   ,rtc_convert_bcd2bin(rtc_date_get_year()));

	if(key == 'D')
		{
		printf("Date : %.2d - %.2d - %.2d\n\r" 			   ,rtc_convert_bcd2bin(rtc_date_get_day())
														   ,rtc_convert_bcd2bin(rtc_date_get_month())
														   ,rtc_convert_bcd2bin(rtc_date_get_year()));
		}
	else if(key == 'T')
	{
		printf("Time : %.2d : %.2d : %.2d\n\r"             	   ,rtc_convert_bcd2bin(rtc_time_get_hour())
															   ,rtc_convert_bcd2bin(rtc_time_get_minute())
															   ,rtc_convert_bcd2bin(rtc_time_get_second()));
	}
	else if(key == 'A')
	{
		printf("Alarm set for %s\n\r" , alarm_time);
		alr_set = 1;

	}
}

void USART2_IRQHandler(void)
{
	/*Check if RXNE is set*/

	if(USART2-> ISR & ISR_RXNE)
	{
		uart_callback();

	}
}

static void SysTick_callback(void)
{
	get_calendar();
	GPIO_set_light();
	if(alr_set)
	{
		if(strcmp((char *)time_buffer , alarm_time) == 0)
		{
			printf("ALARM RINGING!!!!!");
		}
	}
}

void SysTick_Handler(void)
{
	SysTick_callback();
}




