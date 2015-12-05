#include "move.hpp"
#include <stdio.h>
#include <math.h>
#include "pin.hpp"
extern "C"{
#include "mcutime.h"
#include "calculate.h"
}

Move::Move(LineSensor &line,ButtonInfo &swPin,Servo &servoPin,RoboCenter &robo){
	mode=NONSENSOR;
	startSw=&swPin;
	servo=&servoPin;
	this->robo=&robo;
	this->line=&line;
	for(int i=0;i<5;i++){
		adData[i]=0.0;
	}
	for(int i=0;i<15;i++){
		coord[0][i]=0.0;
		coord[1][i]=0.0;
	}
	task=0;
	targetAngle=0;
	distance=0;
	servoAngle=0.0;
	servoX=0.0;
	servoY=0.0;
	countWhile=0;
	countAverage=500;
	time=millis();
	startFlag=false;
	startX=0.0;startY=0.0;
}

int Move::setup(){
	startSw->setup(true,25);
	led1.setupDigitalOut();
	led2.setupDigitalOut();
	led3.setupDigitalOut();
	initAngle=35.0;
	setCoord();
	if(mode==USESENSOR){
		line->setup();
	}
	servo->setup(20.0,dtor(180.0),1.5,2.3);//rb995

	return 0;
}

void Move::setCoord(){
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

#define LINE 0
#define COORD 1
#define MODE COORD

#if MODE==LINE//ライントレース
void Move::cycle(){
	if(mode==USESENSOR){
		TPR105Cycle();
	}else	calibraFlag=true;
	startSw->cycle();
	if(millis()-time>=1){
		time=millis();
		if(!startFlag){
				if(startSw->readDownEdge()) startFlag=true;
		}else if(startFlag){
			led3.digitalHigh();
			if(!useServo){
				pid_gain_t gain=set_pid_gain(0.65,0.0,1.2);//p0.3直進の出力なし
				float speed=0.0;
				float rotation=floatlimit(-1.0,rotationOutput(gain),1.0);
				setDuty(speed,rotation);
				//printf("output,%.2f",rotation);
				//printf("middle%f",middle);
				//printf("sw,%d",sw->readValue());
				//printf("\n");
			}else{
				//static float output=servo->cvtPulse(dtor(INITANGLE));
				//pid_gain_t gain=set_pid_gain(0.000035,0.0,0.0);//1度→0.0019
				static float output=dtor(initAngle);//servo->cvtPulse(dtor(INITANGLE));
				//static float oldAngle=0;
				//static int flag[2]={0};
				//pid_gain_t gain=set_pid_gain(0.0046,0.0,0.0160);//0.0018
				pid_gain_t gain=set_pid_gain(0.0055,0.0,0.0168);//0.0018
				//pid_gain_t gain=set_pid_gain(0.00068,0.0,0.00);//0.0018
				//pid_gain_t gain=set_pid_gain(0.00018,0.0,0.00020);//0.00018//前に取り付け

				float angle=rotationOutput(gain);
				output+=angle;

				if(adData[4]<0.1){
					output+=dtor(0.2);
				}else if(adData[0]<0.1){
					output-=dtor(0.2);
				}

				if(startSw->readValue()) output=dtor(initAngle);
				output=floatlimit(dtor(-45.0+initAngle),output,dtor(45.0+initAngle));
				servo->setAngle(output);
				//printf("output,%.2f\n",output);
			}
		}
		countAverage=countWhile;
		countWhile=0;
	}
	if(!useServo){
		for(int i=0;i<2;i++)
			md[i]->cycle();
	}else{
		if(startFlag)
			servo->cycle();
	}
}
#else
void Move::cycle(){
	static float output=dtor(initAngle);
	pid_gain_t gain=set_pid_gain(0.90,0.0,0.99);
	startSw->cycle();
	if(millis()-time>=5){
		time=millis();
		if(!startFlag){
			if(startSw->readDownEdge()) startFlag=true;
			robo->reset();
			output=dtor(initAngle);
			servoAngle=output*(-1.0);
			servoX=0.0;
			servoY=0.0;
			task=0;
		}else if(startFlag){
			float angle=rotationOutput(gain);
			output-=angle;
			output=floatlimit(dtor(10.0),output,dtor(70.0));
			servoAngle=(output-dtor(initAngle))*(-1.0)+robo->getAngle();//右回転が+だから-1かけてる
			//distance=getVerticalDistance();
			distance=getDistance();

			if(task==5){
				if(distance<=340){
					task++;
				}
			}else if(task>=7){
				if(distance<=430){
					task++;
				}
			}else{
				if(distance<=220){
					task++;
				}
			}
			servo->setAngle(output);
			/*for(float deg=-10;deg<75;deg+=10){
				servo->setAngle(dtor(deg));
				servo->cycle();
				wait(37);
			}
			for(float deg=75;deg>-10;deg-=10){
				servo->setAngle(dtor(deg));
				servo->cycle();
				wait(37);
			}*/
		}
		if(startSw->readValue()){
			robo->reset();
			output=dtor(initAngle);
			servoAngle=output*(-1.0);
			servoX=0.0;
			servoY=0.0;
			task=0;
		}
		servo->cycle();
	}
}

#endif

void Move::TPR105Cycle(){
	countWhile++;
	for(int i=0;i<5;i++){
		adData[i]=get_Average(countAverage,i,line->getValue(i));
	}
}

float Move::rotationOutput(pid_gain_t gain){
#if MODE==LINE
	static pid_data_t data={0};
	//static float oldAd=0;
	//const pid_gain_t gain=set_pid_gain(0.65,0.0,1.2);//p0.3直進の出力なし
	float ad=0;

	//static int reset=millis();
	//const pid_gain_t gain=set_pid_gain(0.2,0.0,0);

	/*if(millis()-reset>=100){
		reset=millis();
		reset_pid_data(&data);
	}*/
	//float ad=((adData[1]+adData[3])-middle);///((other-white));
	//ad=(((1.0-adData[1])-(1.0-adData[3])));//差分を0にするように
	//if(adData[3]<0.1&&adData[1]<0.1){
	//ad=((adData[3]-adData[1]));//差分を0にするように
	ad=((adData[1]-adData[3]));//差分を0にするように
	//	oldAd=ad;
	//}else{
	//	ad=oldAd;
//	}
	//printf("ad,%f",ad);
	float output=calc_pid(&data,ad,gain);
	//printf("%f,  %f,   %f\n",adData[3],adData[1],output);

	return  output;
	//return calc_pid(&data,ad,gain);
#else
	static pid_data_t data={0};
	float targetAngle=getTargetAngle();
	float output=calc_pid(&data,targetAngle-servoAngle,gain);

	return output;
#endif
}



float Move::getTargetAngle(){
	float targetX=coord[CX][task];
	float targetY=coord[CY][task];
	float nowX=robo->getX();
	float nowY=robo->getY();
//	float nowX=servoX;
//	float nowY=servoY;
	targetAngle=getTargetRadian(targetX,targetY,nowX,nowY);
	//targetAngle=0;
	targetAngle=area(targetAngle,-M_PI,M_PI);

	return (targetAngle);
}

float Move::getDistance(){
	float targetX=coord[CX][task];
	float targetY=coord[CY][task];
	float nowX=robo->getX();
	float nowY=robo->getY();
//	float nowX=servoX;
//	float nowY=servoY;
	float value=get_distance(targetX,targetY,nowX,nowY);

	return value;
}

float Move::getVerticalDistance(){
	float targetX=coord[CX][task];
	float targetY=coord[CY][task];
	float nowX=robo->getX();
	float nowY=robo->getY();
	float nowAngle=servoAngle;
	float value=get_vertical_distance_position(targetX,targetY,nowX,nowY,nowAngle);

	return value;
}

void Move::printAdValue(){
	printf("ad%d,%.4f ",0,adData[0]);
	printf("ad%d,%.4f ",1,adData[1]);
	printf("ad%d,%.4f ",2,adData[2]);
	printf("ad%d,%.4f ",3,adData[3]);
	printf("ad%d,%.4f ",4,adData[4]);
}

void Move::printRoboInfo(){
	printf("x,%.2f,",robo->getX());
	printf("y,%.2f,",robo->getY());
	printf("deg,%.2f,",rtod(robo->getAngle()));
	//printf("sx,%.2f,",servoX);
	//printf("sy,%.2f,",servoY);
	printf("sd,%.2f,",rtod(servoAngle));
	printf("td,%.2f,",rtod(targetAngle));
	printf("dis,%.2f,",distance);
	printf("task,%d,",task);
	//printf("enc %.2f,",robo->getEncCnt());
}
