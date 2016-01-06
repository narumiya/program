#include "dual_shock.hpp"
#include <math.h>
#include "mcutime.h"
static float Value_wr_data(char c, float num, int mode);
static void Write_value(char c, float num);
static float Read_value(char c);
static void Receive_order_c(char character);

#define VYFFER_LENGTH	100
#define END '#'					//通信データの終端文字
#define RECEIVE_STR_COLUMN 32	//1データあたりの最大文字数		例: a123# (6文字)
#define READ_MODE 0
#define WRITE_MODE 1

#define CAN_CONTROLLER_ID	0x003

int DualShock::canRead(int id,int number,unsigned char data[8]){
	uint8_t i;

	for(i=0; i < number; i+=2){

		switch(data[i]){	//i=key i+1=value //i+2=#

		case start_ch: 		psbutton.start.value		= data[i+1];
		break;
		case select_ch:		psbutton.select.value 	= data[i+1];
		break;
		case left_x_ch:		psbutton.left_x.value 	= data[i+1];
		break;
		case left_y_ch:		psbutton.left_y.value 	= data[i+1];
		break;
		case right_x_ch:	psbutton.right_x.value 	= data[i+1];
		break;
		case right_y_ch:	psbutton.right_y.value 	= data[i+1];
		break;
		case l1_ch:    		psbutton.L1.value 		= data[i+1];
		break;
		case l2_ch:			psbutton.L2.value 		= data[i+1];
		break;
		case r1_ch:			psbutton.R1.value 		= data[i+1];
		break;
		case r2_ch:			psbutton.R2.value 		= data[i+1];
		break;
		case triangle_ch:	psbutton.Triangle.value 	= data[i+1];
		break;
		case circle_ch:		psbutton.Circle.value 	= data[i+1];
		break;
		case cross_ch:		psbutton.Cross.value 		= data[i+1];
		break;
		case square_ch:		psbutton.Square.value 	= data[i+1];
		break;
		case up_ch:			psbutton.Up.value 		= data[i+1];
		break;
		case right_ch:		psbutton.Right.value 		= data[i+1];
		break;
		case down_ch:		psbutton.Down.value 		= data[i+1];
		break;
		case left_ch:		psbutton.Left.value 		= data[i+1];
		break;
		case pitch_ch:		psbutton.Pitch.value 		= data[i+1];
		if(psbutton.Pitch.value!=oldPitch) time=millis();
		oldRoll=psbutton.Roll.value;//書き加えた
		break;
		case roll_ch:		psbutton.Roll.value 		= data[i+1];
		if(psbutton.Roll.value!=oldRoll) time=millis();
		oldPitch=psbutton.Pitch.value;//書き加えた
		break;
		default:
			break;
		}
	}
	return 0;
}

void DualShock::serialReadChar(char data){
	Receive_order_c(data);
	psbutton.left_x.value = Read_value(LEFT_X);
	psbutton.left_y.value 	=Read_value(LEFT_Y);
	psbutton.right_x.value 	=Read_value(RIGHT_X);
	psbutton.right_y.value 	=Read_value(RIGHT_Y);
	psbutton.Up.value 		=Read_value(KEY_UP);
	psbutton.Right.value 		=Read_value(KEY_RIGHT);
	psbutton.Down.value 		=Read_value(KEY_DOWN);
	psbutton.Left.value 		=Read_value(KEY_LEFT);
	psbutton.Triangle.value 	=Read_value(KEY_TRIANGLE);
	psbutton.Circle.value 	=Read_value(KEY_CIRCLE);
	psbutton.Cross.value 		=Read_value(KEY_CROSS);
	psbutton.Square.value 	=Read_value(KEY_SQUARE);
	//	Read_value(KEY_PS);
	psbutton.start.value		=Read_value(KEY_START);
	psbutton.Roll.value 		=Read_value(ACCEL_X);
	psbutton.Pitch.value 		=Read_value(ACCEL_Y);
	psbutton.L1.value 		=Read_value(KEY_L1);
	psbutton.R1.value 		=Read_value(KEY_R1);
	psbutton.L2.value 		=Read_value(KEY_L2);
	psbutton.R2.value 		=Read_value(KEY_R2);
	psbutton.select.value 	=Read_value(KEY_SELECT);
	if(psbutton.Roll.value!=oldRoll) time=millis();
	if(psbutton.Pitch.value!=oldPitch) time=millis();
	//書き加えた
	oldRoll=psbutton.Roll.value;
	oldPitch=psbutton.Pitch.value;
}

DualShock::DualShock(Can &can){
	mode=modeCan;
	can.addInterface(this);

	psbutton.start.value=0;
	psbutton.select.value=0;
	psbutton.L1.value=0;
	psbutton.L2.value=0;
	psbutton.R1.value=0;
	psbutton.R2.value=0;
	psbutton.Triangle.value=0;
	psbutton.Circle.value=0;
	psbutton.Cross.value=0;
	psbutton.Square.value=0;
	psbutton.Up.value=0;
	psbutton.Right.value=0;
	psbutton.Down.value=0;
	psbutton.Left.value=0;
	psbutton.CError.value=0;
	psbutton.Pitch.value=0;
	psbutton.Roll.value=0;
	psbutton.left_x.value=127;
	psbutton.left_y.value=127;
	psbutton.right_x.value=127;
	psbutton.right_y.value=127;

	psbutton.start.tolerance=0;
	psbutton.select.tolerance=0;
	psbutton.L1.tolerance=0;
	psbutton.L2.tolerance=0;
	psbutton.R1.tolerance=0;
	psbutton.R2.tolerance=0;
	psbutton.Triangle.tolerance=0;
	psbutton.Circle.tolerance=0;
	psbutton.Cross.tolerance=0;
	psbutton.Square.tolerance=0;
	psbutton.Up.tolerance=0;
	psbutton.Right.tolerance=0;
	psbutton.Down.tolerance=0;
	psbutton.Left.tolerance=0;
	psbutton.CError.tolerance=0;
	psbutton.Pitch.tolerance=0;
	psbutton.Roll.tolerance=0;
	psbutton.left_x.tolerance=0;
	psbutton.left_y.tolerance=0;
	psbutton.right_x.tolerance=0;
	psbutton.right_y.tolerance=0;

	time=millis();
	oldPitch=0;
	oldRoll=0;
	disconnectTimeData=500;
}
DualShock::DualShock(Serial &serial){
	mode=modeSerial;
	this->serial=&serial;
	psbutton.start.value=0;
	psbutton.select.value=0;
	psbutton.L1.value=0;
	psbutton.L2.value=0;
	psbutton.R1.value=0;
	psbutton.R2.value=0;
	psbutton.Triangle.value=0;
	psbutton.Circle.value=0;
	psbutton.Cross.value=0;
	psbutton.Square.value=0;
	psbutton.Up.value=0;
	psbutton.Right.value=0;
	psbutton.Down.value=0;
	psbutton.Left.value=0;
	psbutton.CError.value=0;
	psbutton.Pitch.value=0;
	psbutton.Roll.value=0;
	psbutton.left_x.value=127;
	psbutton.left_y.value=127;
	psbutton.right_x.value=127;
	psbutton.right_y.value=127;

	psbutton.start.tolerance=0;
	psbutton.select.tolerance=0;
	psbutton.L1.tolerance=0;
	psbutton.L2.tolerance=0;
	psbutton.R1.tolerance=0;
	psbutton.R2.tolerance=0;
	psbutton.Triangle.tolerance=0;
	psbutton.Circle.tolerance=0;
	psbutton.Cross.tolerance=0;
	psbutton.Square.tolerance=0;
	psbutton.Up.tolerance=0;
	psbutton.Right.tolerance=0;
	psbutton.Down.tolerance=0;
	psbutton.Left.tolerance=0;
	psbutton.CError.tolerance=0;
	psbutton.Pitch.tolerance=0;
	psbutton.Roll.tolerance=0;
	psbutton.left_x.tolerance=0;
	psbutton.left_y.tolerance=0;
	psbutton.right_x.tolerance=0;
	psbutton.right_y.tolerance=0;

	time=millis();
	oldPitch=0;
	oldRoll=0;
	disconnectTimeData=500;
}
/*
DualShock::DualShock(int idArg){
	canId=idArg;
	psbutton.start.value=0;
	psbutton.select.value=0;
	psbutton.L1.value=0;
	psbutton.L2.value=0;
	psbutton.R1.value=0;
	psbutton.R2.value=0;
	psbutton.Triangle.value=0;
	psbutton.Circle.value=0;
	psbutton.Cross.value=0;
	psbutton.Square.value=0;
	psbutton.Up.value=0;
	psbutton.Right.value=0;
	psbutton.Down.value=0;
	psbutton.Left.value=0;
	psbutton.CError.value=0;
	psbutton.Pitch.value=0;
	psbutton.Roll.value=0;
	psbutton.left_x.value=0;
	psbutton.left_y.value=0;
	psbutton.right_x.value=0;
	psbutton.right_y.value=0;

	psbutton.start.tolerance=0;
	psbutton.select.tolerance=0;
	psbutton.L1.tolerance=0;
	psbutton.L2.tolerance=0;
	psbutton.R1.tolerance=0;
	psbutton.R2.tolerance=0;
	psbutton.Triangle.tolerance=0;
	psbutton.Circle.tolerance=0;
	psbutton.Cross.tolerance=0;
	psbutton.Square.tolerance=0;
	psbutton.Up.tolerance=0;
	psbutton.Right.tolerance=0;
	psbutton.Down.tolerance=0;
	psbutton.Left.tolerance=0;
	psbutton.CError.tolerance=0;
	psbutton.Pitch.tolerance=0;
	psbutton.Roll.tolerance=0;
	psbutton.left_x.tolerance=0;
	psbutton.left_y.tolerance=0;
	psbutton.right_x.tolerance=0;
	psbutton.right_y.tolerance=0;

	time=millis();
	oldPitch=0;
	oldRoll=0;
	disconnectTimeData=500;
}
*/
int DualShock::setup(){
	if(mode==modeCan){
		if(canSetup()) return 1;
		canSetId(CAN_CONTROLLER_ID);
	}else if(mode==modeSerial){
		serial->setup(115200,(*this));
	}
	return 0;
}

int DualShock::canId(int id){
	if(CAN_CONTROLLER_ID==id) return 1;
	return 0;
}

float DualShock::lx(void){
	float value=((DUAL_SHOCK_KEY_MAX_VALUE / 2.0) - psbutton.left_y.value) / (DUAL_SHOCK_KEY_MAX_VALUE / 2.0);
	if(fabs(value) < psbutton.left_y.tolerance)value=0.0;
	return(value);
}
float DualShock::ly(void){
	float value=((DUAL_SHOCK_KEY_MAX_VALUE / 2.0) - psbutton.left_x.value) / (DUAL_SHOCK_KEY_MAX_VALUE / 2.0);
	if(fabs(value) < psbutton.left_x.tolerance)value=0.0;
	return(value);
}
float DualShock::rx(void){
	float value=((DUAL_SHOCK_KEY_MAX_VALUE / 2.0) - psbutton.right_y.value) / (DUAL_SHOCK_KEY_MAX_VALUE / 2.0);
	if(fabs(value) < psbutton.right_y.tolerance)value=0.0;
	return(value);
}
float DualShock::ry(void){
	float value=((DUAL_SHOCK_KEY_MAX_VALUE / 2.0) - psbutton.right_x.value) / (DUAL_SHOCK_KEY_MAX_VALUE / 2.0);
	if(fabs(value) < psbutton.right_x.tolerance)value=0.0;
	return(value);
}
float DualShock::up(void){
	float value=psbutton.Up.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.Up.tolerance)value=0.0;
	return(value);
}
#include <stdio.h>
float DualShock::right(void){
	float value=psbutton.Right.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.Right.tolerance)value=0.0;
	return(value);
}
float DualShock::down(void){
	float value=psbutton.Down.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.Down.tolerance)value=0.0;
	return(value);
}
float DualShock::left(void){
	float value=psbutton.Left.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.Left.tolerance)value=0.0;
	return(value);
}
float DualShock::triangle(void){
	float value=psbutton.Triangle.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.Triangle.tolerance)value=0.0;
	return(value);
}
float DualShock::circle(void){
	float value=psbutton.Circle.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.Circle.tolerance)value=0.0;
	return(value);
}
float DualShock::cross(void){
	float value=psbutton.Cross.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.Cross.tolerance)value=0.0;
	return(value);
}
float DualShock::square(void){
	float value=psbutton.Square.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.Square.tolerance)value=0.0;
	return(value);
}

float DualShock::l1(void){
	float value=psbutton.L1.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.L1.tolerance)value=0.0;
	return(value);
}
float DualShock::r1(void){
	float value=psbutton.R1.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.R1.tolerance)value=0.0;
	return(value);
}
float DualShock::l2(void){
	float value=psbutton.L2.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.L2.tolerance)value=0.0;
	return(value);
}
float DualShock::r2(void){
	float value=psbutton.R2.value / DUAL_SHOCK_KEY_MAX_VALUE;
	if(fabs(value) < psbutton.R2.tolerance)value=0.0;
	return(value);
}
int DualShock::select(void){return(psbutton.select.value);}
int DualShock::start(void){return(psbutton.start.value);}
float DualShock::accelX(void){return(psbutton.Roll.value / DUAL_SHOCK_KEY_MAX_VALUE);}
float DualShock::accelY(void){return(psbutton.Pitch.value / DUAL_SHOCK_KEY_MAX_VALUE);}

void DualShock::rumbeHigh(void){
	unsigned char data[8]={rumble_ch,1};
	canWrite(CAN_CONTROLLER_ID,2,data);
};
void DualShock::rumbleLow(void){
	unsigned char data[8]={rumble_ch,2};
	canWrite(CAN_CONTROLLER_ID,2,data);
};
void DualShock::rumbleStop(void){
	unsigned char data[8]={rumble_ch,0};
	canWrite(CAN_CONTROLLER_ID,2,data);
};

void DualShock::setStickTolerance(float toleranceArg){
	psbutton.left_x.tolerance=toleranceArg;
	psbutton.left_y.tolerance=toleranceArg;
	psbutton.right_x.tolerance=toleranceArg;
	psbutton.right_y.tolerance=toleranceArg;
}

void DualShock::setArrowKeyTolerance(float toleranceArg){
	psbutton.Up.tolerance=toleranceArg;
	psbutton.Right.tolerance=toleranceArg;
	psbutton.Down.tolerance=toleranceArg;
	psbutton.Left.tolerance=toleranceArg;
}

void DualShock::setSymbolKeyTolerance(float toleranceArg){
	psbutton.Circle.tolerance=toleranceArg;
	psbutton.Cross.tolerance=toleranceArg;
	psbutton.Square.tolerance=toleranceArg;
	psbutton.Triangle.tolerance=toleranceArg;
}

void DualShock::setSide1KeyTolerance(float toleranceArg){
	psbutton.R1.tolerance=toleranceArg;
	psbutton.L1.tolerance=toleranceArg;
}

void DualShock::setSide2KeyTolerance(float toleranceArg){
	psbutton.R2.tolerance=toleranceArg;
	psbutton.L2.tolerance=toleranceArg;
}

void DualShock::setStartKeyTolerance(float toleranceArg){
	psbutton.start.tolerance=toleranceArg;
}

//------------------------------------------------
// title:	格納データ関数
// return:	読み込みデータ
// argument:char 	データ格納場選択
//			float	書き込み時のデータ
//			int		読み書きのモード選択
// coders:	桐生
static float Value_wr_data(char c, float num, int mode){
	float out_data = 0;
	static float atoz_value[26] = { 0 };
	static float AtoZ_value[26] = { 0 };

	if ((c >= 'a') && (c <= 'z')){
		if (mode == WRITE_MODE)		{ atoz_value[(int)(c - 'a')] = num; }
		else if (mode == READ_MODE)	{ out_data = atoz_value[(int)(c - 'a')]; }
	}
	else if ((c >= 'A') && (c <= 'Z')){
		if (mode == WRITE_MODE)		{ AtoZ_value[(int)(c - 'A')] = num; }
		else if (mode == READ_MODE)	{ out_data = AtoZ_value[(int)(c - 'A')]; }
	}

	return out_data;
}

//--------------------------------------------------------------------
// 格納データの保存

//------------------------------------------------
// title:	格納データを変更する関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
static void Write_value(char c, float num){
	Value_wr_data(c, num, WRITE_MODE);
}
//------------------------------------------------
// title:	格納データを読み取る関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
static float Read_value(char c){
	return (Value_wr_data(c, 0, READ_MODE));
}
//------------------------------------------------
// title:	受信データを保存する関数
// return:	なし
// argument:char 	受信データ
// coders:	桐生
static void Receive_order_c(char character){
	//受信データ方式
	//	1.文字(a-z,A-Z)
	//	2.データ(float型)
	//	3.END(ヘッダーファイルで定義)
	//	この順のデータをこの関数では処理します。
	static char c = 0;
	static float num_data = 0;
	static int
	point_ct = 0,							 //文字を文字列のどこに格納するか
	flont_char_flag = 0,
	minus_flag = 0,
	point_flag = 0;							 //小数点以下が含まれているか否か
	int reset = 0;										 //処理のリセットをするか否か

	if (character == END){
		if (minus_flag == 1)	num_data *= (-1);
		Write_value(c, num_data);
		reset = 1;
		c = 0;
	}
	else{
		if ((character >= '0') && (character <= '9')){
			flont_char_flag = 0;
			if (point_flag == 0){
				num_data = num_data * 10 + (character - '0');
			}
			else{
				point_ct++;
				num_data += (character - '0')*pow(0.1, point_ct);
			}
		}
		else if (((character >= 'a') && (character <= 'z')) || ((character >= 'A') && (character <= 'Z'))){
			reset = 1;
			c = character;
			flont_char_flag = 1;
		}
		else if (character == '-' && flont_char_flag == 1){
			if (minus_flag == 0)	minus_flag = 1;
			else				minus_flag = 0;
		}
		else if (character == '.' && flont_char_flag == 0){
			point_flag = 1;
		}
	}
	if (reset == 1){
		num_data = 0;
		point_ct = 0;
		point_flag = 0;
		minus_flag = 0;
	}
}

int DualShock::disconnect(){
	if(millis()-time>disconnectTimeData) return 1;
	else return 0;
}

void DualShock::disconnectTime(long timeArg){
	disconnectTimeData=timeArg;
}

void DualShock::cycle(){
	if(disconnect()){
		psbutton.start.value=0;
		psbutton.select.value=0;
		psbutton.L1.value=0;
		psbutton.L2.value=0;
		psbutton.R1.value=0;
		psbutton.R2.value=0;
		psbutton.Triangle.value=0;
		psbutton.Circle.value=0;
		psbutton.Cross.value=0;
		psbutton.Square.value=0;
		psbutton.Up.value=0;
		psbutton.Right.value=0;
		psbutton.Down.value=0;
		psbutton.Left.value=0;
		psbutton.CError.value=0;
		psbutton.Pitch.value=0;
		psbutton.Roll.value=0;
		psbutton.left_x.value=127;
		psbutton.left_y.value=127;
		psbutton.right_x.value=127;
		psbutton.right_y.value=127;
	}
}
