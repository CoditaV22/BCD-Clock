#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "rtc.h"
#include "systick.h"
#include "gpio.h"

#define BUFF_LEN	14


static void display_calendar(void);
static void SysTick_callback(void);
static void uart_callback(void);

uint8_t time_buffer[BUFF_LEN] = {0};
uint8_t date_buffer[BUFF_LEN] = {0};

char key;

int main(void)
{

	uart2_rx_interrupt_init();
	rtc_init();
	systick_1Hz_interrupt();

	while(1){

	}

}

static void display_calendar(void)
{
	sprintf((char *)time_buffer , "%.2d : %.2d : %.2d" ,rtc_convert_bcd2bin(rtc_time_get_hour())
													   ,rtc_convert_bcd2bin(rtc_time_get_minute())
													   ,rtc_convert_bcd2bin(rtc_time_get_second()));

	printf("Time : %.2d : %.2d : %.2d\n\r"             ,rtc_convert_bcd2bin(rtc_time_get_hour())
													   ,rtc_convert_bcd2bin(rtc_time_get_minute())
													   ,rtc_convert_bcd2bin(rtc_time_get_second()));


}

static void uart_callback(void)
{
	key =  USART2->RDR;

	sprintf((char *)date_buffer , "%.2d - %.2d - %.2d"     ,rtc_convert_bcd2bin(rtc_date_get_day())
														   ,rtc_convert_bcd2bin(rtc_date_get_month())
														   ,rtc_convert_bcd2bin(rtc_date_get_year()));

	if(key == '1')
		{
		printf("Date : %.2d - %.2d - %.2d\n\r" 			   ,rtc_convert_bcd2bin(rtc_date_get_day())
															   ,rtc_convert_bcd2bin(rtc_date_get_month())
															   ,rtc_convert_bcd2bin(rtc_date_get_year()));
		}
}

void USART2_IRQHandler(void)
{
	/*ChecK if RXNE is set*/

	if(USART2-> ISR & ISR_RXNE)
	{
		uart_callback();

	}
}

static void SysTick_callback(void)
{
	display_calendar();
	GPIO_set_light();
}

void SysTick_Handler(void)
{
	SysTick_callback();
}


