#include "config_i2c.h"
#include "mcutime.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
//int Init_i2c(GPIO_TypeDef *sda_port, uint16_t sda_pin,GPIO_TypeDef *scl_port, uint16_t scl_pin){return 0;};

typedef struct{
	char data[26];
	int dataSize;
}I2C_t;

I2C_t i2c[256];
Rgb_t g_rgb;
//îzóÒÇÃå¬êîÇÕidÇÃêî

void Init_i2c(I2C_TypeDef *use_i2c){
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef	I2C_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	if(use_i2c == I2C1){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	}else if(use_i2c == I2C2){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	}
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);
	if(use_i2c == I2C1){
		GPIO_InitStructure.GPIO_Pin = I2C1_SCL_PIN | I2C1_SDA_PIN;
	}else if(use_i2c == I2C2){
		GPIO_InitStructure.GPIO_Pin = I2C2_SCL_PIN | I2C2_SDA_PIN;
	}

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	if(use_i2c == I2C1){
		GPIO_Init(I2C1_PORT, &GPIO_InitStructure);
		if(I2C1_SCL_PIN == GPIO_Pin_6){
			GPIO_PinAFConfig(I2C1_PORT, GPIO_PinSource6, GPIO_AF_I2C1);
		}else if(I2C1_SCL_PIN == GPIO_Pin_8){
			GPIO_PinAFConfig(I2C1_PORT, GPIO_PinSource8, GPIO_AF_I2C1);
		}
		if(I2C1_SDA_PIN == GPIO_Pin_7){
			GPIO_PinAFConfig(I2C1_PORT, GPIO_PinSource7, GPIO_AF_I2C1);
		}else if(I2C1_SDA_PIN == GPIO_Pin_9){
			GPIO_PinAFConfig(I2C1_PORT, GPIO_PinSource9, GPIO_AF_I2C1);
		}
	}else if(use_i2c == I2C2){
		GPIO_Init(I2C2_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(I2C2_PORT, GPIO_PinSource10, GPIO_AF_I2C2);
		GPIO_PinAFConfig(I2C2_PORT, GPIO_PinSource11, GPIO_AF_I2C2);
	}

	I2C_ITConfig(use_i2c, I2C_IT_EVT|I2C_IT_BUF|I2C_IT_ERR, ENABLE);
	I2C_StructInit(&I2C_InitStructure);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

	I2C_Cmd(use_i2c,ENABLE);

	I2C_Init(use_i2c,&I2C_InitStructure);

	/* Configure the I2C event priority */
	NVIC_InitStructure.NVIC_IRQChannel = I2C2_EV_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

int g_TxBufferSize=0;
int g_directionFlag=2;
int g_TxSlaveAddress=0;
int g_RxSlaveAddress=0;
char g_I2C2BufferRx[256]={0};
int g_RxBufferSize=0;
void I2C1_EV_IRQHandler(void){

}
void I2C1_ER_IRQHandler(void){
	if (I2C_GetITStatus(I2C1, I2C_IT_AF))
		I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
}

void I2C2_EV_IRQHandler(void){
	static int TxAddress=0;
	static int RxAddress=0;
	static int TxDataNum=0;
	static int RxDataNum=0;
	int j;

	switch (I2C_GetLastEvent(I2C2)){
    	case I2C_EVENT_MASTER_MODE_SELECT:
    		if(g_directionFlag==TX){
    			TxAddress=g_TxSlaveAddress;
    			I2C_Send7bitAddress(I2C2, TxAddress, I2C_Direction_Transmitter);
    		}else if(g_directionFlag==RX){
    			RxAddress=g_RxSlaveAddress;
    			I2C_Send7bitAddress(I2C2, RxAddress, I2C_Direction_Receiver);
    		}
    		break;
    	case I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED:
    		I2C_SendData(I2C2, i2c[TxAddress].data[TxDataNum++]);
    		break;
    	case I2C_EVENT_MASTER_BYTE_TRANSMITTED:
    		if(TxDataNum<g_TxBufferSize){
    			I2C_SendData(I2C2, i2c[TxAddress].data[TxDataNum++]);
    			if(g_TxBufferSize - TxDataNum<1)
    				I2C_GenerateSTOP(I2C2, ENABLE);
			}else{
	       		if(i2c[TxAddress].data[0]==0x03){
					g_RxBufferSize=8;
					g_RxSlaveAddress=0x55;
					g_directionFlag=RX;
					//I2C_Cmd(I2C2,ENABLE);
					I2C_GenerateSTART(I2C2, ENABLE);
	        	}
				for(j=0;j<26;j++)	i2c[TxAddress].data[j]='\0';
				TxDataNum=0;
				g_TxBufferSize=0;
			}
    		break;
    	case I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED:
    		//g_I2C2BufferRx[RxDataNum++]=I2C_ReceiveData(I2C2);
    		break;
    	case I2C_EVENT_MASTER_BYTE_RECEIVED:
    		g_I2C2BufferRx[RxDataNum++]=I2C_ReceiveData(I2C2);
    		if(g_RxBufferSize==RxDataNum+1){
    			I2C_AcknowledgeConfig(I2C2, DISABLE);
    			I2C_GenerateSTOP(I2C2, ENABLE);
    		}
    		if(g_RxBufferSize-RxDataNum<1){
    			if(RxAddress==0x55)
    				analaysColor(g_I2C2BufferRx);
        			RxDataNum=0;
        			g_RxBufferSize=0;
    				I2C_AcknowledgeConfig(USE_I2C, ENABLE);
    		}
    		break;
    	default:
    		break;
	}
}

void I2C2_ER_IRQHandler(void){
	if (I2C_GetITStatus(I2C2, I2C_IT_AF))
		I2C_ClearITPendingBit(I2C2, I2C_IT_AF);
}

static int f_i2c_error=3;

void I2c_lcd_cmd_send(char c){
	I2C_GenerateSTART(I2C_LCD_USE_I2C,ENABLE);
	 //I2c_chack_wait(I2C_EVENT_MASTER_MODE_SELECT);
	 while(!I2C_CheckEvent(I2C_LCD_USE_I2C, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C_LCD_USE_I2C,0x7C,I2C_Direction_Transmitter);
	// I2c_chack_wait(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	while(!I2C_CheckEvent(I2C_LCD_USE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C_LCD_USE_I2C,0x00);
	 while(!I2C_CheckEvent(I2C_LCD_USE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	I2C_SendData(I2C_LCD_USE_I2C,c);
	 //I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	 while(!I2C_CheckEvent(I2C_LCD_USE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C_LCD_USE_I2C,ENABLE);
}


void I2c_lcd_init(void){
	//if(f_i2c_error > 2){
		delay_ms(200);
		I2c_lcd_cmd_send(0x38);
		delay_ms(5);
		I2c_lcd_cmd_send(0x39);
		delay_ms(5);
		I2c_lcd_cmd_send(0x14);
		delay_ms(5);
		I2c_lcd_cmd_send(0x70);
		delay_ms(5);
		I2c_lcd_cmd_send(0x56);
		delay_ms(5);
		I2c_lcd_cmd_send(0x6C);
		delay_ms(5);
		I2c_lcd_cmd_send(0x38);
		delay_ms(5);
		I2c_lcd_cmd_send(0x0C);
		delay_ms(5);
		I2c_lcd_cmd_send(0x01);
		delay_ms(5);
	//}
}
void I2c_lcd_clr(void){
	if(f_i2c_error > 2){
		I2c_lcd_cmd_send(0x01);
		delay_ms(2);
	}
}
void I2c_lcd_locate(uint8_t x,uint8_t y){
	//if(f_i2c_error > 2){
		I2c_lcd_cmd_send(0x80 | y*0x40 | x );
	//}
}
void I2c_lcd_put_c(char c){
	/*if(f_i2c_error > 2){
		I2C_GenerateSTART(I2C_LCD_USE_I2C,ENABLE);
		 I2c_chack_wait(I2C_EVENT_MASTER_MODE_SELECT);
		I2C_Send7bitAddress(I2C_LCD_USE_I2C,0x7C,I2C_Direction_Transmitter);
		 I2c_chack_wait(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
		I2C_SendData(I2C_LCD_USE_I2C,0x80);
		 I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
		I2C_SendData(I2C_LCD_USE_I2C,c);
		 I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
		I2C_GenerateSTOP(I2C_LCD_USE_I2C,ENABLE);
	}*/
	I2C_GenerateSTART(I2C_LCD_USE_I2C,ENABLE);
	 //I2c_chack_wait(I2C_EVENT_MASTER_MODE_SELECT);
	 while(!I2C_CheckEvent(I2C_LCD_USE_I2C, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C_LCD_USE_I2C,0x7C,I2C_Direction_Transmitter);
	// I2c_chack_wait(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	while(!I2C_CheckEvent(I2C_LCD_USE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C_LCD_USE_I2C,0x40);
	 while(!I2C_CheckEvent(I2C_LCD_USE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	I2C_SendData(I2C_LCD_USE_I2C,c);
	 //I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	 while(!I2C_CheckEvent(I2C_LCD_USE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C_LCD_USE_I2C,ENABLE);
}

void I2c_lcd_put_str(char *str){
	while(*str!=0)I2c_lcd_put_c(*str++);
}
void I2c_chack_wait(int flag){
	static unsigned int time=0;

	if(millis()-time>=100){
		time=millis();
		while(!I2C_CheckEvent(I2C_LCD_USE_I2C,flag)){
			f_i2c_error+=1;
			break;
		}
	}
}
void I2CLcdCommand(void){
	delay_ms(100);
	I2cCommandSend(0x7C,0x00,0x38);delay_ms(2);
	I2cCommandSend(0x7C,0x00,0x39);delay_ms(2);
	I2cCommandSend(0x7C,0x00,0x14);delay_ms(2);
	I2cCommandSend(0x7C,0x00,0x70);delay_ms(2);
	I2cCommandSend(0x7C,0x00,0x56);delay_ms(2);
	I2cCommandSend(0x7C,0x00,0x6C);delay_ms(2);
	I2cCommandSend(0x7C,0x00,0x38);delay_ms(2);
	I2cCommandSend(0x7C,0x00,0x0C);delay_ms(2);
	I2cCommandSend(0x7C,0x00,0x01);delay_ms(30);
}
void I2CLcdCommandSend(char data){
	const int slaveAddress=0x7C;

	while(!(g_TxBufferSize==0&&g_RxBufferSize==0));
	i2c[slaveAddress].data[0]=0x00;
	i2c[slaveAddress].data[1]=data;
	g_TxBufferSize=2;
	g_TxSlaveAddress=slaveAddress;
	g_directionFlag=TX;
	I2C_GenerateSTART(I2C2,ENABLE);
}
void I2CLcdSendChar(char c){
	I2cCommandSend(0x7C,0x40,c);
}
void I2CLcdSendString(char *str){
	const int slaveAddress=0x7C;
	int i;

	while(!(g_TxBufferSize==0&&g_RxBufferSize==0));
	i2c[slaveAddress].data[0]=0x40;
	for(i=0;str[i]!='\0';i++)	i2c[slaveAddress].data[i+1]=str[i];
	g_TxBufferSize=strlen(i2c[slaveAddress].data);
	g_TxSlaveAddress=slaveAddress;
	g_directionFlag=TX;
	I2C_GenerateSTART(I2C2,ENABLE);
}

void I2CLcdLocate(char x,char y){
	char data=0x80|y * 0x40|x;
	I2cCommandSend(0x7C,0x00,data);
	delay_ms(1);
}

void I2CLcdClear(void){
	I2cCommandSend(0x7C,0x00,0x01);
}

void I2cColorConfig(char mode){
	static unsigned int time=0;
	static int flag=0;
	if(millis()-time>=5){
		time=millis();
		if(flag==0){
			if(mode==LOW)
				I2cCommandSend(0x54,0x00,0x84);
			else if(mode==HIGH)
				I2cCommandSend(0x54,0x00,0x89);
			flag=1;
		}else if(flag==1){
			if(mode==LOW)
				I2cCommandSend(0x54,0x00,0x04);
			else if(mode==HIGH)
				I2cCommandSend(0x54,0x00,0x09);
			flag=2;
		}else if(flag==2) flag=3;
		else if(flag==3){
			while(!(g_TxBufferSize==0&&g_RxBufferSize==0));
			g_TxSlaveAddress=0x54;
			i2c[g_TxSlaveAddress].data[0]=0x03;
			g_TxBufferSize=1;
			g_directionFlag=TX;
			I2C_GenerateSTART(I2C2,ENABLE);
		}
	}
}

void I2cCommandSend(int address,char command,char data){

	while(!(g_TxBufferSize==0&&g_RxBufferSize==0));
	i2c[address].data[0]=command;
	i2c[address].data[1]=data;
	g_TxBufferSize=2;
	g_TxSlaveAddress=address;
	g_directionFlag=TX;
	I2C_GenerateSTART(I2C2,ENABLE);
	/*I2C_GenerateSTART(USE_I2C,ENABLE);
	//I2c_chack_wait(I2C_EVENT_MASTER_MODE_SELECT);
	while(!I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(USE_I2C,address,I2C_Direction_Transmitter);
	// I2c_chack_wait(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	while(!I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(USE_I2C,command);
	 while(!I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	I2C_SendData(USE_I2C,data);
	 //I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	 while(!I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(USE_I2C,ENABLE);*/
}
void I2cGetColor(Rgb_t *rgb){
	char str[8]={0};

	I2cColorConfig(HIGH);
	/*while(I2C_GetFlagStatus(USE_I2C, I2C_FLAG_BUSY));
	I2C_GenerateSTART(USE_I2C, ENABLE);
	while(!I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(USE_I2C, 0x54, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_Cmd(USE_I2C, ENABLE);
	I2C_SendData(USE_I2C, 0x03);
	while(!I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTART(USE_I2C, ENABLE);
	while(!I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(USE_I2C, 0x55, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	i=8;int j=0;
	while(i){
	    if(i == 1){
	      I2C_AcknowledgeConfig(USE_I2C, DISABLE);
	      I2C_GenerateSTOP(USE_I2C, ENABLE);
	    }
		if(I2C_CheckEvent(USE_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED)){
			str[j]=I2C_ReceiveData(USE_I2C);
			j++;
			i--;
		}
	}
	I2C_AcknowledgeConfig(USE_I2C, ENABLE);
    //I2C_AcknowledgeConfig(USE_I2C, DISABLE);
    //I2C_GenerateSTOP(USE_I2C, ENABLE);
    rgb->red=str[0]<<8 | str[1];
	rgb->green=str[2]<<8 | str[3];
	rgb->blue=str[4]<<8 | str[5];
	rgb->infrared=str[6]<<8 | str[7];*/
	/*while(g_RxBufferSize!=0&&g_TxBufferSize);
	g_RxBufferSize=8;
	g_RxSlaveAddress=0x55;
	g_directionFlag=RX;*/
	//I2C_GenerateSTART(USE_I2C, ENABLE);
}

void analaysColor(char *str){
	g_rgb.red=str[0]<<8 | str[1];
	g_rgb.green=str[2]<<8 | str[3];
	g_rgb.blue=str[4]<<8 | str[5];
	g_rgb.infrared=str[6]<<8 | str[7];
}

Rgb_t getColor(void){return g_rgb;}
