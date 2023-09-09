**Using the internal RTC of a STM32 Nucleo board I transmitted time to RealTerm using UART communication. This happens in a SysTick Timer ISR.**
 
**The user can:**
- check the date by pressing 'D' when terminal is connected 
- check the time by pressing 'T' when terminal is connected 
- set an alarm by pressing 'A' when terminal is connected

**This is implemented with the use of UART_RX interrupts**

- After reading the BCD Value of the RTC , the GPIO function sets the OD and MODE Registers for the GPIOs connected to the breadboard LEDs
- **Demonstration:** https://youtube.com/shorts/DG651NfuiZQ
- Now I will want to add, the possibility of setting up a timer and implement a tamper detection in the code.
