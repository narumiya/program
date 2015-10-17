#ifndef I2C_HPP
#define I2C_HPP

class I2c;
class I2cInterface{
public:
	int i2cSetup();
	int i2cWrite(char address,char *data);
	int i2cSetAddress(int address);
	virtual char i2cRead(char address)=0;
	virtual int i2cId(int id){return 0;};

	int i2cInterfaceSetup(I2c *i2c);
private:
	I2c *i2c;
};

class I2c{
public:
	virtual int setup()=0;
	virtual int write(char address,char *value)=0;
	int addInterface(I2cInterface *interfaceArg){return addInterface(*interfaceArg);};
	virtual int addInterface(I2cInterface &interfaceArg)=0;
	virtual int setAdress(int address)=0;
};
#endif
