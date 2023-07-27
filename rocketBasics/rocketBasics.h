
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
/** Variáveis globais *********************************************************************/

volatile uint32_t millis_count = 0;

/** Funções *********************************************************************/
/** Delay e timers ------------------------------------------------------------------------*/

void millis_init() {
    // Ativa o click para TIM2 em APB1
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Número de ticks do clock para incrementar o timer
    TIM2->PSC = (STD_CLOCK / 1000) - 1;

    //Reseta valor do timer para 1 milisegundo
    TIM2->ARR = 1;

    // Ativa as interrupções
    TIM2->DIER |= TIM_DIER_UIE;

    // Ativa o timer
    TIM2->CR1 |= TIM_CR1_CEN;

    // Usa o NVIC para ativar interrupções globais com o timer
    NVIC_EnableIRQ(TIM2_IRQn);
}

// Handler do timer2
void TIM2_IRQHandler() {

    if (TIM2->SR & TIM_SR_UIF) {

        //Limpra a flag de interrupção
        TIM2->SR &= ~TIM_SR_UIF;

        //Incrementa o contador em 2
        millis_count++;
        millis_count++;
    }
}

uint32_t millis() {
    return millis_count;
}

void delay(int time){
	SysTick->LOAD = SEC_TICKS;
	SysTick->VAL = 0;

	//Ativa Systick e usa clock interno (alterar caso usar cristal externo)
	SysTick->CTRL = (1U<<0) | (1U<<2);

	for(int i=0; i<time ; i++){
		//Aguarda a flag de tick
		while((SysTick->CTRL &  (1U<<16)) == 0){}
	}

	//Desativa o Systick
	SysTick->CTRL = 0;
}

/** SERIAL USART3 SETUP ----------------------------------------------------------*/

static uint32_t compute_uart_div(uint32_t perClock, uint32_t baudRate) {
    return perClock / baudRate;
}

static void uart_set_boudRate(USART_TypeDef *usartTx, uint32_t perClock, uint32_t boudRate){

	usartTx->BRR = compute_uart_div(perClock, boudRate);
}

__attribute__((unused)) static void rocketSerialDuplexBegin(uint32_t boudRate){

	//Ativa clock na trilha AHB1 para a porta D
	RCC->AHB1ENR |= (1U<<3);
	//Settar PD8 para modo de função alternada
	GPIOD->MODER |= (1U<<17);
	GPIOD->MODER &=~ (1U<<16);
	//Settar PD9 para modo de função alternada
	GPIOD->MODER |= (1U<<19);
	GPIOD->MODER &=~ (1U<<18);
	//Settar registrador de função alternada de PD8 para AF7
	GPIOD->AFR[1] |= (1U<<0);
	GPIOD->AFR[1] |= (1U<<1);
	GPIOD->AFR[1] |= (1U<<2);
	GPIOD->AFR[1] &=~ (1U<<3);
	//Settar registrador de função alternada de PD9 para AF7
	GPIOD->AFR[1] |= (1U<<4);
	GPIOD->AFR[1] |= (1U<<5);
	GPIOD->AFR[1] |= (1U<<6);
	GPIOD->AFR[1] &=~ (1U<<7);
	//Usart3 ---
	//Ativa clock para USART3
	RCC->APB1ENR |= (1U<<18);
	//Settar boudRate
	uart_set_boudRate(USART3,STD_CLOCK, boudRate);
	//Direção da transmição
	USART3->CR1 = (1U<<3);
	USART3->CR1 = (1U<<2);
	//Habilitar UART
	USART3->CR1 |= (1U<<0);
}

__attribute__((unused)) static void rocketSerialBegin(uint32_t boudRate){

	//Pin ---
	//Ativa clock na trilha AHB1 para a porta D
	RCC->AHB1ENR |= (1U<<3);
	//Settar PD8 para modo de função alternada
	GPIOD->MODER |= (1U<<17);
	GPIOD->MODER &=~ (1U<<16);
	//Settar registrador de função alternada para AF7
	GPIOD->AFR[1] |= (1U<<0);
	GPIOD->AFR[1] |= (1U<<1);
	GPIOD->AFR[1] |= (1U<<2);
	GPIOD->AFR[1] &=~ (1U<<3);

	//Usart3 ---
	//Ativa clock para USART3
	RCC->APB1ENR |= (1U<<18);
	//Settar boudRate
	uart_set_boudRate(USART3,STD_CLOCK, boudRate);
	//Direção da transmição
	USART3->CR1 = (1U<<3);
	//Habilitar UART
	USART3->CR1 |= (1U<<0);
}

/** SERIAL USART3 Write ----------------------------------------------------------*/

__attribute__((unused)) static void usart_3_write(int ch){

	//Se registrador vaziu
	while(!((1u<<7) & USART3->ISR)){}

	//Limpa registrador de transmição e substitui por mensagem desejada
	USART3->TDR = (ch & 0xFF);
}


__attribute__((unused)) static int Serial_println(char* data){
	int nBit;
	nBit = printf(data);
	USART3->TDR = ('\n' & 0xFF);
	USART3->TDR = ('\r' & 0xFF);
	return nBit++;
}

__attribute__((unused)) static int Serial_print(char* data){
	int nBit;
	nBit = printf(data);
	USART3->TDR = ('\r' & 0xFF);
	return nBit++;
}

int __io_putchar(int ch){
	usart_3_write(ch);
	return ch;
}


/** SERIAL USART3 Read ----------------------------------------------------------*/


__attribute__((unused)) static char usart_3_read(){

	//Se registrador não contem informação
	while(!(USART3->ISR & (1U<<5))){}

	//retorna mensagem
	return USART3->RDR;

}

/** GPIO **************************************************************************/

//TO-DO

__attribute__((unused)) static int pinMode(char port, uint8_t pin, uint8_t mode) {
    // Checar se o pino é válido
    if (port < 'A' || port > 'K' || pin > 15 || pin < 0) {
        return 0;
    }

    // Calcular o offset do port
    uint8_t offset = port - 'A';

    // Habilitar clock na porta correta
    RCC->AHB1ENR |= (1U << offset);

    //Apontar para a porta correta
    GPIO_TypeDef* gpioPort = (GPIO_TypeDef*)(GPIOA_BASE + (offset * 0x0400));


    if(mode == OUTPUT){
    	// Configurar o modo correto no pino desejado
    	gpioPort->MODER |= (1U<<(pin*2));
    	gpioPort->MODER &=~ (1U<<((pin*2)+1));
    }else if (mode == INPUT) {
        // Configurar o modo de entrada no pino desejado
    	gpioPort->MODER &=~ (1U<<(pin*2));
    	gpioPort->MODER &=~ (1U<<((pin*2)+1));
    }else {
       // Modo inválido
       return 0;
    }

    return 1;
}

__attribute__((unused)) static int digitalWrite(char port, uint8_t pin, uint8_t mode) {
    // Checar se o pino é válido
    if (port < 'A' || port > 'K' || pin > 15 || pin < 0) {
        return 0;
    }

    // Calcular o offset da porta
    uint8_t offset = port - 'A';

    RCC->AHB1ENR |= (1U << offset);

    // Obter o endereço do registrador de saída (ODR) do GPIO correspondente
    GPIO_TypeDef* gpioPort = (GPIO_TypeDef*)(GPIOA_BASE + (offset * 0x0400));
    uint32_t odrBit = (1U << pin);

    // Escrever no registrador de saída (ODR) para definir o estado do pino
    if (mode == HIGH) {
        gpioPort->BSRR = odrBit;  // Set the pin to HIGH
    } else if (mode == LOW) {
        gpioPort->BSRR = odrBit << 16;  // Set the pin to LOW
    }

    return 1;
}

__attribute__((unused)) static uint8_t digitalRead(char port, uint8_t pin){

	 // Checar se o pino é válido
	 if (port < 'A' || port > 'K' || pin > 15 || pin < 0) {
	     return 0;
	 }

	 // Calcular o offset da porta
	 uint8_t offset = port - 'A';

	 //acessar o registrador de dados de input
	 GPIO_TypeDef* gpioPort = (GPIO_TypeDef*)(GPIOA_BASE + (offset * 0x0400));

	 if(gpioPort->IDR & (1U<<pin)){
		 return 1;
	 }else{
		 return 0;
	 }

}

/** ADC3 ----------------------------------------------------------*/
//Conversão única
void ADC_init(){
	//PF9
	//Canal 7

	//Habilida clock para ADC3 em APB2
	RCC->APB2ENR |= (1U<<10);

	//Habilita clock para GPIOF
	RCC->AHB1ENR |= (1U<<5);

	//Pino PF9 para modo analógico
	GPIOF->MODER |= (1U<<18);
	GPIOF->MODER |= (1U<<19);

	//Configura registrador de sequência do ADC3
	ADC3->SQR3 = (00111U<<0);

	//Configura tamanho da conversão (número de canais a serem lidos)
	ADC3->SQR1 = 0x00;

	//Ativa o ADC3
	ADC3->CR2 |= (1U<<0);
}

void ADC_start_single_conversion(){
	//Ativa conversão pro software
	ADC3->CR2 |= (1U<<30);
}

void ADC_start_continous_conversion(){
	//Ativa conversão pro software
	ADC3->CR2 |= (1U<<1);
	ADC3->CR2 |= (1U<<30);
}

uint32_t ADC_read(){

	//Aguarde a conversão estar completa
	while(!(ADC3->SR & (1U<<1))){}

	return ADC3->DR;
}


