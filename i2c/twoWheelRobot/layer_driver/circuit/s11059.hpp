#ifndef S11059_HPP
#define S11059_HPP

#include "i2c.hpp"

class S11059:public I2cInterface{
private:
	unsigned int time;
	char readAddress;
	char sendAddress;
	int red;
	int green;
	int blue;
	int infrared;
	int mode;
public:
	S11059(I2c &i2cPin);
	int setup();
	int getRed(){return red;};
	int getGreen(){return green;};
	int getBlue(){return blue;};
	int getInfrared(){return infrared;};
	void setMode(int value){mode=value;};
	void i2cRead(char *data);
	int i2cAddress(int address){
		return address==readAddress;
	}
	void cycle();
	enum{
		LOW,
		HIGH
	};
};

#endif
