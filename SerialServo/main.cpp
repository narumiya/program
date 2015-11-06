//libraries
extern "C"{
#include "config_encoder.h"
#include "config_pwm.h"
#include "config_adc.h"
#include "config_usart.h"
}
//application
//controller
#include "layer_controller/blink.hpp"
//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"

//circuit
#include "layer_driver/circuit/ta7291.hpp"
#include "layer_driver/circuit/servo.hpp"

#if 1
int main(void){
	Led0 led0;
	Sw0 sw0;sw0.setupDigitalIn();
	Sw1 sw1;sw1.setupDigitalIn();
	Sw2 sw2;sw2.setupDigitalIn();
	Sw3 sw3;sw3.setupDigitalIn();
	Blink blink0(led0);blink0.setup();blink0.time(200);
	Serial1 serial1;	serial1.setup(115200);
	Serial0 serial0;
	Servo servo(serial0);servo.setup();
	int flag=0;
	float deg=0.00;
	long long int time=0;
	long long int servotime=0;
	int id=0;

	/*servo.setPara(0,1,0.01);
	wait(100);
	servo.setPara(1,2,0.2);*/
	/*servo.setId(1,1);
	while(1);*/

	while(1){
		blink0.cycle();
		servo.serialCycle();
		if(millis()-time>=5){
			time=millis();
			servo.setAngle(id,deg);
			serial1.printf("target,%.3f,",deg);
			/*for(int j=0;j<3;j++){
				serial1.printf("id%d,%.2f,",j,servo.getAngle(j));
			}*/
			serial1.printf("id%d,%.2f,",id,servo.getAngle(id));
			serial1.printf("\n");
			//serial1.printf("%d\n",servo.readPara(1,3));
			//serial1.printf("%d\n",servo.setId(0,1));
		}
		if(millis()-servotime>=1000){
			servotime=millis();
			switch(flag){
				case 0:
					flag=1;
					deg=135;break;
				case 1:
					flag=2;
					deg=0;break;
				case 2:
					flag=3;
					deg=135;break;
				case 3:
					flag=4;
					deg=-135;break;
				case 4:
					flag=0;
					//id++;
					if(id==3) id=0;break;
				}
			/*switch(flag){
			case 0:
				flag=1;
				deg=130;break;
			case 1:
				flag=0;
				deg=-130;break;
			}*/
		}
	}
}
#endif

#if 0
int main(void){
	Led0 led0;
	Sw0 sw0;sw0.setupDigitalIn();
	Sw1 sw1;sw1.setupDigitalIn();
	Sw2 sw2;sw2.setupDigitalIn();
	Sw3 sw3;sw3.setupDigitalIn();
	Blink blink0(led0);blink0.setup();blink0.time(200);
	Serial1 serial1;	serial1.setup(115200);
	Serial0 serial0;
	Servo servo(serial0);servo.setup();
	int data=0;
	int flag=0;
	float deg=0.00;
	long long int time=0;
	long long int timer=0;
	long long int servotime=0;
	int i=0;

	while(1){
		blink0.cycle();
		for(i=0;i<1000;i++){
			servo.setAngle(0,130);
			while(serial0.charAvailable()){
				servo.rec(0,serial0.readChar());
				//serial1.printf("%d\n",serial0.readChar());
			}
			wait(1);
		}
		for(i=0;i<1000;i++){
			servo.setAngle(0,-130);
			while(serial0.charAvailable()){
				servo.rec(0,serial0.readChar());
			}
			wait(1);
		}
	}
}
#endif

#if 0
int main(void){
	Led0 led0;
	Sw0 sw0;sw0.setupDigitalIn();
	Sw1 sw1;sw1.setupDigitalIn();
	Sw2 sw2;sw2.setupDigitalIn();
	Sw3 sw3;sw3.setupDigitalIn();
	Blink blink0(led0);blink0.setup();blink0.time(200);
	Serial1 serial1;	serial1.setup(115200);
	Serial0 serial0;
	Servo servo(serial0);servo.setup();
	int data=0;
	int flag=0;
	float deg=0.00;
	long long int time=0;
	long long int timer=0;
	long long int servotime=0;
	int i=0;
	while(1){
		blink0.cycle();
		if(millis()-time>=10){
			time=millis();
			/*if(millis()-time>=600){
				timer=millis();
				switch(flag){
				case 0:
					flag=1;
					deg=135;break;
				case 1:
					flag=2;
					deg=0;break;
				case 2:
					flag=3;
					deg=135;break;
				case 3:
					flag=4;
					deg=-135;break;
				case 4:
					deg=FREE;
					flag=0;
					i++;
					if(i==4) i=0;break;
				}
			}*/
			/*
            switch(flag){
                case 0:
                flag=1;
                deg=7500;break;
                case 1:
                flag=2;
                deg=11500;break;
                case 2:
                flag=0;
                deg=3500;break;
            }*/

			//data=servo.setPos(0,deg);
			data=servo.setPos(0,deg);
			serial1.printf("%d, %d\n",(int)deg,calcAngle(data));
			//data=servo.set_pos(1,deg);
			//data=servo.set_pos(2,deg);
			//data=servo.set_pos(3,deg);
			/*if(!sw0.digitalRead()){
				data=servo.set_pos(0,deg);
			}else if(!sw1.digitalRead()){
				data=servo.set_pos(1,deg);
			}else if(!sw2.digitalRead()){
				data=servo.set_pos(2,deg);
			}else if(!sw3.digitalRead()){
				data=servo.set_pos(3,deg);
			}*/
		}
		if(millis()-timer>=600){
			timer=millis();
			switch(flag){
			case 0:
				flag=1;
				deg=135;break;
			case 1:
				flag=2;
				deg=0;break;
			case 2:
				flag=3;
				deg=135;break;
			case 3:
				flag=4;
				deg=-135;break;
			case 4:
				deg=FREE;
				flag=0;
				i++;
				if(i==4) i=0;break;
			}
		}
		/*if(millis()-servotime>=30){
			if(fabs(deg-deg)!=0){
				for(i=0;i<4;i++){
					data=servo.set_pos(i,deg);
				}
			}
		}*/
	}
}
#endif
#if 0
int main(void)
{
	Led0 led0;
	Sw0 sw0;sw0.setupDigitalIn();
	Blink blink0(led0);blink0.setup();blink0.time(200);
	Pwm0 pwm0;
	Servo servo(pwm0);servo.setup(30,270,1.5,2.3);
	Serial0 serial0;
	serial0.setup(115200);
	float deg=0;
	float duty=0;
	int flag=0;
	long long int time=0;
	Set_duty(SERVO_TIM_CH,0);
	wait(500);
	while(1){
		blink0.cycle();
		for(deg=-135;deg<135;deg+=10){
			servo.duty(deg);
			if(!sw0.digitalRead())
				servo.cycle();
			led0.digitalToggle();
			serial0.printf("%f\n",deg);
			wait(500);
		}
		for(deg=135;deg>-135;deg-=10){
			servo.duty(deg);
			if(!sw0.digitalRead())
				servo.cycle();
			led0.digitalToggle();
			serial0.printf("%f\n",deg);
			wait(500);
		}
		/*if(millis()-time>=500){
			time=millis();
			if(!sw0.digitalRead()){
				switch (flag) {
					case 0:
						flag=1;
						deg=-135;
						duty=0.7/30;
						break;
					case 1:
						flag=2;
						deg=135;
						duty=2.3/30;
						break;
					case 2:
						flag=0;
						deg=0;
						duty=1.5/30;
						break;
					default:
						break;
				}
				servo_move(deg);
				//Set_duty(SERVO_TIM_CH,duty);
				serial.printf("%f\n",deg);
			}
		}*/
	}
}
#endif
#if 0
int main(void)
{
	Led0 led0;led0.setupDigitalOut();
	Led1 led1;led1.setupDigitalOut();
	Led2 led2;led2.setupDigitalOut();
	Led3 led3;led3.setupDigitalOut();
	Buzzer buzzer;buzzer.setupDigitalOut();
	Sw0 sw0;sw0.setupDigitalIn();
	Sw1 sw1;sw1.setupDigitalIn();
	Sw2 sw2;sw2.setupDigitalIn();
	Sw3 sw3;sw3.setupDigitalIn();

	A0 a0;//a0.setupAnalogIn();
	A1 a1;a1.setupAnalogIn();
	A2 a2;//a2.setupAnalogIn();
	A3 a3;//a3.setupAnalogIn();
	A4 a4;a4.setupAnalogIn();

	/*Init_ADC1(GPIOC,GPIO_Pin_1);
	Init_ADC1(GPIOC,GPIO_Pin_2);//2
	Init_ADC1(GPIOC,GPIO_Pin_3);
	Init_ADC1(GPIOC,GPIO_Pin_4);//4
	Init_ADC1(GPIOC,GPIO_Pin_5);*/

	CW0 cw0;cw0.setupDigitalOut();
	CW1 cw1;cw1.setupDigitalOut();
	CW2 cw2;cw2.setupDigitalOut();
	CW3 cw3;cw3.setupDigitalOut();
	CW4 cw4;cw4.setupDigitalOut();
	CW5 cw5;cw5.setupDigitalOut();
	CCW0 ccw0;ccw0.setupDigitalOut();
	CCW1 ccw1;ccw1.setupDigitalOut();
	CCW2 ccw2;ccw2.setupDigitalOut();
	CCW3 ccw3;ccw3.setupDigitalOut();
	CCW4 ccw4;ccw4.setupDigitalOut();
	CCW5 ccw5;ccw5.setupDigitalOut();
	Pwm0 pwm0;pwm0.setupPwmOut(10000,1);
	Pwm1 pwm1;pwm1.setupPwmOut(10000,1);
	Pwm2 pwm2;pwm2.setupPwmOut(10000,1);
	Pwm3 pwm3;pwm3.setupPwmOut(10000,1);
	Pwm4 pwm4;pwm4.setupPwmOut(10000,1);
	Pwm5 pwm5;pwm5.setupPwmOut(10000,1);
	Enc0 enc0;enc0.setup();
	Enc1 enc1;enc1.setup();
	Enc2 enc2;enc2.setup();
	Serial0 serial0;
	serial0.setup(115200);
	//Blink blink(cw0);blink.setup();
	//blink.time(500);

	Blink blink0(led0);blink0.setup();blink0.time(150);
	Blink blink1(led1);blink1.setup();blink1.time(300);
	Blink blink2(led2);blink2.setup();blink2.time(450);
	Blink blink3(led3);blink3.setup();blink3.time(600);
	//Blink blink4(a4);blink4.setup();blink4.time(2000);

	float duty=0;
	int flag=0;
	int time=0;
	int led=0;

	while(1){
		blink0.cycle();
		blink1.cycle();
		blink2.cycle();
		blink3.cycle();
		//blink4.cycle();
		if(millis()-time>=60){
			time=millis();
			/*if(flag==0){
				if(duty>=1){
					flag=1;
				}
				duty+=0.1;
			}else{
				if(duty<0){
					flag=0;
				}
				duty-=0.1;
			}
			pwm0.pwmWrite(duty);
			pwm1.pwmWrite(duty);
			pwm2.pwmWrite(duty);
			pwm3.pwmWrite(duty);
			pwm4.pwmWrite(duty);
			pwm5.pwmWrite(duty);*/

			if(!sw0.digitalRead())	Reset_encoder_over_under_flow();

			/*serial0.printf("a0:%d, ",a0.analogRead());
			serial0.printf("a1:%d, ",a1.analogRead());
			serial0.printf("a2:%d, ",a2.analogRead());
			serial0.printf("a3:%d, ",a3.analogRead());
			serial0.printf("a4:%d\n",a4.analogRead());*/
			serial0.printf("a0:%.2f",get_ADC1_value(GPIOC,GPIO_Pin_5));
			serial0.printf("a1:%.2f",get_ADC1_value(GPIOC,GPIO_Pin_1));
			serial0.printf("a2:%.2f",get_ADC1_value(GPIOC,GPIO_Pin_2));
			serial0.printf("a3:%.2f",get_ADC1_value(GPIOC,GPIO_Pin_3));
			serial0.printf("a4:%.2f\n",get_ADC1_value(GPIOC,GPIO_Pin_4));
			//serial0.printf("s0:%d, s1:%d, s2:%d, s3:%d ",sw0.digitalRead(),sw1.digitalRead(),sw2.digitalRead(),sw3.digitalRead());
			//serial0.printf("e0:%d, e1:%d, e2:%d\n\r",enc0.count(),enc1.count(),enc2.count());

		}
		/*if(millis()-led>=150){
			led=millis();
			cw0.digitalToggle();ccw0.digitalToggle();
			cw1.digitalToggle();ccw1.digitalToggle();
			cw2.digitalToggle();ccw2.digitalToggle();
			cw3.digitalToggle();ccw3.digitalToggle();
			cw4.digitalToggle();ccw4.digitalToggle();
			cw5.digitalToggle();ccw5.digitalToggle();
		}*/
	}
	return 0;
}
#endif
