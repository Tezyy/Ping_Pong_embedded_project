#ifndef UART_H
#define UART_H

void USART_Init(unsigned int ubrr); // Function to initialize UART communication
void USART_Transmit(unsigned char data); // Function to transmit a character over UART
unsigned char USART_Receive(void); // Function to receive a character via UART
int uart_putchar(char c, FILE *stream); // Function to send a character through UART for printf support
void init_printf(void); // Function to initialize printf to use UART

#endif /* UART_H */
