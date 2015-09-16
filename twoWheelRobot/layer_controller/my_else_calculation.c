//--------------------------------------------------------------------
//
//	my_else_calculation.c
//
//										作成・編集日：2014/11/25
//										作成・編集者：桐生
//--------------------------------------------------------------------

//Warning:
//	このファイルの関数内の角度計算では弧度法を使用しています。
//	このファイルの関数内の距離計算ではメートル法をミリ単位で使用しています。

//calc	:	計算(calculation)


#include <math.h>
#include "my_else_calculation.h"
#include "util.h"

void reset_pid_data(pid_data_t *pid){
	pid->i_data = 0;
	pid->old_gap_data = 0;
}
//------------------------------------------------
// title:	PID計算
// return:	float	計算値
// argument:pid_data_t*	PIDのデータ
//			float	目標値との差(目標値-現在値)
//			float	比例ゲイン
//			float	微分ゲイン
//			float	積分ゲイン
// coders:	桐生
float calc_pid(pid_data_t *data,float difference,pid_gain_t gain){
	float ans=0;

	ans =  gain.p * difference;
	ans += gain.i * data->i_data;
	ans += gain.d * (difference-(data->old_gap_data));

	data->i_data += difference;
	data->old_gap_data  = difference;

	ans = area(ans,-1,1);

	return (ans);
}

//------------------------------------------------
// title:	エンコーダの回転距離計算
// return:	float	エンコーダの回転距離
// argument:float	エンコーダのカウント数
//			float	エンコーダのパルス数 * マイコンが1パルス当たりカウントする回数
//			float	エンコーダタイヤの直径
// coders:	桐生
//float calc_enc_distance(signed long enc_ct,unsigned int pulse,float tire_diameter){
float calc_enc_distance(float enc_ct,float pulse,float tire_diameter){
	return ((enc_ct/pulse)*tire_diameter*M_PI);
}

pid_gain_t set_pid_gain(float p,float i, float d){
	pid_gain_t gain = {p,i,d};
	return gain;
}

