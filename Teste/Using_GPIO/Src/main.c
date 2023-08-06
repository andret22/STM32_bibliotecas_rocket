#include "rocketBasics.h"
#include "rocketI2C.h"
#include "rocketBMP280.h"


int main(){
	/* SETUP */
	rocketSerialBegin(9600);
	rocketI2C2_init();
	BMP280_reset();
	/*END SETUP*/
	while(1){
		/*LOOP*/
		printf("Ola\n\r");
		delay(500);
		/*END LOOP*/

	}
}

