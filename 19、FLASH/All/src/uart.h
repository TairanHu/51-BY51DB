#ifndef UART_H
#define UART_H
#include "includes.h"

void Uart_Init(short brt);
void UartSentChar(uchar ch);
void UartSendStr(uchar *ch);
void Uart_SendNum(int num);





#endif