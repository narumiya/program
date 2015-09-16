#include "move.hpp"

Move::	Move(MiniMD &l,MiniMD &r){
	md[0]=&l;md[1]=&r;
}

int Move::setup(){
	for(int i=0;i<2;i++){
		md[i]->setup();
	}
	return 0;
}

void Move::cycle(){
	for(int i=0;i<2;i++)
		md[i]->cycle();
}

void Move::setDuty(float value){
	md[0]->duty(value);
	md[1]->duty(-value);
}
