#include "robotCenter.hpp"
#include <math.h>
extern "C" {
#include "util.h"
#include "calculate.h"
}

RobotCenter::RobotCenter(Encoder &l,Encoder &r,Encoder &b){
	enc[LEFT]=&l;
	enc[RIGHT]=&r;
	enc[BACK]=&b;
	encRadius=0.0;
	coordX=0.0;
	coordY=0.0;
	velocity=0.0;
	omega=0.0;
	angle=0.0;
	originalAngle=0;
	time=millis();
	for(int i=0;i<3;i++){
		oldEncDisi[i]=0;
		gapEncDis[i]=0;
		encDis[i]=0;
		encMountAngle[i]=0;
		moveEncX[i]=0;
		moveEncY[i]=0;
		temporaryX[i]=0;
		temporaryY[i]=0;
	}
}

void RobotCenter::setup(){
	for(int i=0;i<3;i++){
		enc[i]->setup();
		enc[i]->cpr(1000);
	}
	enc[LEFT]->rev(true);
	enc[RIGHT]->rev(true);
	enc[BACK]->rev(true);
	enc[LEFT]->mlt(50.8);
	enc[RIGHT]->mlt(50.8);
	enc[BACK]->mlt(50.8);
	encMountAngle[LEFT]=dtor(150);
	encMountAngle[RIGHT]=dtor(30);
	encMountAngle[BACK]=dtor(-90);
	encRadius=100.0;
}

void RobotCenter::cycle(){
	float mat[3][3]={0};
	float mat1[2][3]={0};

	if(millis()-time>=5){
		time=millis();

		for(int i=0;i<3;i++){
			gapEncDis[i]=enc[i]->value()-oldEncDisi[i];
			oldEncDisi[i]=enc[i]->value();
			encAngle[i]=gapEncDis[i]/encRadius;
		}
		originalAngle+=(encAngle[0]+encAngle[1]+encAngle[2])/3.0;
		angle=area(originalAngle,(-1.0)*M_PI,M_PI);

		for(int i=0;i<3;i++){
			moveEncX[i]=fabs(gapEncDis[i])*cos(encMountAngle[i]+angle+radiusReverse(gapEncDis[i]));
			moveEncY[i]=fabs(gapEncDis[i])*sin(encMountAngle[i]+angle+radiusReverse(gapEncDis[i]));

			if(tan(encMountAngle[i]+angle)!=0.0)mat[i][0]=1.0/tan(encMountAngle[i]+angle);
			else mat[i][0]=0.0;
			mat[i][1]=1.0;
			mat[i][2]=moveEncY[i]+mat[i][0]*moveEncX[i];
		}
		for(int i=0;i<3;i++){
			Ans_t ans;
			int j=2-(i+1);

			if(j==-1) j=2;
			mat1[0][0]=mat[2-i][0];
			mat1[0][1]=mat[2-i][1];
			mat1[0][2]=mat[2-i][2];

			mat1[1][0]=mat[j][0];
			mat1[1][1]=mat[j][1];
			mat1[1][2]=mat[j][2];
			ans=crameRequation(mat1);
			temporaryX[i]=ans.x;
			temporaryY[i]=ans.y;
		}

		coordX+=(temporaryX[0]+temporaryX[1]+temporaryX[2])/3.0;
		coordY+=(temporaryY[0]+temporaryY[1]+temporaryY[2])/3.0;
	}
	cartesian(coordX,coordY,0);
}

void	RobotCenter::resetInfo(){
	angle=0.0;
	coordX=0.0;
	coordY=0.0;
	originalAngle=0.0;
}
