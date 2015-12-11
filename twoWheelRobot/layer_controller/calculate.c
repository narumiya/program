#include "calculate.h"
#include <math.h>
#include "util.h"

float radiusReverse(float radius){
	if(radius<0) return M_PI;

	return 0.0;
}

Ans_t crameRequation(float mat[2][3]){
	float delta=mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
	Ans_t ans;

	ans.x=mat[0][2]*mat[1][1]-mat[0][1]*mat[1][2];
	ans.x/=delta;

	ans.y=mat[0][0]*mat[1][2]-mat[0][2]*mat[1][0];
	ans.y/=delta;

	return ans;
}

float get_Average(int number_scope, int box, float add){
	static float average[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	static float number[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	if(number[box] >= number_scope){		//回数が増え過ぎたらリセットする
		number[box] = (number_scope-1);
	}

	average[box] *= number[box];			//前回までの平均値と回数から合計を求める
	average[box] += add;				//今回の入力値を加える
	number[box]++;					//回数の値を1加え、今回の回数にする
	average[box] = average[box]/number[box];	//合計を今回の回数で割る

	return (average[box]);				//今回の平均値を返す
}

float getTargetRadian(float targetX, float targetY, float nowX, float nowY){
	static float targetRadOld = 0.0;
	float targetRad = 0.0;

	if((targetX - nowX != 0.0) || (targetY - nowY != 0.0)){
		targetRad = atan2(targetY - nowY, targetX - nowX);
		targetRadOld = targetRad;
	}else{
		targetRad = targetRadOld;
	}
	return (targetRad);
}

float get_distance(float target_x, float target_y, float x_now, float y_now){
	return sqrtf(powf(target_x - x_now, 2) + powf(target_y - y_now, 2));
}

float get_gap_radian(float target_radian, float now_radian){
	float gap_radian = 0.0;

	gap_radian = target_radian - now_radian;
	gap_radian = area(gap_radian,-M_PI,M_PI);

	return (gap_radian);
}

float get_horizontal_distance(float distance, float gapRadian){
	if(gapRadian > M_PI/2.0){
		gapRadian = M_PI - gapRadian;
	}
	if(gapRadian < -M_PI/2.0){
		gapRadian = -gapRadian - M_PI;
	}

	if(gapRadian > 0){
		return ((-1)*distance * cos(((M_PI/2.0)-fabs(gapRadian))));
	}else{
		return (distance * cos(((M_PI/2.0)-fabs(gapRadian))));
	}
}

float get_vertical_distance(float distance, float gapRadian){
	int limit_over = 0;
	if(gapRadian > M_PI/2.0){
		gapRadian = M_PI - gapRadian;
		limit_over = 1;
	}
	if(gapRadian < -M_PI/2.0){
		gapRadian = -gapRadian - M_PI;
		limit_over = 1;
	}

	if(limit_over == 0){
		return (distance * sin(((M_PI/2.0) - fabs(gapRadian))));
	}else{
		return ((-1)*distance * sin(((M_PI/2.0) - fabs(gapRadian))));//車体の向きに対して垂直方向が後方
	}
}

float get_horizontal_distance_position(float target_x, float target_y, float x_now, float y_now, float nowRadian){
	return (get_horizontal_distance(get_distance(target_x,target_y,x_now,y_now),get_gap_radian(getTargetRadian(target_x,target_y,x_now,y_now),nowRadian)));
}

float get_vertical_distance_position(float target_x, float target_y, float x_now, float y_now, float nowRadian){
	return (get_vertical_distance(get_distance(target_x,target_y,x_now,y_now),get_gap_radian(getTargetRadian(target_x,target_y,x_now,y_now),nowRadian)));
}
