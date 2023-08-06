#include "rocketI2C.h"

void rocketI2C2_init(){

	//Ativar clock para porta B
	RCC->AHB1ENR |= (1U<<1);

	//Coloca PB10 E PB11 em modo de função alternada
	//PB10
	GPIOB->MODER &=~ (1U<<20);
	GPIOB->MODER |= (1U<<21);
	//PB11
	GPIOB->MODER &=~ (1U<<22);
	GPIOB->MODER |= (1U<<23);

	//Coloca PB10 e PB11 em I2C
	//PB10
	GPIOB->AFR[1] |= (1U<<10);
	//PB11
	GPIOB->AFR[1] |= (1U<<14);

	//Deixar PB10 E PB11 em modo de dreno aberto
	GPIOB->OTYPER |= (1U<<10);
	GPIOB->OTYPER |= (1U<<11);

	//Colocar PB10 e PB11 em PULL UP
	//PB10
	GPIOB->PUPDR |= (1U<<20);
	GPIOB->PUPDR &=~ (1U<<21);
	//PB11
	GPIOB->PUPDR |= (1U<<22);
	GPIOB->PUPDR &=~ (1U<<23);

	//Habilita clock para I2C2 em APB1
	RCC->APB1ENR |= (1U<<22);

	//Reseta registradores do I2C2 por meio do SoftwareReset
	I2C2->CR1 &=~ (1U<<0);
	for(int i = 0; i<10; i++){}
	I2C2->CR1 &=~ (1U<<1);

	//Setar clock para I2C2 16MHz
	I2C2->TIMINGR = 0x10811E25;

	//Inicia periférico
	I2C2->CR1 |= (1U<<0);
}

void I2C2_read(char saddr, char maddr, char* data){

	__attribute__((unused)) volatile int tmp;

	//Se i2c estiver ocupado, aguarde...
	while(I2C2->ISR & (1U<<15)){}

	//Cria pulso da consição de início
	I2C2->CR2 |= (1U<<13);
	for (volatile int delay = 0; delay < 1000; delay++) {}

	//Transmite endereço do slave
	I2C2->TXDR = (saddr << 1);

	//Aguarda que os dados sejam enviados
	while(!(I2C2->ISR & (1U<<0))){}

	//Checa se o slave reconhece o endereço
	if (I2C2->ISR & (1U<<4)) {
		return;
	}

	tmp = I2C2->ISR;

	//Evia endereço de memória a ser lido
	I2C2->TXDR = maddr;

	//Aguarda que os dados sejam enviados
	while(!(I2C2->ISR & (1<<0))){}

	//Checa se o slave reconhece o endereço
	if (I2C2->ISR & (1U<<4)) {
		return;
	}

	tmp = I2C2->ISR;

	//Cria pulso da condição de reinício
	I2C2->CR2 |= (1U<<13);
	for(volatile int delay = 0; delay < 1000; delay++) {}

	//Se i2c estiver ocupado, aguarde...
	while(I2C2->ISR & (1U<<15)){}

	//Transmite o enderaço do slave + leitura
	I2C2->TXDR = (saddr << 1 | 1);

	//Aguarda que os dados sejam enviados
	while(!(I2C2->ISR & (1<<0))){}

	//Checa se o slave reconhece o endereço
	if (I2C2->ISR & (1U<<4)) {
		return;
	}

	tmp = I2C2->ISR;

	//Gera condição de parada
	I2C2->CR2 |= (1U<<14);

	//Aguarda receber informação
	while(I2C2->ISR & (1U<<2)){}

	*data = I2C2->RXDR;
}

void I2C2_burstRead(char saddr, char maddr, char* data, int n){

	__attribute__((unused)) volatile int tmp;

		//Se i2c estiver ocupado, aguarde...
		while(I2C2->ISR & (1U<<15)){}

		//Cria pulso da consição de início
		I2C2->CR2 |= (1U<<13);
		for (volatile int delay = 0; delay < 1000; delay++) {}

		//Transmite endereço do slave
		I2C2->TXDR = (saddr << 1);

		//Aguarda que os dados sejam enviados
		while(!(I2C2->ISR & (1<<0))){}

		//Checa se o slave reconhece o endereço
		if (I2C2->ISR & (1U<<4)) {
			return;
		}

		tmp = I2C2->ISR;

		//Evia endereço de memória a ser lido
		I2C2->TXDR = maddr;

		//Aguarda que os dados sejam enviados
		while(!(I2C2->ISR & (1<<0))){}

		//Checa se o slave reconhece o endereço
		if (I2C2->ISR & (1U<<4)) {
			return;
		}

		tmp = I2C2->ISR;

		//Cria pulso da condição de reinício
		I2C2->CR2 |= (1U<<13);
		for(volatile int delay = 0; delay < 1000; delay++) {}

		//Se i2c estiver ocupado, aguarde...
		while(I2C2->ISR & (1U<<15)){}

		//Transmite o enderaço do slave + leitura
		I2C2->TXDR = (saddr << 1 | 1);

		//Aguarda que os dados sejam enviados
		while(!(I2C2->ISR & (1<<0))){}

		//Checa se o slave reconhece o endereço
		if (I2C2->ISR & (1U<<4)) {
			return;
		}

		tmp = I2C2->ISR;

		//Gera condição de parada
		I2C2->CR2 |= (1U<<14);

		//Aguarda receber informação
		while(I2C2->ISR & (1U<<2)){}

		while(n > 0U){
		    /*if one byte*/
		    if(n == 1U) {

		    	//Gera condição de parada
		    	I2C2->CR2 |= (1U<<14);

		    	while(I2C2->ISR & (1U<<2)){}

		    	*data++ = I2C2->RXDR;
		        break;
		    }else {

		    	while(I2C2->ISR & (1U<<2)){}

		    	*data++ = I2C2->RXDR;

		        n--;
		    }
		}
}

void I2C2_burstWrite(char saddr, char maddr, char* data, int n) {

	// Preserve the rest of the CR2 register and update the NBYTES field to 1 byte
    I2C2->CR2 = (I2C2->CR2 & ~(0xFFU << 16)) | (1U << 16);

    // Se i2c estiver ocupado, aguarde...
    while (I2C2->ISR & (1U << 15)) {}

    //Flush em TXDR
    I2C2->ISR |= (1U<<0);

    // Cria pulso da consição de início
    I2C2->CR2 |= (1U << 13);

    // Transmite endereço do slave
    I2C2->TXDR = (saddr << 1);

    //Gera condição de parada
    I2C2->CR2 |= (1U<<14);

    // Aguarda que os dados sejam enviados
    while (!(I2C2->ISR & (1 << 0))) {}

    // Check for ACK failure after address transmission
    if (I2C2->ISR & (1U << 4)) {
        // ACK failure, handle error or return if necessary
        return;
    }

    //Zera registrador
    I2C2->ISR = 0;

    // Aguarda que os dados sejam enviados
    while (I2C2->ISR & (1 << 0)) {}

    // Evia endereço de memória a ser lido
    I2C2->TXDR = maddr;



    for (int i = 0; i < n; i++) {
        // Wait for TXIS flag (data register empty)
        while (I2C2->ISR & (1U << 1)) {}

        I2C2->TXDR = *data++;

        if (I2C2->ISR & (1U << 4)) {
             // ACK failure, handle error or return if necessary
             return;
        }

    }

    // Wait for Transfer Complete
    while (!(I2C2->ISR & (1U << 6))) {}


    // Clear STOP bit
    I2C2->CR2 &= ~(1U << 14);
}

void I2C2_burstRead32(char saddr, char maddr, uint32_t* data, int n){

	__attribute__((unused)) volatile int tmp;

		//Se i2c estiver ocupado, aguarde...
		while(I2C2->ISR & (1U<<15)){}

		//Cria pulso da consição de início
		I2C2->CR2 |= (1U<<13);
		for (volatile int delay = 0; delay < 1000; delay++) {}

		//Se i2c estiver ocupado, aguarde...
		while(I2C2->ISR & (1U<<15)){}

		//Transmite endereço do slave
		I2C2->TXDR = (saddr << 1);

		//Transmite condição de parada
		I2C2->CR2 |= (1U << 14);

		//Aguarda que os dados sejam enviados
		while(!(I2C2->ISR & (1<<0))){}

		//Checa se o slave reconhece o endereço
		if (I2C2->ISR & (1U<<4)) {
			return;
		}

		tmp = I2C2->ISR;

		//Evia endereço de memória a ser lido
		I2C2->TXDR = maddr;

		//Aguarda que os dados sejam enviados
		while(!(I2C2->ISR & (1<<0))){}

		//Checa se o slave reconhece o endereço
		if (I2C2->ISR & (1U<<4)) {
			return;
		}

		tmp = I2C2->ISR;

		//Cria pulso da condição de reinício
		I2C2->CR2 |= (1U<<13);
		for(volatile int delay = 0; delay < 1000; delay++) {}

		//Se i2c estiver ocupado, aguarde...
		while(I2C2->ISR & (1U<<15)){}

		//Transmite o enderaço do slave + leitura
		I2C2->TXDR = (saddr << 1 | 1);

		//Aguarda que os dados sejam enviados
		while(!(I2C2->ISR & (1<<0))){}

		//Checa se o slave reconhece o endereço
		if (I2C2->ISR & (1U<<4)) {
			return;
		}

		tmp = I2C2->ISR;

		//Gera condição de parada
		I2C2->CR2 |= (1U<<14);

		//Aguarda receber informação
		while(I2C2->ISR & (1U<<2)){}

		while(n > 0U){
		    /*if one byte*/
		    if(n == 1U) {

		    	//Gera condição de parada
		    	I2C2->CR2 |= (1U<<14);

		    	while(I2C2->ISR & (1U<<2)){}

		    	*data++ = I2C2->RXDR;
		        break;
		    }else {

		    	while(I2C2->ISR & (1U<<2)){}

		    	*data++ = I2C2->RXDR;

		        n--;
		    }
		}
}
