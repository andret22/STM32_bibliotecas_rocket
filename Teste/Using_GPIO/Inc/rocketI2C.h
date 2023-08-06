//* includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"
#include <stdint.h>
#include <stdio.h>

/**** Defines  *****/
#ifndef ROCKETI2C_H_
#define ROCKETI2C_H_
#endif /* ROCKETI2C_H_ */

//I2C2
//PB10 -- CLK
//PB11 == SDA
/**** Funções  *****/

void rocketI2C2_init();
void I2C2_read(char saddr, char maddr, char* data);
void I2C2_burstRead(char saddr, char maddr, char* data, int n);
void I2C2_burstRead32(char saddr, char maddr, uint32_t* data, int n);
void I2C2_burstWrite(char saddr, char maddr, char* data, int n);
