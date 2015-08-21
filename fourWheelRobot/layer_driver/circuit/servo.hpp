#ifndef SERVO_HPP
#define SERVO_HPP

#include "Pwm.hpp"
#include "serial.hpp"
#include "stm32f4xx_usart.h"

#define FREE 99999
#define NUM 6

class Servo{
	private:
		Pwm *pwm;
		Serial *serial;
		float Period;		//ms
		float NeutPulse;	//ms真ん中のパルス
		float RangeDeg;	//サーボ動作角度
		float MaxPulse;	//ms 最大角度時のパルス
		float request;
		int targetAngle[NUM];
		int servoAngle[NUM];
		int time;
		int Id;
	public:
		Servo (Pwm &pwmPin);
		Servo (Serial &serialPin);
		int setup();
		int setup(float setPeriod, float setRangeDeg, float setNeutral, float setMaxPulse);
		void cycle();
		void duty(float deg);

		void setAngle(int id,float angle);
		void rec(int id,char data);
		void serialCycle();
		float getAngle(int id);
		int degToPos(float degree);
		float posToDeg(int pos);
		int readPara(int id,int mode);
		int setPara(int id,int mode,float value);
		/*＜注意＞
		 * ID コマンドを使用する際は、必ず送り側とシリアルサーボを１対１で接続すること！
		 */
		int setId(int id,int mode);
};


#endif
