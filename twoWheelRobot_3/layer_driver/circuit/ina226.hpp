#ifndef INA226_HPP
#define INA226_HPP

#include "i2c.hpp"

class Ina226:public I2cInterface{
private:
	int flag;
	unsigned long long int time;
	char readAddress;
	char sendAddress;
	float voltage;
	float current;
public:
	Ina226(I2c &i2cPin);
	int setup();
	float getVoltage(){return voltage/1000.0;};
	float getCurrent(){return current/1000.0;};
	int i2cAddress(int address);
	void i2cRead(unsigned char *data);
	void i2cReStartSend(char data);
	void cycle();
};

#endif
