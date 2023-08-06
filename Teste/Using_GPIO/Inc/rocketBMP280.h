#include "rocketI2C.h"

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

} BMP280_trim;

/*** Defines ***/
#ifndef ROCKETBMP280_H_
#define ROCKETBMP280_H_
#endif /* ROCKETBMP280_H_ */
#define BMP280_ADDR		(0x76)

#define RESET_VALUE			(0xB6)
#define RESET_ADDR			(0xE0)


/*** Funções ***/
void BMP280_read_address (uint8_t);
void BMP280_write (uint8_t, char);
void BMP280_readTemperature (uint8_t);
void BMP280_readPressure (uint8_t);
void BMP280_reset();

