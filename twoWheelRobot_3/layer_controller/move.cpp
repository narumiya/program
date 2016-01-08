#include "move.hpp"
#include <stdio.h>
#include <math.h>
#include "pin.hpp"
extern "C"{
#include "mcutime.h"
#include "calculate.h"
}

Move::Move(LineSensor &line,Digital &digital,ButtonInfo &sw0Pin,ButtonInfo &sw1Pin,Servo &servoPin,RoboCenter &robo){
	mode=NONSENSOR;
	button0=&sw0Pin;
	button1=&sw1Pin;
	servo=&servoPin;
	buzz=&digital;
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
		initCurveAngle[i]=0.0;//downhill “Ë“üŽž‰ŠúŠp“x
		curveRadius[i]=0.0;//down hill ”¼Œa
		centralAngle[i]=0.0;//down hill ’†SŠp
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
	radius=0.0;
	radiusServo=0.0;
	timeLeft=9999.0;
	radiusR=0;
	radiusL=0;
}

int Move::setup(){
	if(mode==USESENSOR)	line->setup();
	button0->setup(true,25);
	button1->setup(true,25);
	led1.setupDigitalOut();
	led2.setupDigitalOut();
	led3.setupDigitalOut();
	setCoord();
	setStartCoord();
	servo->setup(20.0,dtor(180.0),1.5,2.3);//rb995
	cycleTime=5;
	initAngle=30.0;
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
	startAngle=getTargetRadian(coord[CX][DOWNHILL+1],coord[CY][DOWNHILL+1],startX,startY)*(-1.0);//ƒWƒƒƒCƒ‚ÌŠp“x”½‘Î‚Ì‚½‚ß”½“]
	robo->setAngle(startAngle);
	startTask=DOWNHILL+1;

	return 0;
}

#if 1
void Move::setCoord(){
	coord[CX][SLOPE1]=1295.0;																	coord[CY][SLOPE1]=0.0;//slope1‘O
	coord[CX][HILL1]=coord[CX][HILL1-1]+1062.518*cos(dtor(10.3));	coord[CY][HILL1]=294.923;//hill1‘O
	coord[CX][SLOPE2]=coord[CX][SLOPE2-1]+1087.114;						coord[CY][SLOPE2]=coord[CY][SLOPE2-1]+627.646;//slope2‘O
	coord[CX][HILL2]=coord[CX][HILL2-1]+777.817*cos(dtor(10.3));	coord[CY][HILL2]=coord[CY][HILL2-1]+777.817;//hill2‘O
	coord[CX][SLOPE3]=coord[CX][SLOPE3-1]+1087.114;						coord[CY][SLOPE3]=coord[CY][SLOPE3-1]+627.646;//slope3‘O
	coord[CX][HILL3]=coord[CX][HILL3-1]+1062.0*cos(dtor(10.3));		coord[CY][HILL3]=coord[CY][HILL3-1]+284.701;//hill3‘O
	coord[CX][HILL4]=coord[CX][HILL4-1]+377.646;								coord[CY][HILL4]=coord[CY][HILL4-1]-466.078;
	coord[CX][RIVER]=coord[CX][RIVER-1];												coord[CY][RIVER]=coord[CY][RIVER-1]-649.435;//river ‘O
	coord[CX][RIVER1]=coord[CX][RIVER1-1]+194.975;							coord[CY][RIVER1]=coord[CY][RIVER1-1]-194.975;//river 1
	coord[CX][RIVER2]=coord[CX][RIVER2-1]+47.151;							coord[CY][RIVER2]=coord[CY][RIVER2-1]-518.535;//river 2
	coord[CX][RIVER3]=coord[CX][RIVER3-1]+94.271;							coord[CY][RIVER3]=coord[CY][RIVER3-1]-1037.1;//river 2
	coord[CX][HIGHLAND]=coord[CX][HIGHLAND-1]+353.553;				coord[CY][HIGHLAND]=coord[CY][HIGHLAND-1]-353.553;
	coord[CX][DOWNHILL]=coord[CX][DOWNHILL-1]+636.41;				coord[CY][DOWNHILL]=coord[CY][DOWNHILL-1]-636.396;//down hill Žn‚Ü‚è

	coord[CX][DOWNHILL1_0]=coord[CX][DOWNHILL1_0-1]+544.893*cos(dtor(-44.96));coord[CY][DOWNHILL1_0]=coord[CY][DOWNHILL1_0-1]+544.893*sin(dtor(-44.96));
	//down hill 1‰ñ–Ú ‰~‚Ì’†SÀ•W
	curveRadius[0]=713.385;
	centralAngle[0]=dtor(90.763);
	circleCenter[CX][0]=coord[CX][DOWNHILL1_0]-curveRadius[0]*cos(dtor(44.74-180.0));
	circleCenter[CY][0]=coord[CY][DOWNHILL1_0]-curveRadius[0]*sin(dtor(44.74-180.0));
	initCurveAngle[0]=dtor(44.74-180.0);
	coord[CX][DOWNHILL1_1]=circleCenter[CX][0]+curveRadius[0]*cos(dtor(135.503-180.0));coord[CY][DOWNHILL1_1]=circleCenter[CY][0]+713.385*sin(dtor(135.503-180.0));
	coord[CX][DOWNHILL2_0]=coord[CX][DOWNHILL1_1]+863.105*cos(dtor(45.22));coord[CY][DOWNHILL2_0]=coord[CY][DOWNHILL1_1]+863.105*sin(dtor(45.22));
	//down hill 2‰ñ–Ú ‰~‚Ì’†SÀ•W
	curveRadius[1]=600.123;
	centralAngle[1]=dtor(97.911);
	circleCenter[CX][1]=coord[CX][DOWNHILL2_0]-curveRadius[1]*cos(dtor(37.6+97.911));
	circleCenter[CY][1]=coord[CY][DOWNHILL2_0]-curveRadius[1]*sin(dtor(37.6+97.911));
	initCurveAngle[1]=dtor(37.6+97.911);
	//coord[CX][DOWNHILL2_1]=circleCenter[CX][1]+curveRadius[1]*cos(dtor(37.599));coord[CY][DOWNHILL2_1]=circleCenter[CY][1]+curveRadius[1]*sin(dtor(37.599));
	//coord[CX][DOWNHILL3_0]=coord[CX][DOWNHILL2_1]+555.924*cos(dtor(-51.83));coord[CY][DOWNHILL3_0]=coord[CY][DOWNHILL2_1]+555.924*sin(dtor(-51.83));

	coord[CX][DOWNHILL3_0]=circleCenter[CX][1]+curveRadius[1]*cos(dtor(37.599))+555.924*cos(dtor(-51.83));coord[CY][DOWNHILL3_0]=circleCenter[CY][1]+curveRadius[1]*sin(dtor(37.599))+555.924*sin(dtor(-51.83));

	//down hill 3‰ñ–Ú ‰~‚Ì’†SÀ•W
	curveRadius[2]=852.293;
	centralAngle[2]=dtor(97.911);
	circleCenter[CX][2]=coord[CX][DOWNHILL3_0]-curveRadius[2]*cos(dtor(37.6-180.0));
	circleCenter[CY][2]=coord[CY][DOWNHILL3_0]-curveRadius[2]*sin(dtor(37.6-180.0));
	initCurveAngle[2]=dtor(37.6-180.0);
	coord[CX][DOWNHILL3_1]=circleCenter[CX][2]+curveRadius[2]*cos(dtor(90.041-180.0));coord[CY][DOWNHILL3_1]=circleCenter[CY][2]+curveRadius[2]*sin(dtor(90.041-180.0));
	coord[CX][DOWNHILL3_2]=coord[CX][DOWNHILL3_2-1]+303.090;coord[CY][DOWNHILL3_2]=coord[CY][DOWNHILL3_2-1];

	coord[CX][FIN]=coord[CX][FIN-1]+500.0;										coord[CY][FIN]=coord[CY][DOWNHILL3_2-1];//ÅŒã
}
#endif
#if 0
void Move::setCoord(){
	coord[CX][0]=440.0;	coord[CY][0]=0.0;
	coord[CX][1]=600.0;	coord[CY][1]=200.0;
	coord[CX][2]=600.0;	coord[CY][2]=1000.0;
	coord[CX][3]=600.0;	coord[CY][3]=10000.0;
	/*coord[CX][0]=500.0;	coord[CY][0]=500.0;
	coord[CX][1]=1000.0;	coord[CY][1]=0.0;*/
}
#endif

void Move::setStartCoord(){
	startCoord[CX][0]=0.0;startCoord[CY][0]=0.0;
	startCoord[CX][1]=coord[CX][HILL1];startCoord[CY][1]=coord[CY][HILL1];
	startCoord[CX][2]=coord[CX][HILL2];startCoord[CY][2]=coord[CY][HILL2];
	startCoord[CX][3]=coord[CX][RIVER];startCoord[CY][3]=coord[CY][RIVER];
	startCoord[CX][4]=coord[CX][HIGHLAND];startCoord[CY][4]=coord[CY][HIGHLAND];
}
void Move::cycle(){
	button0->cycle();
	button1->cycle();
	decisionRestartTesk();
	if(millis()-time>=5){
		time=millis();
		if(!startFlag){
			if(button1->readValue()) startFlag=true;
			task=startTask;
			robo->reset(startX,startY);
			output=dtor(initAngle);
			servoAngle=startAngle*(-1.0);
			servoAngle=area(servoAngle,-M_PI,M_PI);
		}else if(startFlag){
			if(button1->readValue()){
				task=startTask;
				robo->reset(startX,startY);
				output=dtor(initAngle);
				servoAngle=startAngle*(-1.0);
				servoAngle=area(servoAngle,-M_PI,M_PI);
			}else{
				float targetRad=getTargetAngle();
				float angle=0.0;

				output=targetRad*(-1.0)+dtor(initAngle);//ƒT[ƒ{‰E•ûŒü‚ª+‚È‚Ì‚Å-1‚©‚¯‚Ä‚é
				output=floatlimit(dtor(-36.0+initAngle),output,dtor(36.0+initAngle));
				servoAngle=(output-dtor(initAngle))*(-1.0)+robo->getAngle();//‰E‰ñ“]‚ª+‚¾‚©‚ç-1‚©‚¯‚Ä‚é
				servoAngle=area(servoAngle,-M_PI,M_PI);
			}
			servo->setAngle(output);
		}
		servo->cycle();
	}
}

void Move::LineCycle(){
	countWhile++;
	for(int i=0;i<5;i++){
		adData[i]=get_Average(countAverage,i,line->getValue(i));
	}
}

float Move::rotationOutput(float diff,pid_gain_t gain){
	static pid_data_t data={0};
	float output=0;

	output=calc_pid(&data,area(diff,-M_PI,M_PI),gain);
	return output;
}

float Move::getTargetAngle(){
	static int oldTask=task;
	static int buzzFlag=0;
	static uint64_t time=millis();
	float targetX=coord[CX][task];
	float targetY=coord[CY][task];
	float nowX=robo->getServoX();//robo->getX();
	float nowY=robo->getServoY();//robo->getY();

	distance=get_vertical_distance_position(targetX,targetY,nowX,nowY,servoAngle);
	//distance=getDistance(targetX,targetY,nowX,nowY);
	//timeLeft=getTimeLeft(distance);
	//angleTime=getAngleTime(area(getTargetRadian(nextX,nextY,nowX,nowY),-M_PI,M_PI),servoAngle);
	//targetAngle=area(getTargetRadian(targetX,targetY,nowX,nowY),-M_PI,M_PI);

	targetAngle=getServoAngle(targetX,targetY);
	this->radiusServo=targetAngle;

	if(task!=FIN){
		if(task==HILL3||task==RIVER1||task==RIVER2||task==DOWNHILL1_1||/*task==DOWNHILL2_1||*/task==DOWNHILL3_1){
			//distance=	get_vertical_distance_position(targetX,targetY,robo->getServoX(),robo->getServoY(),servoAngle);
			//distance=getDistance(targetX,targetY,nowX,nowY);
			if(distance<=130.0){//120//60
				task++;
			}
		}else{
			if(task==DOWNHILL1_0||task==DOWNHILL2_0||task==DOWNHILL3_0){
				//distance=getDistance(targetX,targetY,robo->getX(),robo->getY());
				if(distance<=130.0){//60
					task++;
				}
			}else{
				if(distance<=130.0){//60//100.0
					task++;
				}
			}
		}
	}
	if(oldTask!=task){
		buzzFlag=1;
	}
	if(buzzFlag==1){
		if(millis()-time<=300){
			buzz->digitalHigh();
			led3.digitalHigh();
		}else{
			buzzFlag=0;
		}
	}else{
		time=millis();
		led3.digitalLow();
		buzz->digitalLow();
	}

	oldTask=task;
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
	float nowAngle=robo->getAngle();
	float value=get_vertical_distance_position(targetX,targetY,nowX,nowY,nowAngle);

	return value;
}

float Move::radiusToServo(float radius){
	if(radius==0){
		return 0.0;
	}else if(3945.0<=radius&&radius<=6367.0){
		return 2.0;
	}else if(2859.0<=radius&&radius<=3945.0){
		return 3.0;
	}else if(2247.0<=radius&&radius<=2859.0){
		return 4.0;
	}else if(1854.0<=radius&&radius<=2247.0){
		return 5.0;
	}else if(1581.0<=radius&&radius<=1854.0){
		return 6.0;
	}else if(1563.0<=radius&&radius<=1581.0){
		return 7.0;
	}else if(1193.0<=radius&&radius<=1563.0){
		return 8.0;
	}else if(1089.0<=radius&&radius<=1193.0){
		return 9.0;
	}else if(1003.0<=radius&&radius<=1089.0){
		return 10.0;
	}else if(932.0<=radius&&radius<=1003.0){
		return 11.0;
	}else if(871.0<=radius&&radius<=932.0){
		return 12.0;
	}else if(818.0<=radius&&radius<=871.0){
		return 13.0;
	}else if(772.0<=radius&&radius<=818.0){
		return 14.0;
	}else if(732.0<=radius&&radius<=772.0){
		return 15.0;
	}else if(696.0<=radius&&radius<=732.0){
		return 16.0;
	}else if(664.0<=radius&&radius<=696.0){
		return 17.0;
	}else if(635.0<=radius&&radius<=664.0){
		return 18.0;
	}else if(610.0<=radius&&radius<=635.0){
		return 19.0;
	}else if(586.0<=radius&&radius<=610.0){
		return 20.0;
	}else if(565.0<=radius&&radius<=586.0){
		return 21.0;
	}else if(545.0<=radius&&radius<=565.0){
		return 22.0;
	}else if(527.0<=radius&&radius<=545.0){
		return 23.0;
	}else if(510.0<=radius&&radius<=527.0){
		return 24.0;
	}else if(494.0<=radius&&radius<=510.0){
		return 25.0;
	}else if(480.0<=radius&&radius<=494.0){
		return 26.0;
	}else if(466.0<=radius&&radius<=480.0){
		return 27.0;
	}else if(453.0<=radius&&radius<=466.0){
		return 28.0;
	}else if(441.0<=radius&&radius<=453.0){
		return 29.0;
	}else if(430.0<=radius&&radius<=441.0){
		return 30.0;
	}else if(419.0<=radius&&radius<=430.0){
		return 31.0;
	}else if(409.0<=radius&&radius<=419.0){
		return 32.0;
	}else if(399.0<=radius&&radius<=409.0){
		return 33.0;
	}else if(390.0<=radius&&radius<=399.0){
		return 34.0;
	}else if(381.0<=radius&&radius<=390.0){
		return 35.0;
	}else if(373.0<=radius&&radius<=381.0){
		return 36.0;
	}else if(0.0<radius&&radius<=373.0){
		return 36.0;
	}

	return 0.0;
}

float Move::getServoAngle(){
	float angle=(output-dtor(initAngle))*(-1.0)+robo->getAngle();//‰E‰ñ“]‚ª+‚¾‚©‚ç-1‚©‚¯‚Ä‚é
	angle=area(angle,-M_PI,M_PI);
	return angle;
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

float Move::getServoAngle(float targetX,float targetY){
	float nowFrontX=robo->getServoX();
	float nowFrontY=robo->getServoY();
	float nowBackX=robo->getX();
	float nowBackY=robo->getY();
	float nowFrontRTireX=robo->getFrontRTireX();
	float nowFrontRTireY=robo->getFrontRTireY();
	float nowFrontLTireX=robo->getFrontLTireX();
	float nowFrontLTireY=robo->getFrontLTireY();
	float nowBackRTireX=robo->getBackRTireX();
	float nowBackRTireY=robo->getBackRTireY();
	float slope0=0.0;//–Ú•W’n‚ÆŒ»Ý’n‚ÌŒX‚«
	float slope1=0.0;//Œã‚ë‚ÌŽ²‚ÌŒX‚«
	float intercept0=0.0;//–Ú•W’n‚Æù‰ñ”¼Œa’†S‚Ì’¼i‚ÌØ•Ð
	float intercept1=0.0;//Œã‚ë‚ÌŽ²‚ÌØ•Ð
	float mat[2][3]={0.0};
	float radius=0.0;
	float radiusR=0.0;
	float radiusL=0.0;
	float resultAngle=0.0;
	Ans_t ans={0.0};

	if(targetX==nowFrontX){
		slope0=0.0;
		intercept0=(targetY+nowFrontY)/2.0;
		mat[0][0]=1.0;
		mat[0][1]=0.0;
		mat[0][2]=targetX;
	}else{
		slope0=(targetY-nowFrontY)/(targetX-nowFrontX);
		intercept0=(targetY+nowFrontY)/2.0+(1.0/slope0)*((targetX+nowFrontX)/2.0);
		mat[0][0]=1.0;
		mat[0][1]=slope0;
		mat[0][2]=slope0*intercept0;
	}

	if(nowBackRTireX==nowBackX){
		mat[1][0]=1.0;
		mat[1][1]=0.0;
		mat[1][2]=nowBackX;
	}else{
		slope1=(nowBackRTireY-nowBackY)/(nowBackRTireX-nowBackX);
		intercept1=nowBackY-(slope1*nowBackX);
		mat[1][0]=slope1;
		mat[1][1]=-1.0;
		mat[1][2]=-intercept1;
	}

	ans=crameRequation(mat);

	radiusR=getDistance(nowFrontRTireX,nowFrontRTireY,ans.x,ans.y);
	radiusL=getDistance(nowFrontLTireX,nowFrontLTireY,ans.x,ans.y);

    if(radiusR>radiusL){
        radius=radiusR;
        resultAngle=dtor(radiusToServo(radius));
    }else{
        radius=radiusL;
        resultAngle=dtor(radiusToServo(radius))*(-1.0);
    }
    this->radius=radius;
    this->radiusR=radiusR;
    this->radiusL=radiusL;
	return (resultAngle);
}

float Move::getTargeRadiusAngle(float radius){
	float angle=0.0;

	if(task==DOWNHILL1_1){
		angle=dtor(initAngle-15.0);//10.0
	//}else if(task==DOWNHILL2_1){
	//	angle=dtor(initAngle+18.0);
	}else if(task==DOWNHILL3_1){
		angle=dtor(initAngle-10.0);
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

void Move::decisionRestartTesk(){
	static int task=0;
	int value=0;
	static int oldValue=0;
	static long int time=millis();
	int setTask=0;

	if(!startFlag){
		if(millis()-time>=50){
			time=millis();
			value=button0->readValue();
	        if(oldValue==0&&value==1){
	            oldValue=value;
	            task++;
	        }else{
	            oldValue=value;
	        }
		}

		if(task>4)	task=0;

		switch(task){
		case 0:
			led1.digitalLow();
			led2.digitalLow();
			led3.digitalLow();
			setTask=0;
		break;
		case 1:
			led1.digitalHigh();
			led2.digitalLow();
			led3.digitalLow();
			setTask=HILL1;
		break;
		case 2:
			led1.digitalLow();
			led2.digitalHigh();
			led3.digitalLow();
			setTask=HILL2;
		break;
		case 3:
			led1.digitalHigh();
			led2.digitalHigh();
			led3.digitalLow();
			setTask=HILL3;
		break;
		case 4:
			led1.digitalLow();
			led2.digitalLow();
			led3.digitalHigh();
			setTask=HIGHLAND;
		break;
		default: break;
		}
		getStartCoord(setTask);
	}
}

void Move::getStartCoord(int task){
	if(task==0){
		startX=-495.0+73.0;
		//startX=0.0;
		startY=0.0;
		startAngle=0.0;
		robo->setAngle(startAngle);
		startTask=0;
	}else if(task==HILL1){
		startX=startCoord[CX][1];
		startY=startCoord[CY][1];
		startAngle=area(getTargetRadian(coord[CX][task+1],coord[CY][task+1],startX,startY),-M_PI,M_PI);
		robo->setAngle(startAngle*(-1.0));//ƒWƒƒƒCƒ‚ÌŠp“x”½‘Î‚Ì‚½‚ß”½“]
		startX+=fabs(robo->getEncToBehind())*cos(startAngle);
		startY+=fabs(robo->getEncToBehind())*sin(startAngle);
		startTask=task+1;
	}else if(task==HILL2){
		startX=startCoord[CX][2];
		startY=startCoord[CY][2];
		startAngle=area(getTargetRadian(coord[CX][task+1],coord[CY][task+1],startX,startY),-M_PI,M_PI);
		robo->setAngle(startAngle*(-1.0));//ƒWƒƒƒCƒ‚ÌŠp“x”½‘Î‚Ì‚½‚ß”½“]
		startX+=fabs(robo->getEncToBehind())*cos(startAngle);
		startY+=fabs(robo->getEncToBehind())*sin(startAngle);
		startTask=task+1;
	}else if(task==HILL3){
		startX=startCoord[CX][3];
		startY=startCoord[CY][3];
		startAngle=area(getTargetRadian(coord[CX][task+1],coord[CY][task+1],startX,startY),-M_PI,M_PI);
		robo->setAngle(startAngle*(-1.0));//ƒWƒƒƒCƒ‚ÌŠp“x”½‘Î‚Ì‚½‚ß”½“]
		startX+=fabs(robo->getEncToBehind())*cos(startAngle);
		startY+=fabs(robo->getEncToBehind())*sin(startAngle);
		startTask=task+1;
	}else if(task==HIGHLAND){
		startX=startCoord[CX][4];
		startY=startCoord[CY][4];
		startAngle=area(getTargetRadian(coord[CX][task+1],coord[CY][task+1],startX,startY),-M_PI,M_PI);
		robo->setAngle(startAngle*(-1.0));//ƒWƒƒƒCƒ‚ÌŠp“x”½‘Î‚Ì‚½‚ß”½“]
		startX+=fabs(robo->getEncToBehind())*cos(startAngle);
		startY+=fabs(robo->getEncToBehind())*sin(startAngle);
		startTask=task+1;
	}else{
		startX=coord[CX][task];
		startY=coord[CY][task];
		startAngle=area(getTargetRadian(coord[CX][task+1],coord[CY][task+1],startX,startY),-M_PI,M_PI);
		robo->setAngle(startAngle*(-1.0));//ƒWƒƒƒCƒ‚ÌŠp“x”½‘Î‚Ì‚½‚ß”½“]
		startX=coord[CX][task]+fabs(robo->getEncToBehind())*cos(startAngle);
		startY=coord[CY][task]+fabs(robo->getEncToBehind())*sin(startAngle);
		startTask=task+1;
	}
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
	//printf("sd,%.2f,",rtod(servoAngle));
	printf("tx,%.2f,",coord[CX][task]);
	printf("ty,%.2f,",coord[CY][task]);
	//printf("td,%.2f,",rtod(targetAngle));
	//printf("vel,%.2f,",robo->getVelocity());
	printf("dis,%.2f,",distance);
	printf("task,%d,",task);
	//printf("out,%f,",rtod(output)-initAngle);
	//printf("radius,%f,",radius);
	printf("radiusR,%f,",radiusR);
	printf("radiusL,%f,",radiusL);
	printf("servo,%f,",rtod(radiusServo));
/*	printf("radius,%f,",radius);
	printf("servo,%f,",rtod(radiusServo));
	printf("servoX,%.2f,servoY,%.2f,",robo->getServoX(),robo->getServoY());
	printf("x,%.2f,y,%.2f,",robo->getX(),robo->getY());
	printf("backX,%.2f,backY,%.2f,",robo->getBackRTireX(),robo->getBackRTireY());
	printf("FRX,%.2f,FRY,%.2f,",robo->getFrontRTireX(),robo->getFrontRTireY());
	printf("FLX,%.2f,FLY,%.2f,",robo->getFrontLTireX(),robo->getFrontLTireY());
*/

	//printf("enc %.2f,",robo->getEncCnt());
	//printf("enc,%d",robo->)
}
