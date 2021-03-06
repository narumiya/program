#ifndef AQM0802_HPP
#define AQM0802_HPP

#include "i2c.hpp"

class Aqm0802:public I2cInterface{
private:
	char address;
public:
	Aqm0802(I2c &i2cPin);
	int setup();
	void sendString(const char *data);
	void sendChar(const char data);
	void setCursor(const char x,const char y);
	void clear();
	/*readしないので必要なし*/
	void i2cRead(char *data){};
};

#endif
