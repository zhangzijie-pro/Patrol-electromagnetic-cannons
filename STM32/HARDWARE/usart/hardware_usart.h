#ifndef __husart_h__
#define __husart_h__

//----------------------- Include files ------------------------//

//--------------------------- Define ---------------------------//
#define UART_BUFFER_SIZE 100

//------------------------- Data struct ------------------------//
char receive_buffer[UART_BUFFER_SIZE];
int counter;

int receive_ok_flag;
int baudrate;
int error;

//----------------------- Extern function ----------------------//


//----------------------- Extern variable ----------------------//
#endif // __uart_h__
