#include "r1350n.hpp"
#include "logging.h"
#include <stdio.h>

#define ON 1
#define OFF 0

float R1350n::angle(){
	static float oldAngle=0.0;
	float angle=(angleData-initialAngleData)*M_PI/18000.0;

	if(angle > M_PI){
		angle-=2*M_PI;
	}else if(angle < -M_PI){
		angle+=2*M_PI;
	}
	if(angle>0&&oldAngle<0&&rateData<0)
		angleRoopCount--;
	if(angle<0&&oldAngle>0&&rateData>0)
		angleRoopCount++;
	oldAngle=angle;
//	angle+=angleRoopCount*2*M_PI;

	return angle;
}

void R1350n::serialReadChar(char data){
	readingData[readingCount] = data;

	if((readingData[0]&0xFF) == 0xAA){
		readStart = ON;
	}

	if(readStart == ON){
		readingCount++;
		if(readingCount >= 15){
			readingCount = 0;
			readStart = OFF;

			int check_sum = readingData[2] + readingData[3] + readingData[4] + readingData[5]
						     + readingData[6] + readingData[7] + readingData[8] + readingData[9]
						     + readingData[10] + readingData[11] + readingData[12] + readingData[13];

			if((check_sum&0xFF) == readingData[14]){
				int ang_temp=(readingData[3] & 0xFF) | ((readingData[4] << 8) & 0xFF00);
				if(ang_temp<32768) angleData=-ang_temp;
				else angleData=-ang_temp+65536;

				int rate_temp=(readingData[5] & 0xFF) | ((readingData[6] << 8) & 0xFF00);
				if(rate_temp<32768) rateData=-rate_temp;
				else rateData=-rate_temp+65536;

				int accelx_temp=(readingData[7] & 0xFF) | ((readingData[8] << 8) & 0xFF00);
				//if(accelx_temp<32768) accelXData=-accelx_temp;
				//else accelXData=-accelx_temp+65536;
				if(accelx_temp&0x8000){
					accelx_temp^=0xFFFF;
					accelx_temp+=1;
					accelx_temp*=-1;
				}
				accelXData=accelx_temp;

				int accely_temp=(readingData[9] & 0xFF) | ((readingData[10] << 8) & 0xFF00);
				//if(accely_temp<32768) accelYData=-accely_temp;
				//else accelYData=-accely_temp+65536;
				if(accely_temp&0x8000){
					accely_temp^=0xFFFF;
					accely_temp+=1;
					accely_temp*=-1;
				}
				accelYData=accely_temp;

				int accelz_temp=(readingData[11] & 0xFF) | ((readingData[12] << 8) & 0xFF00);
				//if(accelz_temp<32768) accelZData=-accelz_temp;
				//else accelZData=-accelz_temp+65536;
				if(accelz_temp&0x8000){
					accelz_temp^=0xFFFF;
					accelz_temp+=1;
					accelz_temp*=-1;
				}
				accelZData=accelz_temp;
			}

			if(initialSetStart){
				initialAngleData=angleData;
				initialSetStart=0;
			}
			for(int i=0;i<15;i++) readingData[i]='\0';
		}
	}
}
