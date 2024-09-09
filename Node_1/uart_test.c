/*Test to verify the driver (copy-paste in main to try)*/
int main(void) 
{
    USART_Init(MYUBRR);
  
    /*char message[] = "Test UART\n"; 
    for (int i = 0; message[i] != '\0'; i++) 
    {
        USART_Transmit(message[i]); 
    }*/

    while (1)
    {
        // Transmit a character (echo back)
        unsigned char received = USART_Receive(); // Receive data
        USART_Transmit(received);  // Send it back to the terminal (echo)
    }
  
  return 0;
}
/*To test this, connect your ATmega162 via a serial connection to your PC.
  Open a terminal program (like PuTTY or TeraTerm), set it to the correct COM port and baud rate (9600),
  and type characters. The characters should be echoed back.*/
