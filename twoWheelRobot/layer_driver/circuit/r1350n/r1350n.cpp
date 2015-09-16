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

	if(readingData[0] == 0xAA){
		readStart = ON;
	}

	if(readStart == ON){
		readingCount++;
		if(readingCount >= 15){
			readingCount = 0;
			readStart = OFF;
//						index = g_input_r1350n[2];
			//g_rate =
			int ang_temp=(readingData[3] & 0xFF) | ((readingData[4] << 8) & 0xFF00);
			if(ang_temp<32768) angleData=-ang_temp;
			else angleData=-ang_temp+65536;

			int rate_temp=(readingData[5] & 0xFF) | ((readingData[6] << 8) & 0xFF00);
			if(rate_temp<32768) rateData=-rate_temp;
			else rateData=-rate_temp+65536;

			int accelx_temp=(readingData[7] & 0xFF) | ((readingData[8] << 8) & 0xFF00);
			if(accelx_temp<32768) accelXData=-accelx_temp;
			else accelXData=-accelx_temp+65536;

			int accely_temp=(readingData[9] & 0xFF) | ((readingData[10] << 10) & 0xFF00);
			if(accely_temp<32768) accelYData=-accely_temp;
			else accelYData=-accely_temp+65536;

			int accelz_temp=(readingData[11] & 0xFF) | ((readingData[12] << 10) & 0xFF00);
			if(accelz_temp<32768) accelZData=-accelz_temp;
			else accelZData=-accelz_temp+65536;

			//g_rate = (temp1 & 0xFF) | ((temp2 << 8) & 0xFF00);
			//g_angle = (readingData[5] & 0xFF) | ((readingData[6] << 8) & 0XFF00);
			//g_accx = (readingData[7] & 0xFF) | ((readingData[8] << 8) & 0xFF00);
			//g_accy = (readingData[9] & 0xFF) | ((readingData[10] << 8) & 0XFF00);
			//g_accz = (readingData[11] & 0xFF) | ((readingData[12] << 8) & 0xFF00);
//						reserved = g_input_r1350n[13];

/*				check_sum = 	g_input_r1350n[2] + g_input_r1350n[3] + g_input_r1350n[4] + g_input_r1350n[5]
						     + g_input_r1350n[6] + g_input_r1350n[7] + g_input_r1350n[8] + g_input_r1350n[9]
						     + g_input_r1350n[10] + g_input_r1350n[11] + g_input_r1350n[12] + g_input_r1350n[13];*/
//			printf("%d\r",angleData);
			if(initialSetStart){
				initialAngleData=angleData;
				initialSetStart=0;
			}

		}
	}
}
