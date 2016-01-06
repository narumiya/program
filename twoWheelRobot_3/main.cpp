//libraries
extern "C"{
#include <stdint.h>
#include "layer_driver/board/stm32f4_config/config_adc.h"
#include "layer_driver/board/stm32f4_config/config_i2c.h"
#include "stm32f4xx.h"
}
//application
#include "layer_application/console.hpp"
#include "layer_application/servo_controll.hpp"
//controller
#include "layer_controller/advanced_encoder.hpp"
#include "layer_controller/blink.hpp"
#include "layer_controller/move.hpp"
#include "layer_controller/robo_center.hpp"
//base
#include "system.h"
#include "mcutime.h"
//board
#include "pin.hpp"
//circuit
#include "layer_driver/circuit/mini_md_1.0/mini_md.hpp"
#include "layer_driver/circuit/servo.hpp"
#include "layer_driver/circuit/r1350n/r1350n.hpp"
#include "layer_driver/circuit/button/button.hpp"
#include "layer_driver/circuit/lcd/aqm0802.hpp"
#include "layer_driver/circuit/s11059.hpp"
#include "layer_driver/circuit/ina226.hpp"
#include "layer_driver/circuit/kondo_servo.hpp"
#include "layer_driver/circuit/fun.hpp"
#include "layer_driver/circuit/line_sensor.hpp"

#define AD0		GPIOC,GPIO_Pin_5
#define AD1		GPIOC,GPIO_Pin_1
#define AD2		GPIOC,GPIO_Pin_2
#define AD3		GPIOC,GPIO_Pin_3
#define AD4		GPIOC,GPIO_Pin_4

int main(){
	Pwm0 pwm0;
	Servo servo(pwm0);
	A0 a0;A1 a1;A2 a2;A3 a3;A4 a4;
	LineSensor line(a0,a1,a2,a3,a4);

	Sw0 sw0;ButtonInfo button0(sw0);
	Sw1 sw1;ButtonInfo button1(sw1);
	button0.setup(true,50);
	button1.setup(true,50);
	Led0 led;Blink blink(led);blink.setup();
	Buzzer buzz;buzz.setupDigitalOut();
	blink.time(800);
	Serial0 serial;serial.setup(115200);
	/*Console console(serial);console.setup(115200);
	console.setNewLine(Console::NEWLINE_CR);
	ServoControll servoControll(servo,console);*/
	Enc1 enc;
	AdvancedEncoder adenc(enc,1000);
	Serial1 gyroPin;R1350n gyro(gyroPin);
	RoboCenter robot(adenc,gyro);
	robot.setup();
	Move move(line,buzz,button0,button1,servo,robot);
	move.setup();

	for(unsigned int i=0;i<100000;i++)	buzz.digitalHigh();
	buzz.digitalLow();
	bool flag=false;float deg=0;
	unsigned int serialTime=millis();
	int64_t tim=millis();

	while(1){
		if(move.getStart()){
			blink.time(200);
			blink.cycle();
		}else{
			blink.cycle();
		}

		robot.cycle();
		move.cycle();
		//console.cycle();
		//servoControll.cycle();

#if 0
		for(deg=-65;deg<50;deg+=10){
			servo.setAngle(dtor(deg));
			servo.cycle();
			wait(37);
		}
		for(deg=50;deg>-65;deg-=10){
			servo.setAngle(dtor(deg));
			servo.cycle();
			wait(37);
		}
#endif
#if 0
		if(millis()-tim>=5){
			tim=millis();
			if(serial.charAvailable()){
				flag=true;
				char key=serial.readChar();
				serial.printf("key %c\n",key);
				if(key=='d'){
					deg+=5.0;
					deg=floatlimit(-135,deg,135);
				}else if(key=='a'){
					deg-=5.0;
					deg=floatlimit(-135,deg,135);
				}else if(key=='w'){
					deg=0;
				}
				serial.printf("deg %.2f",deg);
				servo.setAngle(dtor(deg));
			}
		}
		if(flag)servo.cycle();
#endif

#if 1
		if(millis()-serialTime>=100){
			serialTime=millis();
			move.printRoboInfo();
			serial.printf("\n");
		}
#endif
	}
}
