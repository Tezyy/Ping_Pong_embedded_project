#include "uart.h"

void main(void)
{
  begin
  USART_Init(MYUBRR); // Initialisation de l'USART avec une vitesse de 9600 baud
  link_printf(); // Lier la fonction printf à l'USART
  while(1)
  {
    NULL;
  }
}
