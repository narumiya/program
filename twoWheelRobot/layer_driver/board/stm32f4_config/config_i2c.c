#include "config_i2c.h"
#include "mcutime.h"
//int Init_i2c(GPIO_TypeDef *sda_port, uint16_t sda_pin,GPIO_TypeDef *scl_port, uint16_t scl_pin){return 0;};

void Init_i2c(I2C_TypeDef *use_i2c){
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef	I2C_InitStructure;

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


	I2C_StructInit(&I2C_InitStructure);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(use_i2c,&I2C_InitStructure);

	I2C_Cmd(use_i2c,ENABLE);
}



static int f_i2c_error=3;						//エラー時のフラグ

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

void I2cColorConfig(char mode){
	if(mode==LOW){
		delay_ms(200);
		I2cCommandSend(0x2A,0x00,0x84);
		delay_ms(5);
		I2cCommandSend(0x2A,0x00,0x04);
	}else if(mode==HIGH){
		delay_ms(200);
		I2cCommandSend(0x2A,0x00,0x89);
		delay_ms(5);
		I2cCommandSend(0x2A,0x00,0x09);
	}
}

void I2cCommandSend( char address, char command,  char data){
	I2C_GenerateSTART(USE_I2C,ENABLE);
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
	I2C_GenerateSTOP(USE_I2C,ENABLE);
}

uint8_t I2C_read_nack(I2C_TypeDef* I2Cx){
 	// disabe acknowledge of received data
 	// nack also generates stop condition after last byte received
 	// see reference manual for more info
 	I2C_AcknowledgeConfig(I2Cx, DISABLE);
 	I2C_GenerateSTOP(I2Cx, ENABLE);
 	// wait until one byte has been received
 	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
 	// read data from I2C data register and return data byte
 	uint8_t data = I2C_ReceiveData(I2Cx);
 	return data;
}

