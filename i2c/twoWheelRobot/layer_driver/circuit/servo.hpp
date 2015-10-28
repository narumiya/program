#ifndef SERVO_HPP
#define SERVO_HPP

#include "Pwm.hpp"
#include "serial.hpp"
#include "stm32f4xx_usart.h"

#define FREE 99999	//�t���[
#define NUM 1	//�f�C�W�[�`�F�[�������

class Servo:public SerialInterface{
	private:
		Pwm *pwm;
		//Serial *serial;
		float Period;		//����(ms)
		float NeutPulse;	//ms �^�񒆂̃p���X
		float RangeDeg;	//�T�[�{����p�x
		float MaxPulse;	//ms �ő�p�x���̃p���X
		float request;
		int targetAngle[NUM];
		int servoAngle[NUM];
		unsigned int time;
		int Id;
	public:
		/*PWM�œ�����*/
		/*�d���������M������500ms LOW*/

		Servo (Pwm &pwmPin);
		int setup(float setPeriod, float setRangeDeg, float setNeutral, float setMaxPulse);
		void cycle();
		void setAngle(float rad);
		void setDuty(float pos);
		float cvtPulse(float rad);
		/*�V���A���œ�����*/
		/*�d���������M������500ms HIGH*/
		Servo (Serial &serialPin);
		int setup();
		void setAngle(int id,float angle);
		void rec(int id,char data);
		void serialCycle();
		float getAngle(int id);
		int degToPos(float degree);
		float posToDeg(int pos);
		int readPara(int id,int mode);
		int setPara(int id,int mode,float value);
		/*�����Ӂ�
		 * ID �R�}���h���g�p����ۂ́A�K�����葤�ƃV���A���T�[�{���P�΂P�Őڑ����邱�ƁI
		 */
		int setId(int id,int mode);
};


#endif