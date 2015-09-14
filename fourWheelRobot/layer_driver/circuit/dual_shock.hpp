#ifndef DUALSHOCKPLUS_HPP
#define DUALSHOCKPLUS_HPP
/*******************************************
 * dual_shock_plus ver0.1 2015/3/5
 * Classes of can encoder node for ichigo system.
 *
 * [Dependency]
 * canplus
 * usartplus
 * stdint
 *
 * [Note]
 * Rumble available.
 *
 * [Change history]
 * ver1.0 2015/ 3/ 5 The first version.
 ******************************************/
#include "can.hpp"
#include "serial.hpp"
#include <stdint.h>
#define DUAL_SHOCK_KEY_MAX_VALUE 255.0
class DualShock:public CanInterface,public SerialInterface{
private:
	//Dualshock3のデータ解析用
	//この列挙型の値はArduino側の設定と合わせる
	//どの値を読み取ったかを識別する記号。上から(a,b,c...)と続いている
	//ps3_can12
	enum{
		modeCan,
		modeSerial
	};
	enum {
		start_ch = 'a',
		select_ch,
		left_x_ch,
		left_y_ch,
		right_x_ch,
		right_y_ch,
		l1_ch,l2_ch,
		r1_ch,r2_ch,
		triangle_ch,
		circle_ch,
		cross_ch,
		square_ch,
		up_ch,
		down_ch,
		right_ch,
		left_ch,
		pitch_ch,
		roll_ch,
		rumble_ch,
		CError
	}Mnemonic;
	enum{
		LEFT_X		=	'a',//stick 左 上1.0 下-1.0
		LEFT_Y		=	'A',//stick 左 右1.0 左-1.0
		RIGHT_X		=	'b',
		RIGHT_Y		=	'B',
		KEY_UP		=	'c',
		KEY_RIGHT	=	'd',
		KEY_DOWN	=	'e',
		KEY_LEFT	=	'f',
		KEY_TRIANGLE=	'g',
		KEY_CIRCLE	=	'h',
		KEY_CROSS	=	'i',
		KEY_SQUARE	=	'j',
		KEY_START	=	'k',
		KEY_PS		=	'l',
		ACCEL_X		=	'n',
		ACCEL_Y		=	'm',
		KEY_L1		=	'o',
		KEY_R1		=	'p',
		KEY_L2		=	'q',
		KEY_R2		=	'r',
		KEY_SELECT = 's',
		ARDUINO_COUNT=	't'	//未確定
	};

	struct Button{
		uint8_t value;
		float tolerance;//変更
	};

	struct PsButton{
		Button	start,
		select,
		left_x,
		left_y,
		right_x,
		right_y,
		L1,
		L2,
		R1,
		R2,
		Triangle,
		Circle,
		Cross,
		Square,
		Up,
		Right,
		Down,
		Left,
		CError,
		Pitch,
		Roll;
	};

	PsButton psbutton;
	long disconnectTimeData;
	long time;
	int mode;
	uint8_t oldPitch,oldRoll;
	Serial *serial;
public:
	//DualShock(int idArg);
	DualShock(Can &can);
	DualShock(Serial &serial);
	int setup();
	int canId(int id);
	int canRead(int id,int number,unsigned char data[8]);
	void serialReadChar(char data);

	//	Arduinoから受信したキーの状態を返す
	//	左右のスティックの値は -1.0 ～ 1.0
	//	その他のキーの値は 0 ～ 1.0
	//	スティックは上がX正	下がX負	左がY正 右がY負としている
	float lx(void);
	float ly(void);
	float rx(void);
	float ry(void);
	float up(void);
	float right(void);
	float down(void);
	float left(void);
	float triangle(void);
	float circle(void);
	float cross(void);
	float square(void);
	float l1(void);
	float r1(void);
	float l2(void);
	float r2(void);
	int start(void);
	int select(void);
	float accelX(void);
	float accelY(void);
	void rumbeHigh(void);
	void rumbleLow(void);
	void rumbleStop(void);

	int disconnect();
	void disconnectTime(long timeArg);
	void cycle();

	void setStickTolerance(float toleranceArg);
	void setArrowKeyTolerance(float toleranceArg);
	void setSymbolKeyTolerance(float toleranceArg);
	void setSide1KeyTolerance(float toleranceArg);
	void setSide2KeyTolerance(float toleranceArg);
	void setStartKeyTolerance(float toleranceArg);

	void setlxTolerance(float toleranceArg){psbutton.left_x.tolerance=toleranceArg;};
	void setlyTolerance(float toleranceArg){psbutton.left_y.tolerance=toleranceArg;};
	void setrxTolerance(float toleranceArg){psbutton.right_x.tolerance=toleranceArg;};
	void setryTolerance(float toleranceArg){psbutton.right_x.tolerance=toleranceArg;};

	void setUpTolerance(float toleranceArg){psbutton.Up.tolerance=toleranceArg;};
	void setRightTolerance(float toleranceArg){psbutton.Right.tolerance=toleranceArg;};
	void setDownTolerance(float toleranceArg){psbutton.Down.tolerance=toleranceArg;};
	void setLeftTolerance(float toleranceArg){psbutton.Left.tolerance=toleranceArg;};

	void setTriangleTolerance(float toleranceArg){psbutton.Triangle.tolerance=toleranceArg;};
	void setCircleTolerance(float toleranceArg){psbutton.Circle.tolerance=toleranceArg;};
	void setCrossTolerance(float toleranceArg){psbutton.Cross.tolerance=toleranceArg;};
	void setSquareTolerance(float toleranceArg){psbutton.Square.tolerance=toleranceArg;};

	void setR1tolerance(float toleranceArg){psbutton.R1.tolerance=toleranceArg;};
	void setR2tolerance(float toleranceArg){psbutton.R2.tolerance=toleranceArg;};
	void setL1tolerance(float toleranceArg){psbutton.L1.tolerance=toleranceArg;};
	void setL2tolerance(float toleranceArg){psbutton.L2.tolerance=toleranceArg;};

	void setStartTolerance(float toleranceArg){psbutton.start.tolerance=toleranceArg;};


};

#endif//DUALSHOCKPLUS_HPP
