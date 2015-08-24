#ifndef ROBOTCENTER_HPP
#define ROBOTCENER_HPP

#include "encoder.hpp"
#include "util.hpp"

class RobotCenter:public Coord{
private:
	Encoder *enc[3];
	float oldEncDisi[3];				//1�O�̃G���R�[�_���i�񂾋���
	float gapEncDis[3];				//�G���R�[�_���i�񂾋����̕΍�
	float encDis[3];					//�G���R�[�_���i�񂾋����̍��v
	float encAngle[3];				//�G���R�[�_���狁�߂��钆�S�p�x
	float encMountAngle[3];	//�G���R�[�_���t���p�x
	float encMoveNormal[3];	//�G���R�[�_���狁�߂���@��
	float encRadius;					//���S����G���R�[�_�܂ł̋���
	enum{
		LEFT,
		RIGHT,
		BACK
	};
public:
	float angle;
	float coordX;
	float coordY;
	float velocity;
	float omega;
	RobotCenter(Encoder &l,Encoder &r,Encoder &b);
	void setup();
	void cycle();
};

#endif