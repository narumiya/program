#ifndef BUTTON_INFO_HPP
#define BUTTON_INFO_HPP

#include "digital.hpp"

class ButtonInfo{
private:
	Digital *pin;
	int raw;			//�`���^�����O����̃f�[�^
	int info;			//�`���^�����O�Ȃ��̃f�[�^
	int count;			//��������
	int upEdge;	//�A�b�v�G�b�W�t���O
	int downEdge;	//�_�E���G�b�W�t���O
	int state;			//�ꎞ�I�ɕۑ����Ă����{�^���f�[�^
	int timer;				//�`���^�����O����J�E���g
	int old;				//��O�̃{�^�����
	int chatTime;
	unsigned int cycleTime;
	bool normalyClose;
public:
	ButtonInfo();
	ButtonInfo(Digital &digitalPin);
	int setup(bool normaly,int time);
	void cycle();
	int readValue(){return info;};
	int readDownEdge(){return downEdge;};
	int readUpEdge(){return upEdge;};
	int readCount(){return count;};
};

#endif