//libraries

//application

//controller
#include "layer_controller/blink.hpp"
//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"

//circuit

int main(void)
{
	long long int time=0;
	Led0 led;
	Blink blink(led);
	blink.setup();
	blink.time(100);
	Serial0 serial;serial.setup(115200);
	Enc0 enc0;enc0.setup();
	Enc1 enc1;enc1.setup();
	Enc2 enc2;enc2.setup();
	Enc3 enc3;enc3.setup();
	Cw4 cw4;Blink blink0(cw4);blink0.setup();blink0.time(1000);
	Ccw4 ccw4;Blink blink1(ccw4);blink0.setup();blink1.time(100);
	while(1){
		blink.cycle();
		blink0.cycle();
		blink1.cycle();
		if(millis()-time>=100){
			time=millis();
			//serial.printf("%d, %d, %d, %d\n\r",enc0.count(),enc1.count(),enc2.count(),enc3.count());
		}
	}
	return 0;
}
