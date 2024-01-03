#include <rocketADC.h>


void ADC1_10_Init(){
	//Habilita clock para ADC1
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
	//Habilita clock para porta B
	LL_AHB1_GRP1_EnableClock (LL_AHB1_GRP1_PERIPH_GPIOC);
	//PC0 para modo analógico
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG);
	//Gatilho de conversão pro software
	LL_ADC_REG_SetTriggerSource (ADC1, LL_ADC_REG_TRIG_SOFTWARE);
	//Rank de converão
	LL_ADC_REG_SetSequencerRanks (ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_10);
	//Tamanho da fila de conversão
	LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
	//Inicia ADC1_CH10
	LL_ADC_Enable(ADC1);
}

uint8_t ADC1_10_Single32_HasFinished(){
	//Checa se a conversão terminou
	if(ADC1->SR & (1U<<1)){
		return 1;
	}else{
		return 0;
	}
}

void ADC1_10_Single32_Start(){
	//Inicia conversão
	LL_ADC_REG_StartConversionSWStart (ADC1);
}

uint32_t ADC1_10_ReadValue(){
	return LL_ADC_REG_ReadConversionData32 (ADC1);
}


