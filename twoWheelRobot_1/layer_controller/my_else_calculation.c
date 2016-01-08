//--------------------------------------------------------------------
//
//	my_else_calculation.c
//
//										�쐬�E�ҏW���F2014/11/25
//										�쐬�E�ҏW�ҁF�ː�
//--------------------------------------------------------------------

//Warning:
//	���̃t�@�C���̊֐����̊p�x�v�Z�ł͌ʓx�@���g�p���Ă��܂��B
//	���̃t�@�C���̊֐����̋����v�Z�ł̓��[�g���@���~���P�ʂŎg�p���Ă��܂��B

//calc	:	�v�Z(calculation)


#include <math.h>
#include "my_else_calculation.h"
#include "util.h"

void reset_pid_data(pid_data_t *pid){
	pid->i_data = 0;
	pid->old_gap_data = 0;
}
//------------------------------------------------
// title:	PID�v�Z
// return:	float	�v�Z�l
// argument:pid_data_t*	PID�̃f�[�^
//			float	�ڕW�l�Ƃ̍�(�ڕW�l-���ݒl)
//			float	���Q�C��
//			float	�����Q�C��
//			float	�ϕ��Q�C��
// coders:	�ː�
float calc_pid(pid_data_t *data,float difference,pid_gain_t gain){
	float ans=0;

	ans =  gain.p * difference;
	ans += gain.i * data->i_data;
	ans += gain.d * (difference-(data->old_gap_data));

	data->i_data += difference;
	data->old_gap_data  = difference;

	return (ans);
}

//------------------------------------------------
// title:	�G���R�[�_�̉�]�����v�Z
// return:	float	�G���R�[�_�̉�]����
// argument:float	�G���R�[�_�̃J�E���g��
//			float	�G���R�[�_�̃p���X�� * �}�C�R����1�p���X������J�E���g�����
//			float	�G���R�[�_�^�C���̒��a
// coders:	�ː�
//float calc_enc_distance(signed long enc_ct,unsigned int pulse,float tire_diameter){
float calc_enc_distance(float enc_ct,float pulse,float tire_diameter){
	return ((enc_ct/pulse)*tire_diameter*M_PI);
}

pid_gain_t set_pid_gain(float p,float i, float d){
	pid_gain_t gain = {p,i,d};
	return gain;
}
