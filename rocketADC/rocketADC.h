#ifndef ROCKETADC_H_
#define ROCKETADC_H_
#endif /* ROCKETADC_H_ */

#include"stm32f7xx_ll_bus.h"
#include"stm32f7xx_ll_GPIO.h"
#include"stm32f7xx_ll_ADC.h"
#include "stm32f7xx.h"

//PC0 - ADC1_IN10

//Habilita ADC1
void ADC1_10_Init();
//Inicia conversão 32 bits
void ADC1_10_Single32_Start();
//Verifica se a conversão terminou
uint8_t ADC1_10_Single32_HasFinished();
//Retorna valor da conversão
uint32_t ADC1_10_ReadValue();
