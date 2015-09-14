//libraries

//application
#include "layer_application/debug.hpp"
//controller
#include "layer_controller/blink.hpp"
#include "layer_controller/move.hpp"
//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"

//circuit
#include "circuit/md.hpp"
#include "circuit/dual_shock.hpp"

int main(void)
{
	long long int time=0;
	Led0 led;Blink blink0(led);blink0.setup();blink0.time(100);
	A0 a0;Blink blink1(a0);blink1.setup();blink1.time(100);
	Serial0 serial;serial.setup(115200);

	Serial1 serial1;
	Enc0 l;Enc1 r;Enc2 b;
	RobotCenter center(l,r,b);center.setup();
	Can0 can;
	DualShock ps3(serial1);
	ps3.setStickTolerance(0.1);
	//DualShock ps3(serial1);ps3.setup();
	/*Cw4 cw4;Ccw4 ccw4;Pwm4 pwm4;Md md4(cw4,ccw4,pwm4);
	Cw5 cw5;Ccw5 ccw5;Pwm5 pwm5;Md md5(cw5,ccw5,pwm5);
	Cw6 cw6;Ccw6 ccw6;Pwm6 pwm6;Md md6(cw6,ccw6,pwm6);
	Cw7 cw7;Ccw7 ccw7;Pwm7 pwm7;Md md7(cw7,ccw7,pwm7);*/
	CW0 cw4;CCW0 ccw4;Pwm0 pwm4;Md md4(cw4,ccw4,pwm4);
	CW1 cw5;CCW1 ccw5;Pwm1 pwm5;Md md5(cw5,ccw5,pwm5);
	CW2 cw6;CCW2 ccw6;Pwm2 pwm6;Md md6(cw6,ccw6,pwm6);
	CW3 cw7;CCW3 ccw7;Pwm3 pwm7;Md md7(cw7,ccw7,pwm7);
	Move move(md4,md5,md6,md7,center,ps3);move.setup();
	Debug debug(serial,center,ps3);debug.setup();

	while(1){
		blink0.cycle();
		center.cycle();
		ps3.cycle();
		//move.manualModeCycle();
		debug.cycle();

		if(millis()-time>=100){
			time=millis();
			/*serial.printf("lx:%.4f",ps3.lx());
			serial.printf("ly:%.4f",ps3.ly());
			serial.printf("rx:%.4f",ps3.rx());
			serial.printf("ry:%.4f",ps3.ry());
			serial.printf("u:%.4f",ps3.up());
			serial.printf("r:%.4f",ps3.right());
			serial.printf("d:%.4f",ps3.down());
			serial.printf("l:%.4f",ps3.left());
			serial.printf("tri:%.4f",ps3.triangle());
			serial.printf("cir:%.4f",ps3.circle());
			serial.printf("cro:%.4f",ps3.cross());
			serial.printf("squ:%.4f",ps3.square());
			serial.printf("l1:%.4f",ps3.l1());
			serial.printf("l2:%.4f",ps3.l2());
			serial.printf("r1:%.4f",ps3.r1());
			serial.printf("r2:%.4f",ps3.r2());
			serial.printf("start:%.4f",ps3.start());
			serial.printf("select:%.4f",ps3.select());
			serial.printf("dis:%d\n",ps3.disconnect());*/

			//serial.printf("ang,% .4f, x,% .4f, y,% .4f\n",rtod(center.getAngle()),center.x(),center.y());
		}
	}
	return 0;
}
