
//* includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"
#include <stdint.h>
#include <stdio.h>

//* defines ------------------------------------------------------------------*/
#ifndef ROCKETBASICS_H_
#define ROCKETBASICS_H_
#endif /* ROCKETBASICS_H_ */

#define AHB1_BASE 0x40020000
#define STD_CLOCK 16000000
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0
#define __io volatile uint32_t
#define SEC_TICKS 16000


//delay
void delay(int);
//Inicia monitor serial
void rocketSerialBegin(uint32_t);
//Inicia monitor serial duplex
void rocketSerialDuplexBegin(uint32_t);
//Lê caracteres do monitor serial
char SerialRead();
//Seta pinMode
int pinMode(char, uint8_t, uint8_t);
//Escreve no pino digital
int digitalWrite(char, uint8_t, uint8_t);
//Lê do pino digital
uint8_t digitalRead(char, uint8_t);




