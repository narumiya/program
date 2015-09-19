#include "calculate.h"
#include <math.h>

float radiusReverse(float radius){
	if(radius<0){
		return M_PI;
	}
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

float get_Average(int number_scope, int box, float add)
{
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
