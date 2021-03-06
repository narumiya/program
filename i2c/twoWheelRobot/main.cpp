//libraries
extern "C"{
#include "layer_driver/board/stm32f4_config/config_adc.h"
#include "layer_driver/board/stm32f4_config/config_i2c.h"
#include "stm32f4xx.h"
}
//application
#include "layer_application/console.hpp"
#include "layer_application/servo_controll.hpp"
//controller
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
#if 1
#include <stdio.h>
#include <string.h>
int main(){
	long long int time=millis();

	Led0 led;Blink blink(led);blink.setup();
	blink.time(200);
	Serial0 serial0;serial0.setup(115200);
	I2c0 i2c;i2c.setup();
	Aqm0802 lcd(i2c);lcd.setup();
	//S11059 color(i2c);color.setup();

	char data[10]={'\0'};
	int flag=0;

	while(1){
		blink.cycle();
		//color.setMode(S11059::HIGH);
		//color.cycle();
		i2c.cycle();
		if(millis()-time>=500){
			time=millis();
			if(!flag){
				flag=1;
				sprintf(data,"Hello");
				lcd.setCursor(0,0);
				lcd.sendString(data);
				lcd.setCursor(1,1);
				sprintf(data,"World");
				lcd.sendString(data);
			}else{
				flag=0;
				lcd.clear();
			}
			/*serial0.printf("r:%d",color.getRed());
			serial0.printf("g:%d",color.getGreen());
			serial0.printf("b:%d",color.getBlue());
			serial0.printf("inf:%d\n",color.getInfrared());*/
		}
	}
}
#endif
#if 0
#define I2C2_SCL_PIN	GPIO_Pin_10
#define I2C2_SDA_PIN	GPIO_Pin_11
#define I2C2_PORT	GPIOB
int main(){
	//Enc0 enc0;enc0.setup();
	//Enc1 enc1;enc1.setup();
	//Enc2 enc2;enc2.setup();
	Serial0 serial0;serial0.setup(115200);
	Led0 led;Blink blink(led);blink.setup();
	blink.time(200);
	Init_i2c(I2C2,I2C2_PORT,I2C2_SCL_PIN,I2C2_SDA_PIN);
	//I2c_lcd_init();
	I2CLcdCommand();
	//Serial1 serial1;serial1.setup(115200);
	Rgb_t rgb={0,0,0,0};
	char str[30];
	unsigned long int time=millis();
	int flag=0;
	while(1){
		blink.cycle();
		I2cColorConfig(HIGH);

		if(millis()-time>=300){
			time=millis();
			/*switch(flag){
			case 0:
				I2CLcdLocate(0,0);
				I2CLcdSendString("Hello");flag=1;
				break;
			case 1:
				I2CLcdLocate(3,1);
				I2CLcdSendString("World");flag=2;
				break;
			case 2:flag=3;break;
			case 3:
				I2CLcdClear();flag=0;
				break;
			}*/
			rgb=getColor();
			sprintf(str,"R%3d",rgb.red);
			I2CLcdLocate(0,0);
			I2CLcdSendString(str);
			sprintf(str,"G%3d",rgb.green);
			I2CLcdLocate(4,0);
			I2CLcdSendString(str);
			sprintf(str,"B%3d",rgb.blue);
			I2CLcdLocate(0,1);
			I2CLcdSendString(str);
			serial0.printf("r:%d",rgb.red);
			serial0.printf("g:%d",rgb.green);
			serial0.printf("b:%d",rgb.blue);
			serial0.printf("inf:%d\n",rgb.infrared);
		}
		/*I2c_lcd_locate(0,0);
		//I2c_lcd_put_c('a');
		I2c_lcd_put_str("Hello!!");
		I2c_lcd_locate(2,1);
		I2c_lcd_put_str("World!!");*/
		//serial0.printf("%d %d %d\n",enc0.count(),enc1.count(),enc2.count());
		//serial1.printf("%d %d %d\n",enc0.count(),enc1.count(),enc2.count());
	}
}
#endif

#if 0
#define AD0		GPIOC,GPIO_Pin_5
#define AD1		GPIOC,GPIO_Pin_1
#define AD2		GPIOC,GPIO_Pin_2
#define AD3		GPIOC,GPIO_Pin_3
#define AD4		GPIOC,GPIO_Pin_4
int main(){
	Pwm0 pwm0;
	Servo servo(pwm0);
	Sw0 sw;ButtonInfo startSW(sw);
	Sw1 sw1;ButtonInfo resetSw(sw1);
	startSW.setup(true,50);
	resetSw.setup(true,50);
	Led0 led;Blink blink(led);blink.setup();
	blink.time(200);
	Serial0 serial;serial.setup(115200);
	/*Console console(serial);console.setup(115200);
	console.setNewLine(Console::NEWLINE_CR);
	ServoControll servoControll(servo,console);*/
	Enc1 enc;
	Serial1 gyroPin;R1350n gyro(gyroPin);//gyro.setup();
	roboCenter robot(enc,gyro,resetSw);
	robot.setup();
	A0 a0;A1 a1;A2 a2;A3 a3;A4 a4;
	//Move move(left,right,a0,a1,a2,a3,a4,startSW);
	Move move(a0,a1,a2,a3,a4,startSW,servo);
	//move.setup();
	//servo.setup(30,270,1.5,2.3);//�ߓ��T�[�{
	//servo.setup(20.0,180.0,1.5,2.4);//rb956 rb955

	/*int i=a0.setupAnalogIn();
	i=a1.setupAnalogIn();
	i=a2.setupAnalogIn();
	i=a3.setupAnalogIn();
	i=a4.setupAnalogIn();*/
	Init_ADC1(AD0);
	Init_ADC1(AD1);
	Init_ADC1(AD2);
	Init_ADC1(AD3);
	Init_ADC1(AD4);
	bool flag=false;float deg=0;
	unsigned int serialTime=millis();
	unsigned int tim=millis();

	while(1){
		startSW.cycle();
		//move.TPR105Cycle();
		blink.cycle();
		robot.cycle();
		//move.cycle();
		//console.cycle();
		//servoControll.cycle();
		if(startSW.readValue()) gyro.reset();

		if(millis()-tim>=50){
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

		if(millis()-serialTime>=100){
			serialTime=millis();
			//serial.printf("accx %f",currentAccelerationValues[0]);
			//serial.printf("accy %f",currentAccelerationValues[1]);
			//serial.printf("accz %f  ",currentAccelerationValues[2]);
			//serial.printf("accx %f",currentOrientationValues[0]);
			//serial.printf("accy %f",currentOrientationValues[1]);
			//serial.printf("accz %f  ",currentOrientationValues[2]);
			//serial.printf("\n");
			//serial.printf("accx %f",accx);
			//serial.printf("accy %f",accy);
			//serial.printf("accz %f",accz);
			//serial.printf("x,%f",x);
			//serial.printf("vel %f",velocity);
			//serial.printf("\n");
			//serial.printf("deg %.4f",rtod(gyro.angle()));
			//serial.printf("y %f",(gyro.accely()-initaccx));//*9.80665));
			//serial.printf("accy %f",(gyro.accely()-initaccy));//*9.806655));
			//serial.printf("accz %.4f",(gyro.accelz()));//*9.80665));
			//serial.printf("x,%f,y,%f",x,y);
			//serial.printf("accx %f",(gyro.accelx()/1000.0)*9.800);
			//serial.printf("accy %f",(gyro.accely()/1000.0)*9.8000);
			//serial.printf("accz %f",(gyro.accelz()/1000.0)*9.8000);
			//serial.printf("accx %f",(gyro.accelx()));
			//serial.printf("accy %f",(gyro.accely()));
			//serial.printf("accz %f",(gyro.accelz()));
			//serial.printf("ad0 %f,",a0.analogRead());
			//serial.printf("ad1 %f,",a1.analogRead());
			//serial.printf("ad2 %f,",a2.analogRead());
			//serial.printf("ad3 %f,",a3.analogRead());
			//serial.printf("ad4 %f  ",a4.analogRead());
			//move.printAdValue();
			serial.printf("x, %f, y, %f ,deg, %f  ",robot.getX(),robot.getY(),rtod(robot.getAngle()));
			serial.printf("\n");
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
					id++;
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
