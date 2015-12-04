#include "move.hpp"
#include <stdio.h>
#include <math.h>
#include "pin.hpp"
extern "C"{
#include "mcutime.h"
#include "calculate.h"
}

Move::Move(Analog &a0,Analog &a1,Analog &a2,Analog &a3,Analog &a4,ButtonInfo &swPin,Servo &servoPin,RoboCenter &robo){
	mode=USESENSOR;
	startSw=&swPin;
	servo=&servoPin;
	this->robo=&robo;
	an[0]=&a0;an[1]=&a1;
	an[2]=&a2;an[3]=&a3;
	an[4]=&a4;
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
	calibraFlag=false;
	useServo=true;
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
		/*for(int i=0;i<5;i++){
			an[i]->setupAnalogIn();
		}*/
	}
	if(useServo){
		servo->setup(20.0,dtor(180.0),1.5,2.3);//rb995
	}else{
		for(int i=0;i<2;i++){
			md[i]->setup();
		}
	}
	return 0;
}

void Move::setCoord(){
	coord[CX][0]=1295.0;coord[CY][0]=0.0;//slope1
	coord[CX][1]=2358.0;coord[CY][1]=295.0;//hill1
	coord[CX][2]=3445.0;coord[CY][2]=922.0;//slope2
	coord[CX][3]=4223.0;coord[CY][3]=1700.0;//hill2
	coord[CX][4]=5310.0;coord[CY][4]=2328.0;//slope3
	coord[CX][5]=6376.0;coord[CY][5]=2698.0;//hill3
	coord[CX][6]=6750.0;coord[CY][6]=1497.0;//river 前
	coord[CX][7]=7228.0;coord[CY][7]=1019.0;//river 1
	coord[CX][8]=6874.0;coord[CY][8]=665.0;//river 2
	coord[CX][9]=7228.0;coord[CY][9]=312.0;//river 3
	coord[CX][10]=6874.0;coord[CY][10]=41.0;//river 4
	/*coord[CX][0]=500.0;coord[CY][0]=0.0;//slope1
	coord[CX][1]=1000;coord[CY][1]=1850;//hill1
	coord[CX][2]=2000;coord[CY][2]=1850;//slope2
	coord[CX][3]=2500;coord[CY][3]=0.0;//hill2
	coord[CX][4]=3500;coord[CY][4]=0.0;//hill2*/
}

#define LINE 0
#define COORD 1
#define MODE COORD

#if MODE==LINE//ライントレース
void Move::cycle(){
	if(mode==USESENSOR){
		TPR105Cycle();
		//if(!calibraFlag)calibraFlag=calibra();
	}else	calibraFlag=true;
	startSw->cycle();
	if(millis()-time>=1){
		time=millis();
		if(!startFlag){
			//if(calibraFlag){
				if(startSw->readDownEdge()) startFlag=true;
			//}
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
	pid_gain_t gain=set_pid_gain(0.10,0.0,0.13);
	startSw->cycle();
	if(millis()-time>=1){
		time=millis();
		if(!startFlag){
			if(startSw->readDownEdge()) startFlag=true;
		}else if(startFlag){
			float angle=rotationOutput(gain);
			output-=angle;
			output=floatlimit(dtor(-10.0),output,dtor(75.0));
			servoAngle=(output-dtor(initAngle))*(-1.0)+robo->getAngle();//右回転が+だから-1かけてる
			//float theta=area(servoAngle+radiusReverse(robo->getEncCnt()),-M_PI,M_PI);
			//servoX+=fabs(robo->getEncCnt())*cos(theta);
			//servoY+=	fabs(robo->getEncCnt())*sin(theta);
			distance=getDistance();

			if(task==5){
				if(distance<=260){
					task++;
				}
			}else if(task>=7){
				if(distance<=260){
					task++;
				}
			}else{
				if(distance<=180){
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
			output=dtor(initAngle);
			robo->setX(0.0);
			robo->setY(0.0);
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
void Move::setDuty(float straight,float rotat){
	md[0]->duty(straight-rotat);
	md[1]->duty(straight+rotat);
}

void Move::TPR105Cycle(){
	countWhile++;
	for(int i=0;i<5;i++){
		adData[i]=get_Average(countAverage,i,an[i]->analogRead());
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
float Move::getTargetAngle(){
	float targetX=coord[CX][task];
	float targetY=coord[CY][task];
	float nowX=robo->getX();
	float nowY=robo->getY();
//	float nowX=servoX;
//	float nowY=servoY;
	targetAngle=getTargetRadian(targetX,targetY,nowX,nowY);
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

int Move::calibra(){
	static int flag=0;

	switch(flag){
	case 0:
		if(!startSw->readDownEdge())	white=adData[1]+adData[3];
		else{
			flag=1;
			led1.digitalHigh();
			delay_ms(500);
		}
		break;
	case 1:
		if(!startSw->readDownEdge())	other=adData[1]+adData[3];
		else{
			flag=2;
			middle=(white+other)/2;
			led2.digitalHigh();
			delay_ms(500);
			return 1;
		}
		break;
	}
	return 0;
}
