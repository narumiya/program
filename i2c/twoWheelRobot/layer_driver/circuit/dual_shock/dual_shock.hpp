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
	//Dualshock3�̃f�[�^��͗p
	//���̗񋓌^�̒l��Arduino���̐ݒ�ƍ��킹��
	//�ǂ̒l��ǂݎ�����������ʂ���L���B�ォ��(a,b,c...)�Ƒ����Ă���
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
		LEFT_X		=	'a',//stick �� ��1.0 ��-1.0
		LEFT_Y		=	'A',//stick �� �E1.0 ��-1.0
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
		ARDUINO_COUNT=	't'	//���m��
	};

	struct Button{
		uint8_t value;
		float tolerance;//�ύX
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

	//	Arduino�����M�����L�[�̏�Ԃ�Ԃ�
	//	���E�̃X�e�B�b�N�̒l�� -1.0 �` 1.0
	//	���̑��̃L�[�̒l�� 0 �` 1.0
	//	�X�e�B�b�N�͏オX��	����X��	����Y�� �E��Y���Ƃ��Ă���
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