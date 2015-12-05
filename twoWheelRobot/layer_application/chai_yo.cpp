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
	return i;
}

void ChaiYo::setCoord(){
	coord[CX][0]=1295.0;													coord[CY][0]=0.0;//slope1前
	coord[CX][1]=coord[CX][0]+1063.0*cos(dtor(10.3));coord[CY][1]=295.0;//hill1前
	coord[CX][2]=coord[CX][1]+1087.0;							coord[CY][2]=922.0;//slope2前
	coord[CX][3]=coord[CX][2]+777.0*cos(dtor(10.3));	coord[CY][3]=1700.0;//hill2前
	coord[CX][4]=coord[CX][3]+1087.0;							coord[CY][4]=2328.0;//slope3前
	//coord[CX][5]=6376.0;coord[CY][5]=2698.0;//hill3前
	coord[CX][5]=coord[CX][4]+1062.0*cos(dtor(10.3));coord[CY][5]=2612.0;//hill3前
	coord[CX][6]=coord[CX][5]+377.0;								coord[CY][6]=1497.0;//river 前
	coord[CX][7]=coord[CX][6]+477.0;								coord[CY][7]=1019.0;//river 1
	coord[CX][8]=coord[CX][7]-353.0;								coord[CY][8]=665.0;//river 2
	coord[CX][9]=coord[CX][8]+353.0;								coord[CY][9]=312.0;//river 3
	coord[CX][10]=coord[CX][9]-353.0;								coord[CY][10]=-41.0;//river 4
	coord[CX][11]=coord[CX][10]+565.0;							coord[CY][11]=-606.0;//river 終わり
	coord[CX][12]=coord[CX][11]+636.0;							coord[CY][12]=-1243.0;//down hill 始まり
	coord[CX][13]=coord[CX][12]+sqrtf(879.0*879.0+126.0*126.0);	coord[CY][13]=-1831.0;//down hill 1カーブ
	coord[CX][14]=coord[CX][13]+sqrtf(1521.0*1521.0+218.0*218.0);coord[CY][14]=-823.0;//down hill 2カーブ
	coord[CX][15]=coord[CX][14]+sqrtf(907.0*907.0+130.0*130.0);	coord[CY][15]=-1614.0;//down hill 3カーブ
	coord[CX][16]=coord[CX][15]+sqrtf(861.0*861.0+123.0*123.0);	coord[CY][16]=-1831.0;//down hill  最後
	coord[CX][17]=coord[CX][16]+1155.0;						coord[CY][17]=-1831.0;//最後
}

void ChaiYo::cycle(){
	eco->cycle();
	b0->cycle();
	b1->cycle();
	if(millis()-time>=controlPeriod){
		time=millis();
		if(!startFlag){
			if(b0->readDownEdge())  startFlag=true;
			eco->reset();
		}else if(startFlag){

		}
	}
}
