#include "i2c.hpp"

int I2cInterface::i2cInterfaceSetup(I2c *i2c){
	this->i2c=i2c;
	return 0;
}

int I2cInterface::i2cSetup(){
	return i2c->setup();
}
int I2cInterface::i2cWrite(char address,char *data){
	return i2c->write(address,data);
}

int I2cInterface::i2cSetAddress(int address){
	return i2c->setAdress(address);
}
