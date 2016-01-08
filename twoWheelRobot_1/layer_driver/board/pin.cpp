
#include "pin.hpp"
#if 0
extern "C" {
#include <string.h>
#include <stdio.h>
#include "mcutime.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "config_usart.h"
#include "config_encoder.h"
#include "config_systick.h"
#include "config_usart.h"
#include "config_pwm.h"
#include "config_port.h"
#include "layer_driver/board/stm32f4_config/config_adc.h"
#include "config_can.h"
#include "config_i2c.h"
}


//#define LED0 GPIOD, GPIO_Pin_12
#define LED0		GPIOB,GPIO_Pin_12//GPIOB,GPIO_Pin_0
#define LED1		GPIOE,GPIO_Pin_15//GPIOC,GPIO_Pin_0//input �ł��Ȃ�
#define LED2		GPIOB,GPIO_Pin_14//pwm�ł���//GPIOA,GPIO_Pin_5
#define LED3		GPIOB,GPIO_Pin_15//pwm�ł���GPIOA,GPIO_Pin_4
#define SW0		GPIOA,GPIO_Pin_15//GPIOE,GPIO_Pin_2
#define SW1		GPIOB,GPIO_Pin_13//GPIOE,GPIO_Pin_4
#define SW2		GPIOD,GPIO_Pin_11//GPIOE,GPIO_Pin_8
#define SW3		GPIOD,GPIO_Pin_10//GPIOA,GPIO_Pin_15
#define BUZZER	GPIOB,GPIO_Pin_1//pwm�ł���GPIOE,GPIO_Pin_3


#define AD0		GPIOC,GPIO_Pin_5
#define AD1		GPIOC,GPIO_Pin_1
#define AD2		GPIOC,GPIO_Pin_2
#define AD3		GPIOC,GPIO_Pin_3
#define AD4		GPIOC,GPIO_Pin_4

/*
#define PWM0		GPIOE,GPIO_Pin_11//GPIOE,GPIO_Pin_9
#define CWIO0		GPIOA,GPIO_Pin_4//GPIOE,GPIO_Pin_10
#define CCWIO0	GPIOC,GPIO_Pin_0//GPIOE,GPIO_Pin_7
#define PWM0SET			TIM1,PWM0
#define PWM0TIMCH		TIM1,2
*/

#define PWM0		GPIOB,GPIO_Pin_1//GPIOE,GPIO_Pin_9
#define CWIO0		GPIOA,GPIO_Pin_4//GPIOE,GPIO_Pin_10
#define CCWIO0	GPIOC,GPIO_Pin_0//GPIOE,GPIO_Pin_7
#define PWM0SET			TIM3,PWM0
#define PWM0TIMCH		TIM3,4

#define PWM1		GPIOE,GPIO_Pin_6//GPIOE,GPIO_Pin_11
#define CWIO1		GPIOE,GPIO_Pin_12//GPIOE,GPIO_Pin_15
#define CCWIO1	GPIOA,GPIO_Pin_5//GPIOE,GPIO_Pin_12
#define PWM1SET			TIM9,GPIOE,GPIO_Pin_6
#define PWM1TIMCH		TIM9,2

#define PWM2		GPIOE,GPIO_Pin_5//GPIOE,GPIO_Pin_13
#define CWIO2		GPIOB,GPIO_Pin_2//GPIOB,GPIO_Pin_13
#define CCWIO2	GPIOE,GPIO_Pin_7//GPIOB,GPIO_Pin_12
#define PWM2SET			TIM9,GPIOE,GPIO_Pin_5
#define PWM2TIMCH		TIM9,1

#define PWM3		GPIOE,GPIO_Pin_9//GPIOE,GPIO_Pin_14
#define CWIO3		GPIOE,GPIO_Pin_10//GPIOB,GPIO_Pin_15
#define CCWIO3	GPIOB,GPIO_Pin_0//GPIOB,GPIO_Pin_14
#define PWM3SET			TIM1,GPIOE,GPIO_Pin_9
#define PWM3TIMCH		TIM1,1

#define PWM4		GPIOE,GPIO_Pin_14//GPIOE,GPIO_Pin_6
#define CWIO4		GPIOE,GPIO_Pin_4//GPIOD,GPIO_Pin_11
#define CCWIO4	GPIOE,GPIO_Pin_2//GPIOD,GPIO_Pin_10
#define PWM4SET			TIM1,GPIOE,GPIO_Pin_14
#define PWM4TIMCH		TIM1,4

#define PWM5		GPIOE,GPIO_Pin_13//GPIOE,GPIO_Pin_5
#define CWIO5		GPIOE,GPIO_Pin_8//GPIOB,GPIO_Pin_1
#define CCWIO5	GPIOE,GPIO_Pin_3//GPIOB,GPIO_Pin_2
#define PWM5SET			TIM1,GPIOE,GPIO_Pin_13
#define PWM5TIMCH		TIM1,3

//led3��buzzer�ǂ���������pwm�ł��Ȃ�
#define LED2SET			TIM8,GPIOB,GPIO_Pin_14
#define LED2TIMCH		TIM8,2

#define LED3SET			TIM8,GPIOB,GPIO_Pin_15
#define LED3TIMCH		TIM8,3

#define BUZZERSET		TIM8,GPIOB,GPIO_Pin_1
#define BUZZERTIMCH	TIM8,3


#define ENC0TIM	TIM4
#define ENC0		GPIOD,GPIO_Pin_12 | GPIO_Pin_13
#define ENC1TIM	TIM3
#define ENC1		GPIOA,GPIO_Pin_6 | GPIO_Pin_7		//PA6 input�ł��Ȃ�
#define ENC2TIM	TIM5
#define ENC2		GPIOA,GPIO_Pin_0 | GPIO_Pin_1

int Led0:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(LED0);
}

void Led0::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(LED0);
	}else{
		GPIO_SetBits(LED0);
	}
}

int Led0::_digitalRead()
{
	return GPIO_ReadInputDataBit(LED0);
}

int Led0::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, LED0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Led0::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, LED0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Led0::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, LED0, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Led0::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, LED0, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Led1:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(LED1);
}

void Led1::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(LED1);
	}else{
		GPIO_SetBits(LED1);
	}
}

int Led1::_digitalRead()
{
	return GPIO_ReadInputDataBit(LED1);
}

int Led1::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, LED1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 1;
}

int Led1::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, LED1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Led1::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, LED1, GPIO_PuPd_UP, GPIO_OType_PP);
	return 1;
}

int Led1::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, LED1, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Led2:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(LED2);
}

void Led2::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(LED2);
	}else{
		GPIO_SetBits(LED2);
	}
}

int Led2::_digitalRead()
{
	return GPIO_ReadInputDataBit(LED2);
}

int Led2::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, LED2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Led2::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, LED2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Led2::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, LED2, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Led2::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, LED2, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Led3:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(LED3);
}

void Led3::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(LED3);
	}else{
		GPIO_SetBits(LED3);
	}
}

int Led3::_digitalRead()
{
	return GPIO_ReadInputDataBit(LED3);
}

int Led3::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, LED3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Led3::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, LED3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Led3::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, LED3, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Led3::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, LED3, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Sw0:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(SW0);
}

void Sw0::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(SW0);
	}else{
		GPIO_SetBits(SW0);
	}
}

int Sw0::_digitalRead()
{
	return GPIO_ReadInputDataBit(SW0);
}

int Sw0::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, SW0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw0::_setupDigitalOut()
{
	//Init_port(GPIO_Mode_OUT, SW0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 1;
}

int Sw0::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, SW0, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Sw0::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, SW0, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Sw1:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(SW1);
}

void Sw1::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(SW1);
	}else{
		GPIO_SetBits(SW1);
	}
}

int Sw1::_digitalRead()
{
	return GPIO_ReadInputDataBit(SW1);
}

int Sw1::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, SW1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw1::_setupDigitalOut()
{
	//Init_port(GPIO_Mode_OUT, SW1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 1;
}

int Sw1::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, SW1, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Sw1::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, SW1, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Sw2:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(SW2);
}

void Sw2::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(SW2);
	}else{
		GPIO_SetBits(SW2);
	}
}

int Sw2::_digitalRead()
{
	return GPIO_ReadInputDataBit(SW2);
}

int Sw2::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, SW2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw2::_setupDigitalOut()
{
	//Init_port(GPIO_Mode_OUT, SW2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 1;
}

int Sw2::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, SW2, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Sw2::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, SW2, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Sw3:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(SW3);
}

void Sw3::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(SW3);
	}else{
		GPIO_SetBits(SW3);
	}
}

int Sw3::_digitalRead()
{
	return GPIO_ReadInputDataBit(SW3);
}

int Sw3::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, SW3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw3::_setupDigitalOut()
{
	//Init_port(GPIO_Mode_OUT, SW3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 1;
}

int Sw3::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, SW3, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Sw3::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, SW3, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Buzzer:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(BUZZER);
}

void Buzzer::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(BUZZER);
	}else{
		GPIO_SetBits(BUZZER);
	}
}

int Buzzer::_digitalRead()
{
	return GPIO_ReadInputDataBit(BUZZER);
}

int Buzzer::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, BUZZER, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Buzzer::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, BUZZER, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Buzzer::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, BUZZER, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Buzzer::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, BUZZER, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CW0:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO0);
}

void CW0::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO0);
	}else{
		GPIO_SetBits(CWIO0);
	}
}

int CW0::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO0);
}

int CW0::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW0::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW0::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO0, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CW0::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO0, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CCW0:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO0);
}

void CCW0::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO0);
	}else{
		GPIO_SetBits(CCWIO0);
	}
}

int CCW0::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO0);
}

int CCW0::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW0::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW0::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO0, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CCW0::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO0, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CW1:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO1);
}

void CW1::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO1);
	}else{
		GPIO_SetBits(CWIO1);
	}
}

int CW1::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO1);
}

int CW1::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW1::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW1::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO1, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CW1::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO1, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CCW1:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO1);
}

void CCW1::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO1);
	}else{
		GPIO_SetBits(CCWIO1);
	}
}

int CCW1::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO1);
}

int CCW1::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW1::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW1::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO1, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CCW1::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO1, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CW2:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO2);
}

void CW2::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO2);
	}else{
		GPIO_SetBits(CWIO2);
	}
}

int CW2::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO2);
}

int CW2::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW2::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW2::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO2, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CW2::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO2, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CCW2:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO2);
}

void CCW2::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO2);
	}else{
		GPIO_SetBits(CCWIO2);
	}
}

int CCW2::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO2);
}

int CCW2::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW2::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW2::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO2, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CCW2::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO2, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CW3:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO3);
}

void CW3::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO3);
	}else{
		GPIO_SetBits(CWIO3);
	}
}

int CW3::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO3);
}

int CW3::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW3::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW3::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO3, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CW3::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO3, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CCW3:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO3);
}

void CCW3::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO3);
	}else{
		GPIO_SetBits(CCWIO3);
	}
}

int CCW3::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO3);
}

int CCW3::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW3::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW3::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO3, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CCW3::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO3, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CW4:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO4);
}

void CW4::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO4);
	}else{
		GPIO_SetBits(CWIO4);
	}
}

int CW4::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO4);
}

int CW4::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW4::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW4::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO4, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CW4::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO4, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CCW4:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO4);
}

void CCW4::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO4);
	}else{
		GPIO_SetBits(CCWIO4);
	}
}

int CCW4::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO4);
}

int CCW4::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW4::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW4::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO4, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CCW4::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO4, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CW5:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO5);
}

void CW5::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO5);
	}else{
		GPIO_SetBits(CWIO5);
	}
}

int CW5::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO5);
}

int CW5::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW5::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CW5::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO5, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CW5::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO5, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int CCW5:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO5);
}

void CCW5::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO5);
	}else{
		GPIO_SetBits(CCWIO5);
	}
}

int CCW5::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO5);
}

int CCW5::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW5::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int CCW5::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO5, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int CCW5::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO5, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A0:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(AD0);
}

void A0::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(AD0);
	}else{
		GPIO_SetBits(AD0);
	}
}

int A0::_digitalRead()
{
	return GPIO_ReadInputDataBit(AD0);
}

int A0::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, AD0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A0::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, AD0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A0::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, AD0, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A0::_setupDigitalInPullDown()
{

	Init_port(GPIO_Mode_IN, AD0, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A1:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(AD1);
}

void A1::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(AD1);
	}else{
		GPIO_SetBits(AD1);
	}
}

int A1::_digitalRead()
{
	return GPIO_ReadInputDataBit(AD1);
}

int A1::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, AD1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A1::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, AD1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A1::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, AD1, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A1::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, AD1, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A2:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(AD2);
}

void A2::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(AD2);
	}else{
		GPIO_SetBits(AD2);
	}
}

int A2::_digitalRead()
{
	return GPIO_ReadInputDataBit(AD2);
}

int A2::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, AD2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A2::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, AD2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A2::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, AD2, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A2::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, AD2, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A3:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(AD3);
}

void A3::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(AD3);
	}else{
		GPIO_SetBits(AD3);
	}
}

int A3::_digitalRead()
{
	return GPIO_ReadInputDataBit(AD3);
}

int A3::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, AD3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A3::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, AD3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A3::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, AD3, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A3::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, AD3, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A4:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(AD4);
}

void A4::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(AD4);
	}else{
		GPIO_SetBits(AD4);
	}
}

int A4::_digitalRead()
{
	return GPIO_ReadInputDataBit(AD4);
}

int A4::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, AD4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A4::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, AD4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A4::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, AD4, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A4::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, AD4, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Pwm0:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(PWM0);
}

void Pwm0::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(PWM0);
	}else{
		GPIO_SetBits(PWM0);
	}
}

int Pwm0::_digitalRead()
{
	return GPIO_ReadInputDataBit(PWM0);
}

int Pwm0::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, PWM0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm0::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, PWM0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm0::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, PWM0, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Pwm0::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, PWM0, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Pwm1:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(PWM1);
}

void Pwm1::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(PWM1);
	}else{
		GPIO_SetBits(PWM1);
	}
}

int Pwm1::_digitalRead()
{
	return GPIO_ReadInputDataBit(PWM1);
}

int Pwm1::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, PWM1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm1::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, PWM1, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm1::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, PWM1, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Pwm1::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, PWM1, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}


int Pwm2:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(PWM2);
}

void Pwm2::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(PWM2);
	}else{
		GPIO_SetBits(PWM2);
	}
}

int Pwm2::_digitalRead()
{
	return GPIO_ReadInputDataBit(PWM2);
}

int Pwm2::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, PWM2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm2::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, PWM2, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm2::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, PWM2, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Pwm2::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, PWM2, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Pwm3:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(PWM3);
}

void Pwm3::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(PWM3);
	}else{
		GPIO_SetBits(PWM3);
	}
}

int Pwm3::_digitalRead()
{
	return GPIO_ReadInputDataBit(PWM3);
}

int Pwm3::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, PWM3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm3::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, PWM3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm3::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, PWM3, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Pwm3::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, PWM3, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}


int Pwm4:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(PWM4);
}

void Pwm4::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(PWM4);
	}else{
		GPIO_SetBits(PWM4);
	}
}

int Pwm4::_digitalRead()
{
	return GPIO_ReadInputDataBit(PWM4);
}

int Pwm4::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, PWM4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm4::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, PWM4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm4::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, PWM4, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Pwm4::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, PWM4, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Pwm5:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(PWM5);
}

void Pwm5::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(PWM5);
	}else{
		GPIO_SetBits(PWM5);
	}
}

int Pwm5::_digitalRead()
{
	return GPIO_ReadInputDataBit(PWM5);
}

int Pwm5::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, PWM5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm5::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, PWM5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm5::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, PWM5, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Pwm5::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, PWM5, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A0::_setupAnalogIn()
{
	mode = MODE_ANALOG;
	Init_ADC1(AD0);
	return 0;
}

float A0::_analogRead()
{
	return ( get_ADC1_value(AD0) / analogResolution() );
}

int A1::_setupAnalogIn()
{
	mode = MODE_ANALOG;
	Init_ADC1(AD1);
	return 0;
}

float A1::_analogRead()
{
	return ( get_ADC1_value(AD1) / analogResolution() );
}

int A2::_setupAnalogIn()
{
	mode = MODE_ANALOG;
	Init_ADC1(AD2);
	return 0;
}

float A2::_analogRead()
{
	return ( get_ADC1_value(AD2) / analogResolution() );
}

int A3::_setupAnalogIn()
{
	mode = MODE_ANALOG;
	Init_ADC1(AD3);
	return 0;
}

float A3::_analogRead()
{
	return ( get_ADC1_value(AD3) / analogResolution() );
}

int A4::_setupAnalogIn()
{
	mode = MODE_ANALOG;
	Init_ADC1(AD4);
	return 0;
}

float A4::_analogRead()
{
	return ( get_ADC1_value(AD4) / analogResolution() );
}


int Enc0::setup()
{
	Init_encoder(ENC0TIM,ENC0);
	return 0;
}

int Enc0::count()
{
	if(revFlag) return -Select_encoder_count(ENC0TIM);
	else return Select_encoder_count(ENC0TIM);
}

int Enc1::setup()
{
	Init_encoder(ENC1TIM,ENC1);
	return 0;
}

int Enc1::count()
{
	if(revFlag) return -Select_encoder_count(ENC1TIM);
	else return Select_encoder_count(ENC1TIM);
}

int Enc2::setup()
{
	Init_encoder(ENC2TIM,ENC2);
	return 0;
}

int Enc2::count()
{
	if(revFlag) return -Select_encoder_count(ENC2TIM);
	else return Select_encoder_count(ENC2TIM);
}


int Pwm0::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(PWM0SET,frequency);
	Set_duty(PWM0TIMCH,duty);
	return i;
}

void Pwm0::_pwmWrite(float duty)
{
	Set_duty(PWM0TIMCH,duty);
}

float Pwm0::_pwmWrite()
{
	return Read_duty(PWM0TIMCH);
}


int Pwm1::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(PWM1SET,frequency);
	Set_duty(PWM1TIMCH,duty);
	return i;
}

void Pwm1::_pwmWrite(float duty)
{
	Set_duty(PWM1TIMCH,duty);
}

float Pwm1::_pwmWrite()
{
	return Read_duty(PWM1TIMCH);
}


int Pwm2::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(PWM2SET,frequency);
	Set_duty(PWM2TIMCH,duty);
	return i;
}

void Pwm2::_pwmWrite(float duty)
{
	Set_duty(PWM2TIMCH,duty);
}

float Pwm2::_pwmWrite()
{
	return Read_duty(PWM2TIMCH);
}


int Pwm3::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(PWM3SET,frequency);
	Set_duty(PWM3TIMCH,duty);
	return i;
}

void Pwm3::_pwmWrite(float duty)
{
	Set_duty(PWM3TIMCH,duty);
}

float Pwm3::_pwmWrite()
{
	return Read_duty(PWM3TIMCH);
}


int Pwm4::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(PWM4SET,frequency);
	Set_duty(PWM4TIMCH,duty);
	return i;
}

void Pwm4::_pwmWrite(float duty)
{
	Set_duty(PWM4TIMCH,duty);
}

float Pwm4::_pwmWrite()
{
	return Read_duty(PWM4TIMCH);
}


int Pwm5::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(PWM5SET,frequency);
	Set_duty(PWM5TIMCH,duty);
	return i;
}

void Pwm5::_pwmWrite(float duty)
{
	Set_duty(PWM5TIMCH,duty);
}

float Pwm5::_pwmWrite()
{
	return Read_duty(PWM5TIMCH);
}


int Led2::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(LED2SET,frequency);
	Set_duty(LED2TIMCH,duty);
	return i;
}

void Led2::_pwmWrite(float duty)
{
	Set_duty(LED2TIMCH,duty);
}

float Led2::_pwmWrite()
{
	return Read_duty(LED2TIMCH);
}

int Led3::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(LED3SET,frequency);
	Set_duty(LED3TIMCH,duty);
	return i;
}

void Led3::_pwmWrite(float duty)
{
	Set_duty(LED3TIMCH,duty);
}

float Led3::_pwmWrite()
{
	return Read_duty(LED3TIMCH);
}


int Buzzer::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(BUZZERSET,frequency);
	Set_duty(BUZZERTIMCH,duty);
	return i;
}

void Buzzer::_pwmWrite(float duty)
{
	Set_duty(BUZZERTIMCH,duty);
}

float Buzzer::_pwmWrite()
{
	return Read_duty(BUZZERTIMCH);
}

#define SERIAL0TxRx	GPIOA,GPIO_Pin_2,GPIOA,GPIO_Pin_3
#define SERIAL0CH USART2
//#define SERIAL0TxRx GPIOD,GPIO_Pin_8,GPIOD,GPIO_Pin_9
//#define SERIAL0CH USART3
#define SERIAL1TxRx	GPIOB,GPIO_Pin_10,GPIOB,GPIO_Pin_11
#define SERIAL1CH USART3

SerialInterface *Serial0::interface;

int Serial0::_setup(int baudrate, SerialInterface &interfaceArg, int parity, int wordLength)
{
	Init_USART(SERIAL0CH,baudrate,SERIAL0TxRx,parity,wordLength);
	interface=&interfaceArg;
	interface->serialInterfaceSetup(this);
	return 0;
}

void Serial0::writeChar(char value)
{
	transmit(value);
}

void serial0_interrupt(){
	Serial0::interface->serialReadChar(USART_ReceiveData(SERIAL0CH));
}

void Serial0::transmit(char value){
	while(USART_GetFlagStatus(SERIAL0CH, USART_FLAG_TXE) == RESET);
	USART_SendData(SERIAL0CH, value);
}

extern "C" void USART2_IRQHandler(void){
	serial0_interrupt();
}

SerialInterface *Serial1::interface;

int Serial1::_setup(int baudrate, SerialInterface &interfaceArg, int parity, int wordLength)
{
	Init_USART(SERIAL1CH,baudrate,SERIAL1TxRx,parity,wordLength);
	interface=&interfaceArg;
	//interface->serialInterfaceSetup(transmit);
	interface->serialInterfaceSetup(this);
	return 0;
}

void serial1_interrupt(){
	Serial1::interface->serialReadChar(USART_ReceiveData(SERIAL1CH));
}

extern "C" void USART3_IRQHandler(void){
	serial1_interrupt();
}

void Serial1::writeChar(char value){
	transmit(value);
}

void Serial1::transmit(char value){
	while(USART_GetFlagStatus(SERIAL1CH, USART_FLAG_TXE) == RESET);
	USART_SendData(SERIAL1CH, value);
}

void std_char_out(char value){
	while(USART_GetFlagStatus(SERIAL0CH, USART_FLAG_TXE) == RESET);
	USART_SendData(SERIAL0CH, value);
}

int std_char_out_setup(){
	Serial0::interface=new SerialInterface();
	Init_USART(SERIAL0CH,9600,SERIAL0TxRx,0,8);
	return 0;
}


#define CAN_PORT GPIOD,GPIO_Pin_0,GPIOD,GPIO_Pin_1
#define CAN_NUMBER 1

CanInterface *Can0::canInterface[30];
int Can0::canInterfaceCursor=0;

Can0::Can0(){
	setuped=false;
	filter_number=4;
}

int  Can0::setup(){
	printf("can0 setup...");
	int returnValue=0;
	if(!setuped){
		Init_CAN(CAN_NUMBER,CAN_Mode_Normal,CAN_PORT); returnValue=0;
		if(returnValue==0) setuped=true;
		if(setuped)printf("done\n");
	}
	else{
		returnValue=0;
	}
	return returnValue;
}

int Can0::setupLoopBack(){
	int returnValue=0;
	if(!setuped){
		Init_CAN(CAN_NUMBER,CAN_Mode_LoopBack,CAN_PORT); returnValue=0;
		if(returnValue==0) setuped=true;
	}
	else{
		returnValue=0;
	}
	return returnValue;
}

int Can0::addInterface(CanInterface &interfaceArg){
	if(canInterfaceCursor>=30) return 1;
	canInterface[canInterfaceCursor++]=&interfaceArg;
	interfaceArg.canInterfaceSetup(this);
	return 0;
}

int Can0::setId(int id){
	int row=filter_number/4;
	filter[filter_number]=(short)id;
	printf("%s,set id:%x\n",__func__,id);
	Init_CANfilter(row           , CAN_LIST               , filter[row*4+0], CAN_DATA        , filter[row*4+1], CAN_DATA,         filter[row*4+2], CAN_DATA,         filter[row*4+3], CAN_DATA);
	filter_number++;
	return 0;
}
int Can0::setIdAll(){
	Init_CANfilter(10           , CAN_MASK               ,0, CAN_DATA        , 0, CAN_DATA,         0, CAN_DATA,        0,CAN_DATA);
	return 0;
}

int Can0::read(int id,int number,unsigned char data[8]){
//	printf("id:%x length:%x data:%x,%x,%x,%x,%x,%x,%x,%x\n",id,number,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
	for(int i=0;i<canInterfaceCursor;i++) if(canInterface[i]->canId(id)) canInterface[i]->canRead(id,number,data);
	return 0;
}

int Can0::write(int id,int number,unsigned char data[8]){
	CanTxMsg can_tx_flame;
	can_tx_flame.StdId=id;
	can_tx_flame.ExtId=0;
	can_tx_flame.IDE=CAN_Id_Standard;
	if(number!=0)can_tx_flame.RTR=CAN_RTR_Data;
	else can_tx_flame.RTR=CAN_RTR_Remote;
	can_tx_flame.DLC=(uint8_t)number;
	can_tx_flame.Data[0]=data[0];
	can_tx_flame.Data[1]=data[1];
	can_tx_flame.Data[2]=data[2];
	can_tx_flame.Data[3]=data[3];
	can_tx_flame.Data[4]=data[4];
	can_tx_flame.Data[5]=data[5];
	can_tx_flame.Data[6]=data[6];
	can_tx_flame.Data[7]=data[7];
	printf("can0_transmit id:%x length:%d data:%x,%x,%x,%x,%x,%x,%x,%x writing...",(unsigned int)can_tx_flame.StdId,can_tx_flame.DLC,can_tx_flame.Data[0],can_tx_flame.Data[1],can_tx_flame.Data[2],can_tx_flame.Data[3],can_tx_flame.Data[4],can_tx_flame.Data[5],can_tx_flame.Data[6],can_tx_flame.Data[7]);
	send_can1(&can_tx_flame);
	printf("done.\n");
	return 0;
}

CanRxMsg can_rx_flame;
void Can0_Interrupt(){
	if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)){
		CAN_Receive(CAN1, CAN_FIFO0, &can_rx_flame);
		Can0::read((int)can_rx_flame.StdId,(int)can_rx_flame.DLC,can_rx_flame.Data);
	}
}

extern "C" void CAN1_RX0_IRQHandler(void){
	Can0_Interrupt();
}

#define I2C_PORT_SCL_SDA		GPIOB,GPIO_Pin_10,GPIO_Pin_11

int I2c0::directionFlag;
int I2c0::rxSlaveAddress;
int I2c0::txSlaveAddress;
int I2c0::txBufferSize;
int I2c0::rxBufferSize;
unsigned char I2c0::sendData[20];
I2cInterface * I2c0::i2cInterface[10];
int I2c0::i2cInterfaceCursor=0;
RingBuffer<I2c_t,512> I2c0::txBuf;

I2c0::I2c0(){
	directionFlag=true;
	rxSlaveAddress=0;
	txSlaveAddress=0;
	txBufferSize=0;
	rxBufferSize=0;
}

int I2c0::setup(){
	static bool flag=false;
	time=millis();
	if(!flag){
		Init_i2c(I2C2,I2C_PORT_SCL_SDA);delay_ms(10);
		flag=true;
		return 0;
	}
	return 1;
}

int I2c0::addInterface(I2cInterface &interfaceArg){
	if(i2cInterfaceCursor>=10) return 1;
	i2cInterface[i2cInterfaceCursor++]=&interfaceArg;
	interfaceArg.i2cInterfaceSetup(this);
	return 0;
}

int I2c0::write(char address,unsigned char *value,char dataSize,bool txrx){
	I2c_t i2c;

	if(getBufferFlag()==0){
		if(txBuf.isEmpty()==1){
			txSlaveAddress=address;
			txBufferSize=dataSize;
			for(int i=0;i<dataSize;i++){
				sendData[i]=*(value+i);
			}
			directionFlag=txrx;
			I2C_GenerateSTART(I2C2,ENABLE);
			return 0;
		}
	}
	i2c.address=address;
	for(int i=0;i<dataSize;i++){
		i2c.data[i]=*(value+i);
	}
	i2c.dataSize=dataSize;
	i2c.txrxFlag=txrx;
	while(txBuf.write(i2c)){
		cycle();//printf("max\n");
	}

	return 0;
}

int I2c0::getBufferFlag(){
	return rxBufferSize+txBufferSize;
}

void I2c0_Interrupt(void){
	static int TxAddress=0;
	static int RxAddress=0;
	static int TxDataNum=0;
	static int RxDataNum=0;
	static unsigned char rxData[10]={0};

	switch (I2C_GetLastEvent(I2C2)){
		case I2C_EVENT_MASTER_MODE_SELECT:
			if(I2c0::directionFlag==TX){
				TxAddress=I2c0::txSlaveAddress;
				I2C_Send7bitAddress(I2C2, TxAddress, I2C_Direction_Transmitter);
			}else if(I2c0::directionFlag==RX){
				RxAddress=I2c0::rxSlaveAddress;
				I2C_Send7bitAddress(I2C2, RxAddress, I2C_Direction_Receiver);
			}
			break;
		case I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED:
			I2C_SendData(I2C2, I2c0::sendData[TxDataNum++]);
			break;
		case I2C_EVENT_MASTER_BYTE_TRANSMITTED:
			if(TxDataNum<I2c0::txBufferSize){
				I2C_SendData(I2C2, I2c0::sendData[TxDataNum++]);
				if(I2c0::txBufferSize-TxDataNum<1)
					I2C_GenerateSTOP(I2C2, ENABLE);
			}else{
				int i;
				for(i=0;i<I2c0::i2cInterfaceCursor;i++){
					if(I2c0::i2cInterface[i]->i2cAddress(TxAddress)){
						I2c0::i2cInterface[i]->i2cReStartSend(I2c0::sendData[0]);
					}
				}
				TxDataNum=0;
				I2c0::txBufferSize=0;
			}
			break;
	 	case I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED:
	    		break;
		case I2C_EVENT_MASTER_BYTE_RECEIVED:
			rxData[RxDataNum++]=I2C_ReceiveData(I2C2);
			if(I2c0::rxBufferSize==RxDataNum+1){
				I2C_AcknowledgeConfig(I2C2, DISABLE);
				I2C_GenerateSTOP(I2C2, ENABLE);
			}
			if(I2c0::rxBufferSize-RxDataNum<1){
				RxDataNum=0;
				I2C_AcknowledgeConfig(I2C2, ENABLE);
				I2c0::rxBufferSize=0;
				int i;
				for(i=0;i<I2c0::i2cInterfaceCursor;i++){
					if(I2c0::i2cInterface[i]->i2cAddress(RxAddress)){
						I2c0::i2cInterface[i]->i2cRead(rxData);
					}
				}
			}
			break;
		default:
			break;
	}
}

void I2c0::startI2c(){
	if(txBuf.isEmpty()==0){
		I2c_t i2c;i2c=txBuf.read();
		txSlaveAddress=i2c.address;
		txBufferSize=i2c.dataSize;
		for(int i=0;i<txBufferSize;i++){
			sendData[i]=i2c.data[i];
		}
		directionFlag=i2c.txrxFlag;
		I2C_GenerateSTART(I2C2,ENABLE);
	}
}

void I2c0::cycle(){
	if(getBufferFlag()==0){
		if(millis()-time>=10){
			time=millis();
			startI2c();
		}
	}else{
		time=millis();
	}
}

extern "C" void I2C2_EV_IRQHandler(void){
	I2c0_Interrupt();
}
#endif