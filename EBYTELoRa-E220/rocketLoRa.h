#include <stdint.h>
#include <stdlib.h>
#include "STM32F767xx.h"
#include "stm32f7xx_ll_usart.h"
#ifndef ROCKETLORA_H_
#define ROCKETLORA_H_

#endif /* ROCKETLORA_H_ */

//LoRa registers
#define	ADDH		0x00UL
#define	ADDL		0x01UL
#define	REG0		0x02UL
#define	REG1		0x03UL
#define	REG2		0x04UL
#define	REG3		0x05UL
#define	CRYPT_H		0x06UL
#define CRYPT_L		0x07UL
//Modes
#define MODE_NORMAL	0	//Defined through hardware
#define MODE_WOR_T	1	//Use pins M0 and 01
#define MODE_WOR_R	2
#define MODE_SLEEP	3
//BoudRate
#define	UART_1200	0
#define	UART_2400	1
#define	UART_4800	2
#define	UART_9600	3	//Default
#define	UART_19200	4
#define	UART_38400	5
#define	UART_57600	6
#define	UART_115200	7
//Parity
#define PARITY_8N1	0	//Default
#define	PARITY_801	1
#define	PARITY_8E1	2
//Air data rate
#define	DATARATE_2D4K	2	//Default
#define	DATARATE_4D8K	3
#define	DATARATE_9D6K	4
#define	DATARATE_19D2K	5
#define	DATARATE_38D4K	6
#define	DATARATE_62D5K	7
//Transmition power
#define	POWER_22dBm	0	//Default
#define	POWER_17dBm	1
#define	POWER_13dBm	2
#define	POWER_10dBm	3
//WOR Cycle
#define WOR_500		0	//Default
#define WOR_1000	1
#define WOR_1500	2
#define WOR_2000	3
#define WOR_2500	4
#define WOR_3000	5
#define WOR_3500	6
#define WOR_4000	7
//Transmission modes
#define NULL_TERMINATED 0
//Structs

struct loraHandler{

	USART_TypeDef * usart;
	uint8_t mode;
	uint8_t freq;	//Frequency is calculated as f = (850.125 + freq)Mz
					//freq goes from 0 to 81
					//Adding a number higher than 81 will result in freq = 81
					//Adding a number lower than 0 will result in freq = 0
					//Default is 81
	uint8_t boudrate;
	uint8_t parity;
	uint8_t datarate;
	uint8_t tpower;	//If power supply isn't a problem, keep at maximum
	uint8_t worc;	//Cycle T= (1+WOR)*500ms, the maximum is 4000ms. the minimum is 500ms; <-- Datasheet info
};

struct loraResult{
	uint8_t data;
	struct loraResult* next;
};

typedef struct loraResult LoraResult;
typedef struct loraHandler LoraHandler;

/* Functions  */

//Initialize the handler with the default values.
//THIS FUNCTION ONLY INITIALIZES THE LORA HANDLER, NOT THE UART PERIPHERAL
//MAKE SURE TO INITIALIZE THE UART CORRECTLY BEFORE CALLING THIS FUNCTION, OTHERWISE IT WILL NOT WORK
LoraHandler* lora_init(USART_TypeDef*);

/* This function read a specific range of registers and return the content to an array
*  Format will be:
*
 * 	Read flag	Starting addr	Range	Results
 *
 * 		C1			XX			  XX	...
 *
 *	Invalid format will be answered with FF FF FF
 */
LoraResult* lora_read(LoraHandler*, uint8_t, uint8_t);

/* This function writes in a specific register
*  Format will be:
*
 * 	Write flag	Starting addr	Range	Content
 *
 * 		C0			XX			  XX		XX
 *
 *	Invalid format will be answered with FF FF FF
 */
LoraResult* lora_write(LoraHandler*, uint8_t, uint8_t, uint8_t*);

//Transmits a message
int lora_transmit(LoraHandler*, char*, size_t);

//Receives a message
LoraResult* lora_receive(LoraHandler*, char);


