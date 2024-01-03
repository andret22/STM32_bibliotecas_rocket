#include "rocketLoRa.h"
#include "rocketBasics.h"
/*
 * rocketLoRa.c
 *
 *  Created on: Dec 27, 2023
 *      Author: andre
 */
//Global variables
LoraResult* resultset;
uint8_t global_range;
char stop;
uint8_t IRQen = 0;

LoraResult* list_init(){
	return NULL;
}

LoraHandler* lora_init(USART_TypeDef* usart){

	resultset = list_init();

	LoraHandler* newH = (LoraHandler*)malloc(sizeof(LoraHandler));

	newH->usart = usart;
	newH->boudrate = UART_9600;
	newH->datarate = DATARATE_2D4K;
	newH->freq = 81;
	newH->mode = DATARATE_2D4K;
	newH->parity = PARITY_8N1;
	newH->tpower = POWER_22dBm;
	newH->worc = WOR_500;

	return newH;
}

void free_list(LoraResult** rs){
	LoraResult* aux;
	while((*rs) != NULL){
		aux = (*rs)->next;
		free(*rs);
		*rs = aux;
	}
}

//TO-DO enable interrupt dynamicaly
void interrupt_en(LoraHandler* lh){
	LL_USART_EnableIT_RXNE(lh->usart);
	NVIC_SetPriority(UART4_IRQn, 1);
	NVIC_EnableIRQ(UART4_IRQn);

}

LoraResult* lora_read(LoraHandler* h, uint8_t addr, uint8_t range){

	global_range = range + 3;

	//Free previous alocated list
	LoraResult* aux;
	while(resultset != NULL){
		aux = resultset->next;
		free(resultset);
		resultset = aux;
	}

	//Enables interrupt
	LL_USART_EnableIT_RXNE(h->usart);
	NVIC_SetPriority(UART4_IRQn, 1);
	NVIC_EnableIRQ(UART4_IRQn);

	//Transmit read request
	char data[3] = {0xC1, addr, range};

	UART4->CR1 &=~ (1U<<3);
	UART4->CR1 |= (1U<<3);
	while(!(UART4->ISR & (1U<<21))){}

	for (int i = 0; i < sizeof(data); i++) {
		h->usart->TDR = data[i];
		while(!(UART4->ISR & (1U<<6))){}
	}

	//Wait form awnser
	while(global_range > 0){}
	return resultset;
}


LoraResult* lora_write(LoraHandler* h, uint8_t addr, uint8_t range, uint8_t* content){

	global_range = range + 3;

	if(resultset != NULL){
		//Free previous alocated list
		free_list(&resultset);
	}

	//Enables interrupt
	interrupt_en(h);

	char data[3] = {0xC0, addr, range};

	//Enables transmiter
	UART4->CR1 &=~ (1U<<3);
	UART4->CR1 |= (1U<<3);
	while(!(UART4->ISR & (1U<<21))){}

	//Transmits data
	for (int i = 0; i < sizeof(data); i++) {
		h->usart->TDR = data[i];
		while(!(UART4->ISR & (1U<<6))){}
	}
	for (int i = 0; i < range; i++) {
		h->usart->TDR = *content;
		while(!(UART4->ISR & (1U<<6))){}
		content++;
	}

	//Wait form awnser
	while(global_range > 0){}

	return resultset;
}

LoraResult* lora_receive(LoraHandler* h, char stopc){

	if(resultset != NULL){
		//Free previous alocated list
		free_list(&resultset);
	}

	global_range = 7;


	interrupt_en(h);

	//Wait form awnser
	while(global_range > 0){}

	return resultset;

}

int lora_transmit(LoraHandler* h, char* buffer, size_t size_of_buffer){

	int bytes_send = 0;
	h->usart->CR1 |= (1U<<3);
	for(int i = 0; i<size_of_buffer; i++){
		while(!((1u<<7) & h->usart->ISR)){}
		h->usart->TDR = *buffer;
		while(!((1u<<6) & h->usart->ISR)){}
		buffer++;
		bytes_send++;
	}

	return bytes_send;
}



void UART4_IRQHandler(){

	uint8_t data = UART4->RDR;



	//Fixed size transmission
	if(global_range-- > 0){
		if(resultset == NULL){

			resultset = (LoraResult*)malloc(sizeof(LoraResult));
			resultset->data = data;
			resultset->next = NULL;
		}else if (resultset->next == NULL){

			LoraResult* novo = (LoraResult*)malloc(sizeof(LoraResult));
			novo->data = data;
			novo->next = NULL;
			resultset->next = novo;
		}else{

			LoraResult* aux = resultset;
			while(resultset->next != NULL){
				resultset = resultset->next;
			}
			LoraResult* novo = (LoraResult*)malloc(sizeof(LoraResult));
			novo->data = data;
			novo->next = NULL;
			resultset->next = novo;
			resultset = aux;
		}


	}else{
		NVIC_DisableIRQ(UART4_IRQn);
		LL_USART_DisableIT_RXNE(UART4);
	}
}












