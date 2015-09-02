#ifndef MOVE_HPP
#define MOVE_HPP
#include "circuit/md.hpp"

class Move{
private:
	Md *md[4];
	float xComponent;			//�x�N�g����x����
	float yComponent;			//�x�N�g����y����
	float freeAngle[4];			//�t���[��]�������
	float duty[4];
	enum{
		FRONTR,
		FRONTL,
		BACKL,
		BACKR
	};
public:
	Move(Md &md0,Md &md1,Md &md2,Md &md3);
	void getParallelOutput(float vector);						//���s�ړ��̏o�͌v�Z
	void getRotationOutput();					//��]�̏o��
	void getXYComponent(float vector, float angle);		//�x�N�g����xy�����ɕ���
	void setDuty(float vector);
	void cycle();
	void setup();
};

#endif