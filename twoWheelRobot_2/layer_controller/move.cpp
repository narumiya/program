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
	for(int i=0;i<3;i++){
		circleCenter[0][i]=0.0;
		circleCenter[1][i]=0.0;
		initCurveAngle[i]=0.0;//downhill 突入時初期角度
		curveRadius[i]=0.0;//down hill 半径
		centralAngle[i]=0.0;//down hill 中心角
	}
	task=0;
	targetAngle=0.0;
	distance=0.0;
	servoAngle=0.0;
	countWhile=0;
	countAverage=500;
	time=millis();
	startFlag=false;
	startX=0.0;startY=0.0;
	startAngle=0.0;
	startTask=0;
	angleTime=0.0;
	timeLeft=9999.0;
}

int Move::setup(){
	if(mode==USESENSOR)	line->setup();
	startSw->setup(true,25);
	led1.setupDigitalOut();
	led2.setupDigitalOut();
	led3.setupDigitalOut();
	setCoord();
	servo->setup(20.0,dtor(180.0),1.5,2.3);//rb995

	initAngle=4.0;
	output=dtor(initAngle);
/*
	startX=-495.0+73.0;
	//startX=0.0;
	startY=0.0;
	startAngle=0.0;
	robo->setAngle(startAngle);
	startTask=SLOPE1;
*/
	startX=coord[CX][DOWNHILL];
	startY=coord[CY][DOWNHILL];
	startAngle=getTargetRadian(coord[CX][DOWNHILL+1],coord[CY][DOWNHILL+1],startX,startY)*(-1.0);//ジャイロの角度反対のため反転
	robo->setAngle(startAngle);
	startTask=DOWNHILL+1;

	return 0;
}
/*
void Move::setCoord(){
	coord[CX][SLOPE1]=1295.0;																coord[CY][SLOPE1]=0.0;//slope1前
	coord[CX][HILL1]=coord[CX][HILL1-1]+1063.0*cos(dtor(10.3));	coord[CY][HILL1]=295.0;//hill1前
	coord[CX][SLOPE2]=coord[CX][SLOPE2-1]+1087.0;						coord[CY][SLOPE2]=922.0;//slope2前
	coord[CX][HILL2]=coord[CX][HILL2-1]+777.0*cos(dtor(10.3));	coord[CY][HILL2]=1700.0;//hill2前
	coord[CX][SLOPE3]=coord[CX][SLOPE3-1]+1087.0;						coord[CY][SLOPE3]=2328.0;//slope3前
	//coord[CX][5]=6376.0;coord[CY][5]=2698.0;//hill3前
	coord[CX][HILL3]=coord[CX][HILL3-1]+1062.0*cos(dtor(10.3));	coord[CY][HILL3]=2612.0;//hill3前
	coord[CX][HILL4]=coord[CX][HILL4-1]+377.0;								coord[CY][HILL4]=coord[CY][HILL4-1]-560.0;
	coord[CX][RIVER]=coord[CX][RIVER-1];											coord[CY][RIVER]=1497.0;//river 前
	coord[CX][RIVER1]=coord[CX][RIVER1-1]+477.0;							coord[CY][RIVER1]=1019.0;//river 1
	coord[CX][RIVER2]=coord[CX][RIVER2-1]-353.0;							coord[CY][RIVER2]=665.0;//river 2
	coord[CX][RIVER3]=coord[CX][RIVER3-1]+353.0;							coord[CY][RIVER3]=312.0;//river 3
	coord[CX][RIVER4]=coord[CX][RIVER4-1]-353.0;							coord[CY][RIVER4]=-41.0;//river 4
	//coord[CX][RIVERFIN]=coord[CX][RIVERFIN-1]+565.0;					coord[CY][RIVERFIN]=-606.0;//river 終わり
	coord[CX][DOWNHILL]=coord[CX][DOWNHILL-1]+1202.0;				coord[CY][DOWNHILL]=-1243.0;//down hill 始まり
	coord[CX][DOWNHILL1]=coord[CX][DOWNHILL1-1]+sqrtf(879.0*879.0+126.0*126.0);	coord[CY][DOWNHILL1]=-1831.0;//down hill 1カーブ
	coord[CX][DOWNHILL2]=coord[CX][DOWNHILL2-1]+sqrtf(1521.0*1521.0+218.0*218.0);coord[CY][DOWNHILL2]=-823.0;//down hill 2カーブ
	coord[CX][DOWNHILL3]=coord[CX][DOWNHILL3-1]+sqrtf(907.0*907.0+130.0*130.0);	coord[CY][DOWNHILL3]=-1614.0;//down hill 3カーブ
	coord[CX][DOWNHILLFIN]=coord[CX][DOWNHILLFIN-1]+sqrtf(861.0*861.0+123.0*123.0);	coord[CY][DOWNHILLFIN]=-1831.0;//down hill  最後
	coord[CX][FIN]=coord[CX][FIN-1]+1155.0;										coord[CY][FIN]=-1831.0;//最後
}
*/
/*
void Move::setCoord(){
    coord[CX][SLOPE1]=1295.0;																coord[CY][SLOPE1]=0.0;//slope1前
	coord[CX][HILL1]=coord[CX][HILL1-1]+1063.0*cos(dtor(10.3));	coord[CY][HILL1]=295.0;//hill1前
	coord[CX][SLOPE2]=coord[CX][SLOPE2-1]+1087.0;						coord[CY][SLOPE2]=922.0;//slope2前
	coord[CX][HILL2]=coord[CX][HILL2-1]+777.0*cos(dtor(10.3));	coord[CY][HILL2]=1700.0;//hill2前
	coord[CX][SLOPE3]=coord[CX][SLOPE3-1]+1087.0;						coord[CY][SLOPE3]=2328.0;//slope3前
	coord[CX][HILL3]=coord[CX][HILL3-1]+1062.0*cos(dtor(10.3));	coord[CY][HILL3]=2612.0;//hill3前
//	coord[CX][HILL4]=coord[CX][HILL4-1]+377.0;								coord[CY][HILL4]=coord[CY][HILL4-1]-560.0;
	coord[CX][RIVER]=coord[CX][RIVER-1]+377.0;											coord[CY][RIVER]=1497.0-560.0;//river 前
	coord[CX][RIVER1]=coord[CX][RIVER1-1]+336.0;							coord[CY][RIVER1]=coord[CY][RIVER1-1]-407.0;//river 1
	coord[CX][RIVER4]=coord[CX][RIVER4-1]+70.0;								coord[CY][RIVER4]=coord[CY][RIVER4-1]-1060.0;//river 4
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
}*/
void Move::setCoord(){
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

coord[CX][FIN]=coord[CX][FIN-1]+5000.0;										coord[CY][FIN]=-1831.0;//最後
}
#define LINE 0
#define COORD 1
#define MODE COORD

#if MODE==LINE//ライントレース
void Move::cycle(){
	if(mode==USESENSOR){
		LineCycle();
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
	pid_gain_t gain=set_pid_gain(0.2,0.0,0.0);
	startSw->cycle();
	if(millis()-time>=1){
		time=millis();
		if(!startFlag){
			if(startSw->readDownEdge()) startFlag=true;
			task=startTask;
			robo->reset(startX,startY);
			output=dtor(initAngle);
			servoAngle=startAngle*(-1.0);
			servoAngle=area(servoAngle,-M_PI,M_PI);
		}else if(startFlag){
			if(startSw->readValue()){
				task=startTask;
				robo->reset(startX,startY);
				output=dtor(initAngle);
				servoAngle=startAngle*(-1.0);
				servoAngle=area(servoAngle,-M_PI,M_PI);
			}else{
				float targetRad=getTargetAngle();
				float nowRadius=getTurningRadius(servoAngle);
				float targetRadius=getTargetTurningRadius();
				float angle=0.0;

				if(task==DOWNHILL1_1||task==DOWNHILL2_1||task==DOWNHILL3_1){
					//gain=set_pid_gain(0.2,0.0,0.25);
					angle=getTargeRadiusAngle(0,output*(-1.0));
					//angle=rotationOutput(targetRadius-nowRadius,gain);
					output=angle*(-1.0);
				}else{
					gain=set_pid_gain(0.4,0.0,0.0);
					angle=rotationOutput(targetRad-servoAngle,gain);
					output-=angle;
				}

				output=floatlimit(dtor(-36.0+initAngle),output,dtor(36.0+initAngle));
				servoAngle=(output-dtor(initAngle))*(-1.0)+robo->getAngle();//右回転が+だから-1かけてる
				servoAngle=area(servoAngle,-M_PI,M_PI);
				//distance=getDistance();
			}
			servo->setAngle(output);
		}
		servo->cycle();
	}
}
#endif

void Move::LineCycle(){
	countWhile++;
	for(int i=0;i<5;i++){
		adData[i]=get_Average(countAverage,i,line->getValue(i));
	}
}

float Move::rotationOutput(float diff,pid_gain_t gain){
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
	float output=0;

	output=calc_pid(&data,area(diff,-M_PI,M_PI),gain);
	return output;
#endif
}

float Move::getTargetAngle(){
	float targetX=coord[CX][task];
	float targetY=coord[CY][task];
	float nextX=coord[CX][task+1];
	float nextY=coord[CY][task+1];
	float nowX=robo->getX();
	float nowY=robo->getY();
	//float dis=0.0;
	//float timeLeft=0.0;
	//float angleTime=0.0;
	static int oldTask=task;
	static int flag=0;
	static float cnt=1.0;
	float n=8.0;

	distance=get_vertical_distance_position(targetX,targetY,nowX,nowY,servoAngle);
	timeLeft=getTimeLeft(distance);
	angleTime=getAngleTime(area(getTargetRadian(nextX,nextY,nowX,nowY),-M_PI,M_PI),servoAngle);
	targetAngle=area(getTargetRadian(targetX,targetY,nowX,nowY),-M_PI,M_PI);

	if(task!=oldTask){
		cnt=1;
	}
	oldTask=task;

#if 0
	if(task==DOWNHILL1_1){
		if(flag==0){
			n=10.0;
			targetX=circleCenter[CX][0]+curveRadius[0]*cos(area(initCurveAngle[0]+((centralAngle[0]*cnt)/n),-M_PI,M_PI));
			targetY=circleCenter[CY][0]+curveRadius[0]*sin(area(initCurveAngle[0]+((centralAngle[0]*cnt)/n),-M_PI,M_PI));
			distance=get_vertical_distance_position(targetX,targetY,nowX,nowY,servoAngle);
			timeLeft=getTimeLeft(distance);
			nextX=circleCenter[CX][0]+curveRadius[0]*cos(area(initCurveAngle[0]+((centralAngle[0]*(cnt+1))/n),-M_PI,M_PI));
			nextY=circleCenter[CY][0]+curveRadius[0]*sin(area(initCurveAngle[0]+((centralAngle[0]*(cnt+1))/n),-M_PI,M_PI));
			angleTime=getAngleTime(area(getTargetRadian(nextX,nextY,nowX,nowY),-M_PI,M_PI),servoAngle);
			targetAngle=area(getTargetRadian(targetX,targetY,nowX,nowY),-M_PI,M_PI);
			/*if(timeLeft<200.0){
				cnt++;
				if(cnt>=n){
					flag=1;
					task++;
					cnt=1;
				}
			}*/
			if(distance<=50.0){
				cnt++;
				if(cnt>=n){
					flag=1;
					cnt=1;
					task++;
				}
			}
		}
	}else if(task==DOWNHILL2_1){
		n=8;
		if(flag==1){
			targetX=circleCenter[CX][1]+curveRadius[1]*cos(area(initCurveAngle[1]+((centralAngle[1]*cnt)/n),-M_PI,M_PI));
			targetY=circleCenter[CY][1]+curveRadius[1]*sin(area(initCurveAngle[1]+((centralAngle[1]*cnt)/n),-M_PI,M_PI));
			distance=get_vertical_distance_position(targetX,targetY,nowX,nowY,servoAngle);
			timeLeft=getTimeLeft(distance);
			nextX=circleCenter[CX][1]+curveRadius[1]*cos(area(initCurveAngle[1]+((centralAngle[1]*(cnt+1))/n),-M_PI,M_PI));
			nextY=circleCenter[CY][1]+curveRadius[1]*sin(area(initCurveAngle[1]+((centralAngle[1]*(cnt+1))/n),-M_PI,M_PI));
			angleTime=getAngleTime(area(getTargetRadian(nextX,nextY,nowX,nowY),-M_PI,M_PI),servoAngle);
			targetAngle=area(getTargetRadian(targetX,targetY,nowX,nowY),-M_PI,M_PI);

			/*if(timeLeft<200.0){
				cnt++;
				if(cnt>=n){
					flag=1;
					cnt=1;
				}
			}*/
			if(distance<=50.0){
				cnt++;
				if(cnt>=n){
					flag=2;
					cnt=1;
					task++;
				}
			}
		}
	}else if(task==DOWNHILL3_1){
		n=5;
		if(flag==2){
			targetX=circleCenter[CX][2]+curveRadius[2]*cos(area(initCurveAngle[2]+((centralAngle[2]*cnt)/n),-M_PI,M_PI));
			targetY=circleCenter[CY][2]+curveRadius[2]*sin(area(initCurveAngle[2]+((centralAngle[2]*cnt)/n),-M_PI,M_PI));
			distance=get_vertical_distance_position(targetX,targetY,nowX,nowY,servoAngle);
			timeLeft=getTimeLeft(distance);
			nextX=circleCenter[CX][2]+curveRadius[2]*cos(area(initCurveAngle[2]+((centralAngle[2]*(cnt+1))/n),-M_PI,M_PI));
			nextY=circleCenter[CY][2]+curveRadius[2]*sin(area(initCurveAngle[2]+((centralAngle[2]*(cnt+1))/n),-M_PI,M_PI));
			angleTime=getAngleTime(area(getTargetRadian(nextX,nextY,nowX,nowY),-M_PI,M_PI),servoAngle);
			targetAngle=area(getTargetRadian(targetX,targetY,nowX,nowY),-M_PI,M_PI);
			/*if(timeLeft<200.0){
				cnt++;
				if(cnt>=n){
					flag=1;
					cnt=1;
				}
			}*/
			if(distance<=50.0){
				cnt++;
				if(cnt>=n){
					flag=3;
					task++;
					cnt=1;
				}
			}
		}
	}else if(distance<=100.0){
		task++;
	}
#endif
	if(task!=FIN){
		if(task==DOWNHILL1_1||task==DOWNHILL2_1||task==DOWNHILL3_1){
			distance=	get_vertical_distance_position(targetX,targetY,robo->getServoX(),robo->getServoY(),servoAngle);
			if(distance<=80.0){
				task++;
			}
		}else{
			if(distance<=160.0){
				task++;
			}
		}
	}
	if(startSw->readValue()){
		flag=0;cnt=1;
	}

	return (targetAngle);
}

float Move::getTargetAngle(float targetX,float targetY,float nowX,float nowY){
	return getTargetRadian(targetX,targetY,nowX,nowY);
}

float Move::getDistance(){
	float targetX=coord[CX][task];
	float targetY=coord[CY][task];
	float nowX=robo->getX();
	float nowY=robo->getY();
	float value=get_distance(targetX,targetY,nowX,nowY);

	return value;
}

float Move::getDistance(float targetX, float targetY,float nowX,float nowY){
	return get_distance(targetX,targetY,nowX,nowY);
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

float Move::getServoAngle(){
	float angle=(output-dtor(initAngle))*(-1.0)+robo->getAngle();//右回転が+だから-1かけてる
	angle=area(angle,-M_PI,M_PI);
	return angle;
}

float Move::getSteeringOuterRingAngle(float angle){
	float value=-0.0069*angle*angle+1.0191*angle-0.935;
	value=dtor(value);
	return value;
}

float Move::getSteeringInnerRingAngle(float angle){
	float value=-0.0039*angle*angle+1.1319*angle-0.4349;
	value=dtor(value);
	return value;
}

float Move::getTurningRadius(float angle){
	//const float tread=165.0;
	const float length=190.0;
	float steer=0.0;
	float otherSteer=0.0;
    float turningRadius=0.0;

    steer=getSteeringInnerRingAngle(fabs(angle));
    otherSteer=getSteeringOuterRingAngle(fabs(angle));

    if(angle<0){
       	turningRadius=(length/2.0)*((1.0/sin(steer))+(1.0/sin(otherSteer)))*(-1.0);
    }else if(angle>0){
        turningRadius=(length/2.0)*((1.0/sin(steer))+(1.0/sin(otherSteer)));
    }else{
        turningRadius=0.0;
    }
	return turningRadius;
}

float Move::getTargetTurningRadius(){
	float radius=0.0;
	if(task==DOWNHILL1_0){
		radius=curveRadius[0];
	}else if(task==DOWNHILL2_0){
		radius=curveRadius[1];
	}else if(task==DOWNHILL3_0){
		radius=curveRadius[2];
	}
	return radius;
}

float Move::getTargeRadiusAngle(float radius, float output){
	float angle=0.0;

	if(task==DOWNHILL1_1){
		angle=dtor(10.0);//20.0
	}else if(task==DOWNHILL2_1){
		if(output>=dtor(-22.0)){
			//angle=dtor(-20.0);
			angle=output-dtor(0.5);
		}else{
			angle=dtor(-22.0);
		}
	}else if(task==DOWNHILL3_1){
		angle=dtor(5.0);
	}

	return angle;
}

float Move::getTimeLeft(float distance){
	static float oldTime=0.0;
	float time=9999.0;
	float velocity=robo->getVelocity();

	if(velocity<=0.0){
		time=oldTime;
	}else{
		time=(distance/fabs(velocity/1000.0));
	}
	oldTime=time;

	return time;
}

float Move::getAngleTime(float targetRad,float nowRad){
	float servoVelocity=servo->getVelocity();
	float time=0.0;
	time=(1.0/servoVelocity)*fabs(targetRad)*(1.0/1000.0);
	return time;
}

void Move::requestAngle(float targetX,float targetY,float nowX,float nowY){
	static pid_data_t data={0};
	pid_gain_t gain=set_pid_gain(pGain,iGain,dGain);
	float targetAngle=getTargetAngle(targetX,targetY,nowX,nowY);
	output-=calc_pid(&data,area(targetAngle-servoAngle,-M_PI,M_PI),gain);
	output=floatlimit(dtor(-45.0+initAngle),output,dtor(45.0+initAngle));
	servo->setAngle(output);
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
	printf("sd,%.2f,",rtod(servoAngle));
	printf("tx,%.2f,",coord[CX][task]);
	printf("ty,%.2f,",coord[CY][task]);
	printf("td,%.2f,",rtod(targetAngle));
	printf("vel,%.2f,",robo->getVelocity());
	printf("dis,%.2f,",distance);
	printf("task,%d,",task);
	printf("out%f",rtod(output));
	//printf("enc %.2f,",robo->getEncCnt());
}
