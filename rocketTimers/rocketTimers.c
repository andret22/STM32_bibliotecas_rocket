#include "rocketTimers.h"
#include "system_stm32f7xx.h"

/*
 *  TIMER 2
 */
uint32_t TIM2_Enable(uint32_t time, uint32_t pr){
	//Ativa clock para APB1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	//Prescaler
	 LL_TIM_SetPrescaler (TIM2, pr-1);
	 //Auto-reload
	 LL_TIM_SetAutoReload(TIM2, time-1);
	 //Ativa o timer
	 LL_TIM_EnableCounter(TIM2);

	 return STATUS_OK;
}

uint32_t TIM2_Enable_IT(uint32_t time, uint32_t prescaler, uint32_t prio){
	//Ativa clock para APB1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	//Prescaler
	 LL_TIM_SetPrescaler (TIM2, prescaler-1);
	 //Auto-reload
	 LL_TIM_SetAutoReload(TIM2, time-1);
	 //Ativa o timer
	 LL_TIM_EnableCounter(TIM2);

	 //Ativa interrpção
	 LL_TIM_EnableIT_UPDATE(TIM2);
	 //Seta prioridade da interrupção
	 NVIC_SetPriority(TIM2_IRQn, prio);
	 //ativa handler do NVIC
	 NVIC_EnableIRQ(TIM2_IRQn);

	 return STATUS_OK;
}

uint32_t TIM2_Elapsed(){
	if(TIM2->SR & (1U<<0)){
		LL_TIM_ClearFlag_UPDATE(TIM2);
		return 1;
	}else{
		return 0;
	}
}

/*
 * TIMER 3
 */

uint32_t TIM3_Enable(uint32_t time, uint32_t pr){
	//Ativa clock para APB1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	//Prescaler
	 LL_TIM_SetPrescaler (TIM3, pr-1);
	 //Auto-reload
	 LL_TIM_SetAutoReload(TIM3, time-1);
	 //Ativa o timer
	 LL_TIM_EnableCounter(TIM3);

	 return STATUS_OK;
}

uint32_t TIM3_Enable_IT(uint32_t time, uint32_t prescaler, uint32_t prio){
	//Ativa clock para APB1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	//Prescaler
	 LL_TIM_SetPrescaler (TIM3, prescaler-1);
	 //Auto-reload
	 LL_TIM_SetAutoReload(TIM3, time-1);
	 //Ativa o timer
	 LL_TIM_EnableCounter(TIM3);

	 //Ativa interrpção
	 LL_TIM_EnableIT_UPDATE(TIM3);
	 //Seta prioridade da interrupção
	 NVIC_SetPriority(TIM3_IRQn, prio);
	 //ativa handler do NVIC
	 NVIC_EnableIRQ(TIM3_IRQn);

	 return STATUS_OK;
}

uint32_t TIM3_Elapsed(){
	if(TIM3->SR & (1U<<0)){
		LL_TIM_ClearFlag_UPDATE(TIM3);
		return 1;
	}else{
		return 0;
	}
}

/*
 * TIMER 4
 */

uint32_t TIM4_Enable(uint32_t time, uint32_t pr){
	//Ativa clock para APB1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	//Prescaler
	 LL_TIM_SetPrescaler (TIM4, pr-1);
	 //Auto-reload
	 LL_TIM_SetAutoReload(TIM4, time-1);
	 //Ativa o timer
	 LL_TIM_EnableCounter(TIM4);

	 return STATUS_OK;
}

uint32_t TIM4_Enable_IT(uint32_t time, uint32_t prescaler, uint32_t prio){
	//Ativa clock para APB1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	//Prescaler
	 LL_TIM_SetPrescaler (TIM4, prescaler-1);
	 //Auto-reload
	 LL_TIM_SetAutoReload(TIM4, time-1);
	 //Ativa o timer
	 LL_TIM_EnableCounter(TIM4);

	 //Ativa interrpção
	 LL_TIM_EnableIT_UPDATE(TIM4);
	 //Seta prioridade da interrupção
	 NVIC_SetPriority(TIM4_IRQn, prio);
	 //ativa handler do NVIC
	 NVIC_EnableIRQ(TIM4_IRQn);

	 return STATUS_OK;
}

uint32_t TIM4_Elapsed(){
	if(TIM4->SR & (1U<<0)){
		LL_TIM_ClearFlag_UPDATE(TIM3);
		return 1;
	}else{
		return 0;
	}
}

/*
 * TIMER 5
 */

uint32_t TIM5_Enable(uint32_t time, uint32_t pr){
	//Ativa clock para APB1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
	//Prescaler
	 LL_TIM_SetPrescaler (TIM5, pr-1);
	 //Auto-reload
	 LL_TIM_SetAutoReload(TIM5, time-1);
	 //Ativa o timer
	 LL_TIM_EnableCounter(TIM5);

	 return STATUS_OK;
}

uint32_t TIM5_Enable_IT(uint32_t time, uint32_t prescaler, uint32_t prio){
	//Ativa clock para APB1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
	//Prescaler
	 LL_TIM_SetPrescaler (TIM5, prescaler-1);
	 //Auto-reload
	 LL_TIM_SetAutoReload(TIM5, time-1);
	 //Ativa o timer
	 LL_TIM_EnableCounter(TIM5);

	 //Ativa interrpção
	 LL_TIM_EnableIT_UPDATE(TIM5);
	 //Seta prioridade da interrupção
	 NVIC_SetPriority(TIM5_IRQn, prio);
	 //ativa handler do NVIC
	 NVIC_EnableIRQ(TIM5_IRQn);

	 return STATUS_OK;
}

uint32_t TIM5_Elapsed(){
	if(TIM5->SR & (1U<<0)){
		LL_TIM_ClearFlag_UPDATE(TIM3);
		return 1;
	}else{
		return 0;
	}
}


void TestLed_Init(){
	//Habilita clock e coloca PD7 como output
	//Clock for AHB1
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	//PinMode to AF
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7,LL_GPIO_MODE_OUTPUT);
	//AF to 2
	//LL_GPIO_SetAFPin_0_7 (GPIOB, LL_GPIO_PIN_7,LL_GPIO_AF_2);
}

/*
 *  Handlers
 *
 */

__WEAK void TIM2_IRQHandler(){
	//Faça algo aqui
	LL_TIM_ClearFlag_UPDATE(TIM2);
	LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_7);
}

__WEAK void TIM3_IRQHandler(){
	//Faça algo aqui
	LL_TIM_ClearFlag_UPDATE(TIM3);
	LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_7);
}

__WEAK void TIM4_IRQHandler(){
	//Faça algo aqui
	LL_TIM_ClearFlag_UPDATE(TIM4);
	LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_7);
}

__WEAK void TIM5_IRQHandler(){
	//Faça algo aqui
	LL_TIM_ClearFlag_UPDATE(TIM5);
	LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_7);
}

