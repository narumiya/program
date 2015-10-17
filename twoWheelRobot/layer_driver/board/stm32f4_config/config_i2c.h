#ifndef CONFIG_I2C_H
#define CONFIG_I2C_H

#include "cmsis_lib/include/stm32f4xx_i2c.h"
#include "stm32f4xx.h"

#define TX 0
#define RX 1

#define I2C1_SCL_PIN	GPIO_Pin_6
#define I2C1_SDA_PIN	GPIO_Pin_7
//#define I2C1_SCL_PIN	GPIO_Pin_8
//#define I2C1_SDA_PIN	GPIO_Pin_9
#define I2C1_PORT	GPIOB

#define I2C2_SCL_PIN	GPIO_Pin_10
#define I2C2_SDA_PIN	GPIO_Pin_11
#define I2C2_PORT	GPIOB

void Init_i2c(I2C_TypeDef *use_i2c);

//----------------------------------------------------------
/*I2C_LCDの機能 */
//I2C_LCDで使用しているI2Cモジュール
#define I2C_LCD_USE_I2C		 I2C2//使用するI2cモジュール
void I2c_chack_wait(int flag);
void I2c_lcd_cmd_send(char c);
void I2c_lcd_init(void);
void I2c_lcd_clr(void);
void I2c_lcd_locate(uint8_t x,uint8_t y);
void I2c_lcd_put_c(char c);
void I2c_lcd_put_str(char *str);

void I2CLcdCommand(void);
void I2CLcdCommandSend(char data);
void I2CLcdSendChar(char c);
void I2CLcdSendString(char *str);
void I2CLcdLocate(char x,char y);
void I2CLcdClear(void);

#define LOW 0
#define HIGH 1
#define USE_I2C	I2C2

typedef struct{
	int red;
	int green;
	int blue;
	int infrared;
}Rgb_t;
/*カラーセンサ*/
void I2cColorConfig(char mode);
void I2cGetColor(Rgb_t *rgb);
void I2cCommandSend(int address,char command, char data);
void analaysColor(char *str);
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx);
Rgb_t getColor(void);

#endif//CONFIG_I2C_H
