#ifndef CALUCULATE_H
#define CALUCULATE_H

float radiusReverse(float radius);

typedef struct{
	float x;
	float y;
}Ans_t;

Ans_t crameRequation(float mat[2][3]);
float get_Average(int number_scope, int box, float add);

#endif
