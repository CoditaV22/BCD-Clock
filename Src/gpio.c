#include "gpio.h"
#include "rtc.h"

#define GPIOAEN 	(1U << 17)
#define GPIOBEN		(1U << 18)

/*
	LEDs : Hours[0]   :     PA0 - 1
		   Hours[1]   :     PB4-5 PA4- 5
		   Minutes[0] :		PA6 - 8
		   Minutes[1] : 	PA9 - 12
		   Seconds[0] : 	PB6-8
		   Seconds[1] : 	PB0 - 3


*/


void GPIO_set_light()
{
	uint32_t hour = rtc_convert_bcd2bin(rtc_time_get_hour());
	uint32_t minute = rtc_convert_bcd2bin(rtc_time_get_minute());
	uint32_t second = rtc_convert_bcd2bin(rtc_time_get_second());
	/*Enable clock access to GPIOA and GPIOB*/
	RCC -> AHBENR |= GPIOAEN;
	RCC -> AHBENR |= GPIOBEN;

	/*Set GPIOs as output*/
	GPIOA -> MODER |= (1U << 0);
	GPIOA -> MODER &=~(1U << 1);
	GPIOA -> MODER |= (1U << 2);
	GPIOA -> MODER &=~(1U << 3);
	GPIOA -> MODER |= (1U << 8);
	GPIOA -> MODER &=~(1U << 9);
	GPIOA -> MODER |= (1U << 10);
	GPIOA -> MODER &=~(1U << 11);
	GPIOA -> MODER |= (1U << 12);
	GPIOA -> MODER &=~(1U << 13);
	GPIOA -> MODER |= (1U << 14);
	GPIOA -> MODER &=~(1U << 15);
	GPIOA -> MODER |= (1U << 16);
	GPIOA -> MODER &=~(1U << 17);
	GPIOA -> MODER |= (1U << 18);
	GPIOA -> MODER &=~(1U << 19);
	GPIOA -> MODER |= (1U << 20);
	GPIOA -> MODER &=~(1U << 21);
	GPIOA -> MODER |= (1U << 22);
	GPIOA -> MODER &=~(1U << 23);
	GPIOA -> MODER |= (1U << 24);
	GPIOA -> MODER &=~(1U << 25);


	GPIOB -> MODER |= (1U << 0);
	GPIOB -> MODER &=~ (1U << 1);
	GPIOB -> MODER |= (1U << 2);
	GPIOB -> MODER &=~ (1U << 3);
	GPIOB -> MODER |= (1U << 4);
	GPIOB -> MODER &=~ (1U << 5);
	GPIOB -> MODER |= (1U << 6);
	GPIOB -> MODER &=~ (1U << 7);
	GPIOB -> MODER |= (1U << 8);
	GPIOB -> MODER &=~ (1U << 9);
	GPIOB -> MODER |= (1U << 10);
	GPIOB -> MODER &=~ (1U << 11);
	GPIOB -> MODER |= (1U << 12);
	GPIOB -> MODER &=~ (1U << 13);
	GPIOB -> MODER |= (1U << 14);
	GPIOB -> MODER &=~ (1U << 15);
	GPIOB -> MODER |= (1U << 16);
	GPIOB -> MODER &=~ (1U << 17);

	/*Hour[0]*/
	if(hour >= 20) //10
	{
		GPIOA -> ODR |=  (1U << 0);
		GPIOA -> ODR &=~ (1U << 1);
	}
	else if(hour >= 10) //01
	{
		GPIOA -> ODR &=~  (1U << 0);
		GPIOA -> ODR |= (1U << 1);
	}
	else //00
	{
		GPIOA -> ODR |=  (1U << 0);
		GPIOA -> ODR &=~ (1U << 1);
	}

	/*Hour[1]*/
	if(hour % 2 == 0)
	{
		GPIOA -> ODR &=~ (1U << 5);
	}
	else
	{
		GPIOA -> ODR |= (1U << 5);
	}
	if(hour % 10 == 0) //0000
	{
		GPIOB -> ODR &=~ (1U << 4);
		GPIOB -> ODR &=~ (1U << 5);
		GPIOA -> ODR &=~  (1U << 4);
	}
	else if(hour % 10 == 1)//0001
	{
		GPIOB -> ODR &=~ (1U << 4);
		GPIOB -> ODR &=~ (1U << 5);
		GPIOA -> ODR &=~ (1U << 4);
	}
	else if(hour % 10 == 2)//0010
	{
		GPIOB -> ODR &=~ (1U << 4);
		GPIOB -> ODR &=~ (1U << 5);
		GPIOA -> ODR |=  (1U << 4);
	}
	else if(hour % 10 == 3)//0011
	{
		GPIOB -> ODR &=~ (1U << 4);
		GPIOB -> ODR &=~ (1U << 5);
		GPIOA -> ODR |= (1U << 4);
	}
	else if(hour % 10 == 4)//0100
	{
		GPIOB -> ODR &=~ (1U << 4);
		GPIOB -> ODR |= (1U << 5);
		GPIOA -> ODR &=~  (1U << 4);
	}
	else if(hour % 10 == 5)//0101
	{
		GPIOB -> ODR &=~ (1U << 4);
		GPIOB -> ODR |= (1U << 5);
		GPIOA -> ODR &=~ (1U << 4);
	}
	else if(hour % 10 == 6)//0110
	{
		GPIOB -> ODR &=~ (1U << 4);
		GPIOB -> ODR |= (1U << 5);
		GPIOA -> ODR |=  (1U << 4);
	}
	else if(hour % 10 == 7)//0111
	{
		GPIOB -> ODR &=~ (1U << 4);
		GPIOB -> ODR |= (1U << 5);
		GPIOA -> ODR |= (1U << 4);
	}
	else if(hour % 10 == 8)//1000
	{
		GPIOB -> ODR |= (1U << 4);
		GPIOB -> ODR &=~ (1U << 5);
		GPIOA -> ODR &=~  (1U << 4);
	}
	else if(hour % 10 == 9)//1001
	{
		GPIOB -> ODR |= (1U << 4);
		GPIOB -> ODR &=~ (1U << 5);
		GPIOA -> ODR &=~  (1U << 4);
	}

	/*Minute[0] PA6 - 8*/
	if(minute < 10) //000
	{
		GPIOA -> ODR &=~ (1U << 6);
		GPIOA -> ODR &=~ (1U << 7);
		GPIOA -> ODR &=~ (1U << 8);
	}
	else if(minute < 20) //001
	{
		GPIOA -> ODR &=~ (1U << 6);
		GPIOA -> ODR &=~ (1U << 7);
		GPIOA -> ODR |= (1U << 8);
	}
	else if(minute < 30) //010
	{
		GPIOA -> ODR &=~ (1U << 6);
		GPIOA -> ODR |= (1U << 7);
		GPIOA -> ODR &=~ (1U << 8);
	}
	else if(minute  < 40) //011
	{
		GPIOA -> ODR &=~ (1U << 6);
		GPIOA -> ODR |= (1U << 7);
		GPIOA -> ODR |= (1U << 8);
	}
	else if(minute  < 50) //100
	{
		GPIOA -> ODR |= (1U << 6);
		GPIOA -> ODR &=~ (1U << 7);
		GPIOA -> ODR &=~ (1U << 8);
	}
	else //101
	{
		GPIOA -> ODR |= (1U << 6);
		GPIOA -> ODR &=~ (1U << 7);
		GPIOA -> ODR |= (1U << 8);
	}




	/*Minute[1] PA9 - 12*/
	if(minute % 2 == 0)
	{
		GPIOA -> ODR &=~ (1U << 12);
	}
	else
	{
		GPIOA -> ODR |= (1U << 12);
	}

	if(minute % 10 == 0) //0000
	{
		GPIOA -> ODR &=~ (1U << 9);
		GPIOA -> ODR &=~ (1U << 10);
		GPIOA -> ODR &=~ (1U << 11);
	}
	else if(minute % 10 == 1)//0001
	{
		GPIOA -> ODR &=~ (1U << 9);
		GPIOA -> ODR &=~ (1U << 10);
		GPIOA -> ODR &=~ (1U << 11);
	}
	else if(minute % 10 == 2)//0010
	{
		GPIOA -> ODR &=~ (1U << 9);
		GPIOA -> ODR &=~ (1U << 10);
		GPIOA -> ODR |=  (1U << 11);
	}
	else if(minute % 10 == 3)//0011
	{
		GPIOA -> ODR &=~ (1U << 9);
		GPIOA -> ODR &=~ (1U << 10);
		GPIOA -> ODR |= (1U << 11);
	}
	else if(minute % 10 == 4)//0100
	{
		GPIOA -> ODR &=~ (1U << 9);
		GPIOA -> ODR |=  (1U << 10);
		GPIOA -> ODR &=~ (1U << 11);
	}
	else if(minute % 10 == 5)//0101
	{
		GPIOA -> ODR &=~ (1U << 9);
		GPIOA -> ODR |=  (1U << 10);
		GPIOA -> ODR &=~ (1U << 11);
	}
	else if(minute % 10 == 6)//0110
	{
		GPIOA -> ODR &=~ (1U << 9);
		GPIOA -> ODR |=  (1U << 10);
		GPIOA -> ODR |=  (1U << 11);
	}
	else if(minute % 10 == 7)//0111
	{
		GPIOA -> ODR &=~ (1U << 9);
		GPIOA -> ODR |=  (1U << 10);
		GPIOA -> ODR |=  (1U << 11);
	}
	else if(minute % 10 == 8)//1000
	{
		GPIOA -> ODR |=  (1U << 9);
		GPIOA -> ODR &=~ (1U << 10);
		GPIOA -> ODR &=~ (1U << 11);

	}
	else if(minute % 10 == 9)//1001
	{
		GPIOA -> ODR |=  (1U << 9);
		GPIOA -> ODR &=~ (1U << 10);
		GPIOA -> ODR &=~ (1U << 11);
	}

	//Second[0] PB 6-8
		if(second < 10) //000
		{
			GPIOB -> ODR &=~ (1U << 6);
			GPIOB -> ODR &=~ (1U << 7);
			GPIOB -> ODR &=~ (1U << 8);
		}
		else if(second < 20) //001
		{
			GPIOB -> ODR &=~ (1U << 6);
			GPIOB -> ODR &=~ (1U << 7);
			GPIOB -> ODR |= (1U << 8);
		}
		else if(second < 30) //010
		{
			GPIOB -> ODR &=~ (1U << 6);
			GPIOB -> ODR |= (1U << 7);
			GPIOB -> ODR &=~ (1U << 8);
		}
		else if(second  < 40) //011
		{
			GPIOB -> ODR &=~ (1U << 6);
			GPIOB -> ODR |= (1U << 7);
			GPIOB -> ODR |= (1U << 8);
		}
		else if(second  < 50) //100
		{
			GPIOB -> ODR |= (1U << 6);
			GPIOB -> ODR &=~ (1U << 7);
			GPIOB -> ODR &=~ (1U << 8);
		}
		else //101
		{
			GPIOB -> ODR |= (1U << 6);
			GPIOB -> ODR &=~ (1U << 7);
			GPIOB -> ODR |= (1U << 8);
		}

		/*Second[1] PB0 - 3*/
			if(second % 2 == 0)
			{
				GPIOB -> ODR &=~ (1U << 3);
			}
			else
			{
				GPIOB -> ODR |= (1U << 3);
			}

			if(second % 10 == 0) //0000
			{
				GPIOB -> ODR &=~ (1U << 0);
				GPIOB -> ODR &=~ (1U << 1);
				GPIOB -> ODR &=~ (1U << 2);
			}
			else if(second % 10 == 1)//0001
			{
				GPIOB -> ODR &=~ (1U << 0);
				GPIOB -> ODR &=~ (1U << 1);
				GPIOB -> ODR &=~ (1U << 2);
			}
			else if(second % 10 == 2)//0010
			{
				GPIOB -> ODR &=~ (1U << 0);
				GPIOB -> ODR &=~ (1U << 1);
				GPIOB -> ODR |=  (1U << 2);
			}
			else if(second % 10 == 3)//0011
			{
				GPIOB -> ODR &=~ (1U << 0);
				GPIOB -> ODR &=~ (1U << 1);
				GPIOB -> ODR |=  (1U << 2);
			}
			else if(second % 10 == 4)//0100
			{
				GPIOB -> ODR &=~ (1U << 0);
				GPIOB -> ODR |=  (1U << 1);
				GPIOB -> ODR &=~ (1U << 2);
			}
			else if(second % 10 == 5)//0101
			{
				GPIOB -> ODR &=~ (1U << 0);
				GPIOB -> ODR |=  (1U << 1);
				GPIOB -> ODR &=~ (1U << 2);
			}
			else if(second % 10 == 6)//0110
			{
				GPIOB -> ODR &=~ (1U << 0);
				GPIOB -> ODR |=  (1U << 1);
				GPIOB -> ODR |=  (1U << 2);
			}
			else if(second % 10 == 7)//0111
			{
				GPIOB -> ODR &=~ (1U << 0);
				GPIOB -> ODR |=  (1U << 1);
				GPIOB -> ODR |=  (1U << 2);
			}
			else if(second % 10 == 8)//1000
			{
				GPIOB -> ODR |=  (1U << 0);
				GPIOB -> ODR &=~ (1U << 1);
				GPIOB -> ODR &=~ (1U << 2);

			}
			else if(second % 10 == 9)//1001
			{
				GPIOB -> ODR |=  (1U << 0);
				GPIOB -> ODR &=~ (1U << 1);
				GPIOB -> ODR &=~ (1U << 2);
			}

}
