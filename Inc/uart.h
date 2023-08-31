
#ifndef UART_H_
#define UART_H_
#include <stdint.h>

#include "stm32f0xx.h"

char uart2_read(void);
void uart2_rxtx_init(void);
void uart2_rx_interrupt_init(void);
void uart2_tx_interrupt_init(void);

#define ISR_RXNE		(1U << 5)
#define ISR_TXE 		(1U << 7)


#endif /* UART_H_ */
