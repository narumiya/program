#ifndef CALUCULATE_H
#define CALUCULATE_H

typedef struct{
	float x;
	float y;
}Ans_t;

float radiusReverse(float radius);
Ans_t crameRequation(float mat[2][3]);
float get_Average(int number_scope, int box, float add);

#endif
