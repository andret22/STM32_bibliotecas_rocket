#include "rocketI2C.h"
#include "rocketBMP280.h"
/*** Structs ***/

typedef struct {
    uint16_t T1;
    int16_t  T2;
    int16_t  T3;
    uint16_t P1;
    int16_t  P2;
    int16_t  P3;
    int16_t  P4;
    int16_t  P5;
    int16_t  P6;
    int16_t  P7;
    int16_t  P8;
    int16_t  P9;

} BMP280_trim_TypeDef;

#define TRIM	((BMP280_trim_TypeDef*)0x88)

/*** Variáveis ***/
char data;
uint32_t data_rec[3];

/*** Funções ***/
void BMP280_read_address (uint8_t reg) {
	I2C2_read(BMP280_ADDR, reg, &data);
}

void BMP280_write (uint8_t reg, char value) {

	char data[1];
	data[0] = value;

	I2C2_burstWrite(BMP280_ADDR, reg, data, 1);
}

void BMP280_readTemperature (uint8_t reg) {
	I2C2_burstRead32(BMP280_ADDR, reg, data_rec, 3);
}

void BMP280_readPressure (uint8_t reg) {
	I2C2_burstRead32(BMP280_ADDR, reg,data_rec, 3);
}

void BMP280_reset(){
	BMP280_write(RESET_ADDR, RESET_VALUE);
}

