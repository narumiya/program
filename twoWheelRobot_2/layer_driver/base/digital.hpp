#ifndef DIGITAL_H_INCLUDED
#define DIGITAL_H_INCLUDED


#define DIGITAL_IN 0
#define DIGITAL_OUT 1
#define DIGITAL_IN_PLUP 2
#define DIGITAL_IN_PLDN 3

#define DIGITAL_HIGH    1
#define DIGITAL_LOW     0
#define DIGITAL_TOGGLE -1
#include <stdio.h>

class Digital{
protected:
//***************override******************
    virtual int _digitalWrite()=0;
    virtual void _digitalWrite(int)=0;
    virtual int _digitalRead()=0;
    virtual int _setupDigitalIn()=0;
	virtual int _setupDigitalOut()=0;
	virtual int _setupDigitalInPullUp()=0;
	virtual int _setupDigitalInPullDown()=0;
//***************override******************

    enum{
        DIGITAL_MODE_NULL,
        DIGITAL_MODE_IN,
        DIGITAL_MODE_OUT,
        DIGITAL_MODE_PULLUP,
        DIGITAL_MODE_PULLDOWN,
    };
    int _digitalMode;
public:
	virtual int setupDigitalIn();
	virtual int setupDigitalOut();
	virtual int setupDigitalInPullUp();
	virtual int setupDigitalInPullDown();

	virtual void digitalWrite(int value);
	virtual int digitalRead();
	virtual void digitalHigh();
	virtual void digitalLow();
	virtual void digitalToggle();

    Digital& operator= (int value) {
        digitalWrite(value);
        return *this;
    }

    Digital& operator= (Digital& dig) {
        digitalWrite(dig.digitalRead());
        return *this;
    }

    operator int() {
        return digitalRead();
    }

};




#endif // DIGITAL_H_INCLUDED
