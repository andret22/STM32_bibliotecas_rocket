#include"stm32f7xx_ll_bus.h"
#include"stm32f7xx_ll_GPIO.h"
#include"stm32f7xx_ll_tim.h"
#include "stm32f767xx.h"
#include "system_stm32f7xx.h"

#define STATUS_OK 1
#define TIM_TICK uint32_t

//Inicializa timer 2 (16 bits)
TIM_TICK TIM2_Enable(uint32_t, uint32_t);
//Inicializa timer 2 em modo de interrupção (16 bits)
TIM_TICK TIM2_Enable_IT(uint32_t, uint32_t, uint32_t);
//Checa se tim2
uint32_t TIM2_Elapsed();

//Inicializa timer 3 (16 bits)
TIM_TICK TIM3_Enable(uint32_t, uint32_t);
//Inicializa timer 3 em modo de interrupção (16 bits)
TIM_TICK TIM3_Enable_IT(uint32_t, uint32_t, uint32_t);
//Checa se tim2
uint32_t TIM3_Elapsed();

//Inicializa timer 4 (16 bits)
TIM_TICK TIM4_Enable(uint32_t, uint32_t);
//Inicializa timer 3 em modo de interrupção (16 bits)
TIM_TICK TIM4_Enable_IT(uint32_t, uint32_t, uint32_t);
//Checa se tim2
uint32_t TIM4_Elapsed();
//Habilida LED de teste

//Inicializa timer 5 (16 bits)
TIM_TICK TIM5_Enable(uint32_t, uint32_t);
//Inicializa timer 3 em modo de interrupção (16 bits)
TIM_TICK TIM5_Enable_IT(uint32_t, uint32_t, uint32_t);
//Checa se tim2
uint32_t TIM5_Elapsed();
//Habilida LED de teste

//Habilida LED de teste
void TestLed_Init();


