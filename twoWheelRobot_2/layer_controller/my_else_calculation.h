//--------------------------------------------------------------------
//
//	my_else_calculation.h
//
//										作成・編集日：2014/11/25
//										作成・編集者：桐生
//--------------------------------------------------------------------

//Warning:
//	このファイルの角度計算では弧度法を使用しています。
//	このファイルの距離計算ではメートル法をミリ単位で使用しています。

//calc	:	計算(calculation)


#ifndef my_else_calculation_h
#define my_else_calculation_h

#include <math.h>


//----------------------------------------------------------
//PID用構造体(複数箇所で行っていたPID制御を1つの関数で行えるようにするために、関数内で保存されていたデータを構造体で置くこととした)
//Caution:
//		構造体内の情報を変更する際は注意してください。
typedef struct {
	float old_gap_data;	//前回データ
	float i_data;		//積分データ
}pid_data_t;

typedef struct{
	float p;
	float i;
	float d;
}pid_gain_t;

void reset_pid_data(pid_data_t *pid);


//------------------------------------------------
// title:	PID計算
// return:	float	計算値
// argument:pid_data_t*	PIDのデータ
//			float	目標値との差
//			float	比例ゲイン
//			float	微分ゲイン
//			float	積分ゲイン
// coders:	桐生
float calc_pid(pid_data_t *data,float difference,pid_gain_t gain);

//------------------------------------------------
// title:	エンコーダの回転距離計算
// return:	float	エンコーダの回転距離
// argument:float	エンコーダのカウント数
//			float	エンコーダのパルス数 * マイコンが1パルス当たりカウントする回数
//			float	エンコーダタイヤの直径
// coders:	桐生
//float calc_enc_distance(signed long enc_ct,unsigned int pulse,float tire_diameter);
//float calc_enc_distance(float enc_ct,float pulse,float tire_diameter);

pid_gain_t set_pid_gain(float p,float i, float d);

#endif
