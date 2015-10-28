//--------------------------------------------------------------------
//
//	my_else_calculation.h
//
//										�쐬�E�ҏW���F2014/11/25
//										�쐬�E�ҏW�ҁF�ː�
//--------------------------------------------------------------------

//Warning:
//	���̃t�@�C���̊p�x�v�Z�ł͌ʓx�@���g�p���Ă��܂��B
//	���̃t�@�C���̋����v�Z�ł̓��[�g���@���~���P�ʂŎg�p���Ă��܂��B

//calc	:	�v�Z(calculation)


#ifndef my_else_calculation_h
#define my_else_calculation_h

#include <math.h>


//----------------------------------------------------------
//PID�p�\����(�����ӏ��ōs���Ă���PID�����1�̊֐��ōs����悤�ɂ��邽�߂ɁA�֐����ŕۑ�����Ă����f�[�^���\���̂Œu�����ƂƂ���)
//Caution:
//		�\���̓��̏���ύX����ۂ͒��ӂ��Ă��������B
typedef struct {
	float old_gap_data;	//�O��f�[�^
	float i_data;		//�ϕ��f�[�^
}pid_data_t;

typedef struct{
	float p;
	float i;
	float d;
}pid_gain_t;

void reset_pid_data(pid_data_t *pid);


//------------------------------------------------
// title:	PID�v�Z
// return:	float	�v�Z�l
// argument:pid_data_t*	PID�̃f�[�^
//			float	�ڕW�l�Ƃ̍�
//			float	���Q�C��
//			float	�����Q�C��
//			float	�ϕ��Q�C��
// coders:	�ː�
float calc_pid(pid_data_t *data,float difference,pid_gain_t gain);

//------------------------------------------------
// title:	�G���R�[�_�̉�]�����v�Z
// return:	float	�G���R�[�_�̉�]����
// argument:float	�G���R�[�_�̃J�E���g��
//			float	�G���R�[�_�̃p���X�� * �}�C�R����1�p���X������J�E���g�����
//			float	�G���R�[�_�^�C���̒��a
// coders:	�ː�
//float calc_enc_distance(signed long enc_ct,unsigned int pulse,float tire_diameter);
//float calc_enc_distance(float enc_ct,float pulse,float tire_diameter);

pid_gain_t set_pid_gain(float p,float i, float d);

#endif