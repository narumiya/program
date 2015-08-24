//libraries

//application
#include "my_standard_io.h"
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
	Led0 led;Blink blink(led);blink.setup();blink.time(100);
	Serial0 serial;serial.setup(115200);
	Serial2 ps3;
	Enc0 enc0;enc0.setup();
	Enc1 enc1;enc1.setup();
	Enc2 enc2;enc2.setup();
	Enc3 enc3;enc3.setup();
	Cw7 cwPin;Blink blink0(cwPin);blink0.setup();blink0.time(1000);
	Ccw7 ccwPin;Blink blink1(ccwPin);blink0.setup();blink1.time(500);
	Pwm7 pwmPin;pwmPin.setupPwmOut(100000,0);
	A0 a0;a0.setupAnalogIn();
	A1 a1;a1.setupAnalogIn();
	A2 a2;a2.setupAnalogIn();
	A3 a3;a3.setupAnalogIn();
	A4 a4;a4.setupAnalogIn();

	while(1){
		blink.cycle();
		blink0.cycle();
		blink1.cycle();
		if(millis()-time>=500){
			time=millis();

			/*if(flag==0){
				pwmPin.pwmWrite(0.1);
				flag=1;
			}else if(flag==1){
				pwmPin.pwmWrite(1);
				flag=0;
			}*/


			//serial.printf("%d, %d, %d, %d\n\r",enc0.count(),enc1.count(),enc2.count(),enc3.count());
			//serial.printf("%.4f, %.4f, %.4f, %.4f, %.4f\n",a0.analogRead(),a1.analogRead(),a2.analogRead(),a3.analogRead(),a4.analogRead());

		}
	}
	return 0;
}
