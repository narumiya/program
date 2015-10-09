#ifndef I2C_HPP
#define I2C_HPP

class I2c;
class I2cInterface{
public:
	int i2cSetup();
	int i2cWrite(char address,char data);
	virtual char i2cRead(char address);

	int i2cInterfaceSetup(I2c *i2c);
private:
	I2c *i2c;
};

class I2c{
public:
	virtual void write(char value,char address);
	virtual char read(char address);
	virtual int setup()=0;
};
#endif
