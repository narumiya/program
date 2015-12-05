#ifndef CALUCULATE_H
#define CALUCULATE_H

typedef struct{
	float x;
	float y;
}Ans_t;

float radiusReverse(float radius);
Ans_t crameRequation(float mat[2][3]);
float get_Average(int number_scope, int box, float add);
float getTargetRadian(float targetX, float targetY, float nowX, float nowY);
float get_distance(float target_x, float target_y, float x_now, float y_now);
float get_gap_radian(float target_radian, float now_radian);
float get_horizontal_distance(float distance, float gapRadian);
float get_vertical_distance(float distance, float gapRadian);
float get_horizontal_distance_position(float target_x, float target_y, float x_now, float y_now, float nowRadian);
float get_vertical_distance_position(float target_x, float target_y, float x_now, float y_now, float nowRadian);

#endif
