#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

extern "C" {
#include "config_usart.h"
#include "config_encoder.h"
#include "config_systick.h"
#include "config_usart.h"
#include "config_pwm.h"
#include "config_port.h"
#include "config_adc.h"
#include "config_can.h"
}

#include "pin.hpp"

#define LED0		GPIOD,GPIO_Pin_14
#define LED1		GPIOD,GPIO_Pin_15


#define AD0		GPIOC,GPIO_Pin_0
#define AD1		GPIOC,GPIO_Pin_1
#define AD2		GPIOC,GPIO_Pin_2
#define AD3		GPIOC,GPIO_Pin_3
#define AD4		GPIOE,GPIO_Pin_12


#define PWM4				GPIOE,GPIO_Pin_8//GPIOE,GPIO_Pin_6
#define PWM4SET			TIM1,PWM4
#define PWM4TIMCH		TIM1,1
#define CWIO4				GPIOB,GPIO_Pin_2//GPIOD,GPIO_Pin_11
#define CCWIO4			GPIOE,GPIO_Pin_10//GPIOD,GPIO_Pin_10

#define PWM5				GPIOA,GPIO_Pin_2//GPIOE,GPIO_Pin_5
#define PWM5SET			TIM2,PWM5
#define PWM5TIMCH		TIM2,3
#define CWIO5				GPIOE,GPIO_Pin_6//GPIOB,GPIO_Pin_1
#define CCWIO5			GPIOE,GPIO_Pin_7//GPIOB,GPIO_Pin_2

#define PWM6				GPIOE,GPIO_Pin_14//GPIOE,GPIO_Pin_6
#define PWM6SET			TIM1,PWM6
#define PWM6TIMCH		TIM1,4
#define CWIO6				GPIOB,GPIO_Pin_10//GPIOD,GPIO_Pin_11
#define CCWIO6			GPIOB,GPIO_Pin_12//GPIOD,GPIO_Pin_10

#define PWM7				GPIOE,GPIO_Pin_13//GPIOE,GPIO_Pin_5
#define PWM7SET			TIM1,PWM7
#define PWM7TIMCH		TIM1,3
#define CWIO7				GPIOD,GPIO_Pin_12//GPIOB,GPIO_Pin_1
#define CCWIO7			GPIOE,GPIO_Pin_15//GPIOB,GPIO_Pin_2


#define ENC0TIM	TIM8
#define ENC0			GPIOC,GPIO_Pin_6 | GPIO_Pin_7
#define ENC1TIM	TIM4
#define ENC1			GPIOB,GPIO_Pin_6 | GPIO_Pin_7		//PA6 input‚Å‚«‚È‚¢
#define ENC2TIM	TIM3
#define ENC2			GPIOB,GPIO_Pin_4 | GPIO_Pin_5
#define ENC3TIM	TIM5
#define ENC3			GPIOA,GPIO_Pin_0 | GPIO_Pin_1


#define SERIAL0TxRx		GPIOD,GPIO_Pin_5,GPIOD,GPIO_Pin_6
#define SERIAL0CH 		USART2
#define SERIAL1TxRx		GPIOA,GPIO_Pin_9,GPIOA,GPIO_Pin_10
#define SERIAL1CH 		USART1
#define SERIAL2TxRx		GPIOD,GPIO_Pin_8,GPIOD,GPIO_Pin_9
#define SERIAL2CH 		USART3


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


int Cw4:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO4);
}

void Cw4::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO4);
	}else{
		GPIO_SetBits(CWIO4);
	}
}

int Cw4::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO4);
}

int Cw4::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Cw4::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Cw4::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO4, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Cw4::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO4, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Ccw4:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO4);
}

void Ccw4::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO4);
	}else{
		GPIO_SetBits(CCWIO4);
	}
}

int Ccw4::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO4);
}

int Ccw4::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Ccw4::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Ccw4::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO4, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Ccw4::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO4, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Cw5:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO5);
}

void Cw5::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO5);
	}else{
		GPIO_SetBits(CWIO5);
	}
}

int Cw5::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO5);
}

int Cw5::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Cw5::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Cw5::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO5, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Cw5::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO5, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Ccw5:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO5);
}

void Ccw5::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO5);
	}else{
		GPIO_SetBits(CCWIO5);
	}
}

int Ccw5::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO5);
}

int Ccw5::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Ccw5::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Ccw5::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO5, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Ccw5::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO5, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Cw6:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO6);
}

void Cw6::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO6);
	}else{
		GPIO_SetBits(CWIO6);
	}
}

int Cw6::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO6);
}

int Cw6::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO6, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Cw6::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO6, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Cw6::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO6, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Cw6::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO6, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Ccw6:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO6);
}

void Ccw6::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO6);
	}else{
		GPIO_SetBits(CCWIO6);
	}
}

int Ccw6::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO6);
}

int Ccw6::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO6, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Ccw6::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO6, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Ccw6::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO6, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Ccw6::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO6, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Cw7:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CWIO7);
}

void Cw7::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CWIO7);
	}else{
		GPIO_SetBits(CWIO7);
	}
}

int Cw7::_digitalRead()
{
	return GPIO_ReadInputDataBit(CWIO7);
}

int Cw7::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CWIO7, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Cw7::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CWIO7, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Cw7::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CWIO7, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Cw7::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CWIO7, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Ccw7:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(CCWIO7);
}

void Ccw7::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(CCWIO7);
	}else{
		GPIO_SetBits(CCWIO7);
	}
}

int Ccw7::_digitalRead()
{
	return GPIO_ReadInputDataBit(CCWIO7);
}

int Ccw7::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, CCWIO7, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Ccw7::_setupDigitalOut()
{
	Init_port(GPIO_Mode_OUT, CCWIO7, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Ccw7::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, CCWIO7, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Ccw7::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, CCWIO7, GPIO_PuPd_DOWN, GPIO_OType_PP);
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

int Pwm6:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(PWM6);
}

void Pwm6::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(PWM6);
	}else{
		GPIO_SetBits(PWM6);
	}
}

int Pwm6::_digitalRead()
{
	return GPIO_ReadInputDataBit(PWM6);
}

int Pwm6::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, PWM6, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm6::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, PWM6, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm6::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, PWM6, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Pwm6::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, PWM6, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Pwm7:: _digitalWrite()
{
	return GPIO_ReadOutputDataBit(PWM7);
}

void Pwm7::_digitalWrite(int value)
{
	if(value==0){
		GPIO_ResetBits(PWM7);
	}else{
		GPIO_SetBits(PWM7);
	}
}

int Pwm7::_digitalRead()
{
	return GPIO_ReadInputDataBit(PWM7);
}

int Pwm7::_setupDigitalIn()
{
	Init_port(GPIO_Mode_IN, PWM7, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm7::_setupDigitalOut()
{
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, PWM7, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Pwm7::_setupDigitalInPullUp()
{
	Init_port(GPIO_Mode_IN, PWM7, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Pwm7::_setupDigitalInPullDown()
{
	Init_port(GPIO_Mode_IN, PWM7, GPIO_PuPd_DOWN, GPIO_OType_PP);
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

int Enc3::setup()
{
	Init_encoder(ENC3TIM,ENC3);
	return 0;
}

int Enc3::count()
{
	if(revFlag) return -Select_encoder_count(ENC3TIM);
	else return Select_encoder_count(ENC3TIM);
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

int Pwm6::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(PWM6SET,frequency);
	Set_duty(PWM6TIMCH,duty);
	return i;
}

void Pwm6::_pwmWrite(float duty)
{
	Set_duty(PWM6TIMCH,duty);
}

float Pwm6::_pwmWrite()
{
	return Read_duty(PWM6TIMCH);
}

int Pwm7::_setupPwmOut(float frequency, float duty)
{
	int i;
	mode = MODE_PWM;
	i=Init_PWM(PWM7SET,frequency);
	Set_duty(PWM7TIMCH,duty);
	return i;
}

void Pwm7::_pwmWrite(float duty)
{
	Set_duty(PWM7TIMCH,duty);
}

float Pwm7::_pwmWrite()
{
	return Read_duty(PWM7TIMCH);
}


SerialInterface *Serial0::interface;

int Serial0::_setup(int baudrate, SerialInterface &interfaceArg, int parity, int wordLength)
{
	Init_USART(SERIAL0CH,baudrate,SERIAL0TxRx,parity,wordLength);
	interface=&interfaceArg;
	interface->serialInterfaceSetup(transmit);
	return 0;
}

void Serial0::charWrite(char value)
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
	interface->serialInterfaceSetup(transmit);
	return 0;
}

void Serial1::charWrite(char value)
{
	transmit(value);
}

void serial1_interrupt(){
	Serial1::interface->serialReadChar(USART_ReceiveData(SERIAL1CH));
}

void Serial1::transmit(char value){
	while(USART_GetFlagStatus(SERIAL1CH, USART_FLAG_TXE) == RESET);
	USART_SendData(SERIAL1CH, value);
}

extern "C" void USART1_IRQHandler(void){
	serial1_interrupt();
}

SerialInterface *Serial2::interface;

int Serial2::_setup(int baudrate, SerialInterface &interfaceArg, int parity, int wordLength)
{
	Init_USART(SERIAL2CH,baudrate,SERIAL2TxRx,parity,wordLength);
	interface=&interfaceArg;
	interface->serialInterfaceSetup(transmit);
	return 0;
}

void Serial2::charWrite(char value)
{
	transmit(value);
}

void serial2_interrupt(){
	Serial2::interface->serialReadChar(USART_ReceiveData(SERIAL2CH));
}

void Serial2::transmit(char value){
	while(USART_GetFlagStatus(SERIAL2CH, USART_FLAG_TXE) == RESET);
	USART_SendData(SERIAL2CH, value);
}

extern "C" void USART3_IRQHandler(void){
	serial2_interrupt();
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

extern "C" void CAN1_RX0_IRQHandler(void)
{
	Can0_Interrupt();
}
