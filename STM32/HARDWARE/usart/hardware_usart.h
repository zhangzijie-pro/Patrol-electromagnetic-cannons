#ifndef __husart_h__
#define __husart_h__

//----------------------- Include files ------------------------//

//--------------------------- Define ---------------------------//
#define UART_BUFFER_SIZE 100

//------------------------- Data struct ------------------------//
typedef struct{

	char receive_buffer[UART_BUFFER_SIZE];
	int counter;
 
	int receive_ok_flag;
	int baudrate;
	int error;
	int (* initialize)(unsigned long int);
	int (* send_string)(char *);
	int (* send_byte)(char);
	int (* send_buffer)(void *,int len);
	int (* printf)(const char * ,...);
}UART_T;

//----------------------- Extern function ----------------------//
extern UART_T usart4;
extern UART_T usart2;

//----------------------- Extern variable ----------------------//
#endif // __uart_h__
