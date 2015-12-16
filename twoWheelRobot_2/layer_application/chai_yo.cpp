#include "chai_yo.hpp"

ChaiYo::ChaiYo(Move &move,RoboCenter &eco,Buzzer &buzz,Led1 &l1,Led2 &l2,Led3 &l3,ButtonInfo &b0,ButtonInfo &b1){
	this->move=&move;
	this->eco=&eco;
	this->buzz=&buzz;
	this->led1=&l1;
	this->led2=&l2;
	this->led3=&l3;
	this->b0=&b0;
	this->b1=&b1;
	time=millis();
	startFlag=false;
	task=0;
	startTask=0;
}

int ChaiYo::setup(){
	int i=eco->setup();
	i+=move->setup();
	i+=led1->setupDigitalOut();
	i+=led2->setupDigitalOut();
	i+=led3->setupDigitalOut();
	i+=b0->setup(true,25);
	i+=b1->setup(true,25);
	controlPeriod=5;

	startX=-495.0+72.0;
	startY=0.0;
	startAngle=0.0;
	eco->setAngle(startAngle);
	startTask=SLOPE1;

	initServoAngle=0.0;

	return i;
}

void ChaiYo::cycle(){
	eco->cycle();
	b0->cycle();
	b1->cycle();
	if(millis()-time>=controlPeriod){
		time=millis();
		if(!startFlag){
			if(b0->readDownEdge())  startFlag=true;
			eco->reset(startX,startY);
			servoAngle=initServoAngle;
		}else if(startFlag){

		}
	}
}


void ChaiYo::setCoord(){
	coord[CX][SLOPE1]=1295.0;																coord[CY][SLOPE1]=0.0;//slope1前
	coord[CX][HILL1]=coord[CX][HILL1-1]+1063.0*cos(dtor(10.3));	coord[CY][HILL1]=295.0;//hill1前
	coord[CX][SLOPE2]=coord[CX][SLOPE2-1]+1087.0;						coord[CY][SLOPE2]=922.0;//slope2前
	coord[CX][HILL2]=coord[CX][HILL2-1]+777.0*cos(dtor(10.3));	coord[CY][HILL2]=1700.0;//hill2前
	coord[CX][SLOPE3]=coord[CX][SLOPE3-1]+1087.0;						coord[CY][SLOPE3]=2328.0;//slope3前
	coord[CX][HILL3]=coord[CX][HILL3-1]+1062.0*cos(dtor(10.3));	coord[CY][HILL3]=2612.0;//hill3前
	coord[CX][HILL4]=coord[CX][HILL4-1]+377.0;								coord[CY][HILL4]=coord[CY][HILL4-1]-560.0;
	coord[CX][RIVER]=coord[CX][RIVER-1];											coord[CY][RIVER]=1497.0;//river 前
	coord[CX][RIVER1]=coord[CX][RIVER1-1]+336.0;							coord[CY][RIVER1]=coord[CY][RIVER1-1]-407.0;//river 1
	coord[CX][RIVER2]=coord[CX][RIVER2-1]-70.0;								coord[CY][RIVER2]=coord[CY][RIVER2-1]-353.0;//river 2
	coord[CX][RIVER3]=coord[CX][RIVER3-1]+69.0;							coord[CY][RIVER3]=coord[CY][RIVER3-1]-354.0;//river 3
	coord[CX][RIVER4]=coord[CX][RIVER4-1]-69.0;								coord[CY][RIVER4]=coord[CY][RIVER4-1]-352.0;//river 4
	coord[CX][DOWNHILL]=coord[CX][DOWNHILL-1]+1131.0;			coord[CY][DOWNHILL]=-1243.0;//down hill 始まり

	coord[CX][DOWNHILL1_0]=coord[CX][DOWNHILL1_0-1]+544.893*cos(dtor(-44.96));coord[CY][DOWNHILL1_0]=coord[CY][DOWNHILL1_0-1]+544.893*sin(dtor(-44.96));
	//down hill 1回目 円の中心座標
	curveRadius[0]=713.385;
	centralAngle[0]=dtor(90.763);
	circleCenter[CX][0]=coord[CX][DOWNHILL1_0]-curveRadius[0]*cos(dtor(44.74-180.0));
	circleCenter[CY][0]=coord[CY][DOWNHILL1_0]-curveRadius[0]*sin(dtor(44.74-180.0));
	initCurveAngle[0]=dtor(44.74-180.0);
	coord[CX][DOWNHILL1_1]=circleCenter[CX][0]+curveRadius[0]*cos(dtor(135.503-180.0));coord[CY][DOWNHILL1_1]=circleCenter[CY][0]+713.385*sin(dtor(135.503-180.0));
	coord[CX][DOWNHILL2_0]=coord[CX][DOWNHILL1_1]+863.105*cos(dtor(45.22));coord[CY][DOWNHILL2_0]=coord[CY][DOWNHILL1_1]+863.105*sin(dtor(45.22));
	//down hill 2回目 円の中心座標
	curveRadius[1]=600.123;
	centralAngle[1]=dtor(97.911);
	circleCenter[CX][1]=coord[CX][DOWNHILL2_0]-curveRadius[1]*cos(dtor(37.6+97.911));
	circleCenter[CY][1]=coord[CY][DOWNHILL2_0]-curveRadius[1]*sin(dtor(37.6+97.911));
	initCurveAngle[1]=dtor(37.6+97.911);
	coord[CX][DOWNHILL2_1]=circleCenter[CX][1]+curveRadius[1]*cos(dtor(37.599));coord[CY][DOWNHILL2_1]=circleCenter[CY][1]+curveRadius[1]*sin(dtor(37.599));
	coord[CX][DOWNHILL3_0]=coord[CX][DOWNHILL2_1]+555.924*cos(dtor(-51.83));coord[CY][DOWNHILL3_0]=coord[CY][DOWNHILL2_1]+555.924*sin(dtor(-51.83));
	//down hill 3回目 円の中心座標
	curveRadius[2]=852.293;
	centralAngle[2]=dtor(97.911);
	circleCenter[CX][2]=coord[CX][DOWNHILL3_0]-curveRadius[2]*cos(dtor(37.6-180.0));
	circleCenter[CY][2]=coord[CY][DOWNHILL3_0]-curveRadius[2]*sin(dtor(37.6-180.0));
	initCurveAngle[2]=dtor(37.6-180.0);
	coord[CX][DOWNHILL3_1]=circleCenter[CX][2]+curveRadius[2]*cos(dtor(90.041-180.0));coord[CY][DOWNHILL3_1]=circleCenter[CY][2]+curveRadius[2]*sin(dtor(90.041-180.0));
	coord[CX][DOWNHILL3_2]=coord[CX][DOWNHILL3_2-1]+303.090;coord[CY][DOWNHILL3_2]=coord[CY][DOWNHILL3_2-1];

	coord[CX][FIN]=coord[CX][FIN-1]+1155.0;										coord[CY][FIN]=-1831.0;//最後
}
