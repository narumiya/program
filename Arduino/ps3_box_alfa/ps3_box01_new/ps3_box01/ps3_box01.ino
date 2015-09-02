#include <SPI.h>
#include <PS3BT.h>
#include <usbhub.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#define ID 0x003
#define Serial_PC 0

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

double fPitch=0;
unsigned long fPitchTime=0;
double fRoll=0;
unsigned long fRollTime=0;

class Ta7291p{
private:
  int cw,ccw,pwm;
  double request;
public:
  Ta7291p(int cw,int ccw,int pwm){
    this->cw=cw;
    this->ccw=ccw;
    this->pwm=pwm;
    request=0.0;
  }
  int setup(){
    pinMode(cw,OUTPUT);
    pinMode(ccw,OUTPUT);
//    pinMode(pwm,OUTPUT);
    return 0;
  }
  void duty(double value){
    request=constrain(value,-1.0,1.0);
  }
  void cycle(){
    if(request>0){
      digitalWrite(cw ,HIGH);
      digitalWrite(ccw,LOW );
      analogWrite(pwm,255-(int)(255*abs(request)));
    }
    else if(request<0){
      digitalWrite(cw ,LOW );
      digitalWrite(ccw,HIGH);
      analogWrite(pwm,255-(int)(255*abs(request)));
    }
    else{
      digitalWrite(cw,HIGH);
      digitalWrite(ccw,HIGH);
      analogWrite(pwm,255-0);
    }
  }
};
/*
class RelayMD{
private:
  int cwPin,ccwPin;
  enum{
    RELAY_MD_NULL,
    RELAY_MD_CW,
    RELAY_MD_CCW
  };
  float requestDuty;
  int time;
  int frequency;
public:
  RelayMD(int cwPin,int ccwPin){
    this->cwPin=cwPin;
    this->ccwPin=ccwPin;
    requestDuty=0.0;
    time=millis();
    frequency=(int)(1000/100);
  }
  int setup(){
    pinMode(cwPin ,OUTPUT);
    pinMode(ccwPin,OUTPUT);
  }
  void cw(){
    duty(1.0);
  }
  void ccw(){
    duty(-1.0);
  }
  void stop(){
    duty(0.0);
  }
  void duty(float value){
    requestDuty=constrain(value,0.0,1.0);
  }
  void cycle(){
     if(millis()-time>frequency){
        time=millis();
     }
    if(requestDuty>0.0){
      if(requestDuty==1.0) digitalWrite(cwPin ,HIGH);
      else if(millis()-time>frequency*abs(requestDuty)) digitalWrite(cwPin ,LOW);
      else digitalWrite(cwPin ,HIGH);
      digitalWrite(ccwPin,LOW );
    }
    else if(requestDuty<0.0){
      digitalWrite(ccwPin,LOW);
      if(requestDuty==-1.0) digitalWrite(ccwPin ,HIGH);
      else if(millis()-time>frequency*abs(requestDuty))digitalWrite(ccwPin,LOW);
      else digitalWrite(ccwPin,HIGH);
    }
    else{
      digitalWrite(cwPin ,LOW);
      digitalWrite(ccwPin,LOW);
    }
  }
};
*/
class RelayMD{
private:
  int cwPin,ccwPin;
  enum{
    RELAY_MD_NULL,
    RELAY_MD_CW,
    RELAY_MD_CCW
  };
  float request;
public:
  RelayMD(int cwPin,int ccwPin){
    this->cwPin=cwPin;
    this->ccwPin=ccwPin;
    request=RELAY_MD_NULL;
  }
  int setup(){
    pinMode(cwPin ,OUTPUT);
    pinMode(ccwPin,OUTPUT);
  }
  void cw(){
    request=RELAY_MD_CW;
  }
  void ccw(){
    request=RELAY_MD_CCW;
  }
  void stop(){
    request=RELAY_MD_NULL;
  }
  void cycle(){
    if(request==RELAY_MD_CW){
      digitalWrite(cwPin ,HIGH);
      digitalWrite(ccwPin,LOW );
    }
    else if(request==RELAY_MD_CCW){
      digitalWrite(cwPin,LOW);
      digitalWrite(ccwPin,HIGH);
    }
    else{
      digitalWrite(cwPin ,LOW);
      digitalWrite(ccwPin,LOW);
    }
  }
};

class LedDisk{
private:
  int pin;
  int64_t cycleData;
  float cycleDutyData;
  int64_t time;
  int mode;
  enum{
    LEDDISK_MODE_NULL,
    LEDDISK_MODE_CYCLE,
    LEDDISK_MODE_PULSE
  };
public:
  LedDisk(int pin){
    this->pin=pin;
  }
  int setup(){
    pinMode(pin,OUTPUT);
  }
  void cycle(){
    if(mode==LEDDISK_MODE_NULL){
      digitalWrite(pin,LOW);
    }
    else if(mode==LEDDISK_MODE_CYCLE){
      if(cycleDutyData==1.0) digitalWrite(pin,HIGH);
      else if(cycleDutyData==0.0) digitalWrite(pin,LOW);
      else{
        if(millis()-time>cycleData){
          time=millis();
        }
        if(((float)(millis()-time)/(float)cycleData)>cycleDutyData) digitalWrite(pin,LOW);
        else digitalWrite(pin,HIGH);
      }
    }
    else if(mode==LEDDISK_MODE_PULSE){
      if(millis()>time){
        digitalWrite(pin,LOW);
        mode=LEDDISK_MODE_NULL;
      }
      else{
        digitalWrite(pin,HIGH);
      }
    }
  }
  void on(){
    cycleChange(1000);
    cycleDuty(1.0);
  }
  void off(){
    mode=LEDDISK_MODE_NULL;
  }
  void toggle(){
    if(mode==LEDDISK_MODE_NULL) on();
    else off();
  }
  void pulse(int millisArg){
    mode=LEDDISK_MODE_PULSE;
    time=millis()+millisArg;
  }
  void cycleChange(int millisArg){
    mode=LEDDISK_MODE_CYCLE;
    cycleData=millisArg;
  }
  void cycleDuty(float value){
    cycleDutyData=value;
  }
  void manual(){
    cycleChange(400);
    cycleDuty(0.5);
  }
  void automatic(){
    cycleChange(100);
    cycleDuty(0.5);
  }
  void wait(){
    cycleChange(1000);
    cycleDuty(0.5);
  }
  void safety(){
    cycleChange(500);
    cycleDuty(0.1);
  }
  void disconnect(){
    cycleChange(500);
    cycleDuty(0.8);
  }
};

//RelayMD motor0(7,8);
//RelayMD motor1(4,5);
//RelayMD motor2(A4,A5);
//RelayMD motor3(0,1);

RelayMD motor0(8,7);
RelayMD motor1(4,5);
RelayMD motor2(0,1);
RelayMD motor3(A5,A4);


Ta7291p motor4(A0,A2,3);
Ta7291p motor5(A1,A3,6);

LedDisk led(9);

void setup() {
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    while (1); //halt
  }

  motor0.setup();
  motor1.setup();
  motor2.setup();
  motor3.setup();

  motor4.setup();
  motor5.setup();

  led.setup();
  led.cycleChange(1000);
  led.cycleDuty(0.5);
}

int tireFlag=0;
float leftJoy=0.0,rightJoy=0.0;
int moveFlag=0;
int circleFlag=0;
int R2Flag=0;
long long int timer=0;

void loop() {

  Usb.Task();
  if (PS3.PS3Connected) {
    led.manual();
    
    if(millis()-timer>=5){
       timer=millis();
    tireFlag=1;
    
      leftJoy=(1 - ((float)PS3.getAnalogHat(LeftHatY)/127.5));
    rightJoy=(1 - ((float)PS3.getAnalogHat(RightHatY)/127.5));
    //足
    if(leftJoy>0.1){
       motor0.cw();
       tireFlag=0;
    }else if(leftJoy<-0.1){
       motor0.ccw();
       tireFlag=0;
    }else{
       motor0.stop();
    }
    
    if(rightJoy>0.1){
       motor1.cw();
       tireFlag=0;
    }else if(rightJoy<-0.1){
       motor1.ccw();
       tireFlag=0;
    }else{
       motor1.stop();
    }
    
    if(tireFlag){
      if(PS3.getAnalogButton(UP)>10){
        if(PS3.getAnalogButton(RIGHT)>10){
          motor0.cw();
          motor1.stop();
        }
        else if(PS3.getAnalogButton(LEFT)>10){
          motor0.stop();
          motor1.cw();
        }
        else{
          motor0.cw();
          motor1.cw();
        }
      }
      else if(PS3.getAnalogButton(DOWN)){
        if(PS3.getAnalogButton(RIGHT)>10){
          motor0.ccw();
          motor1.stop();
        }
        else if(PS3.getAnalogButton(LEFT)>10){
          motor0.stop();
          motor1.ccw();
        }
        else{
          motor0.ccw();
          motor1.ccw();
        }
      }
      else{
        if(PS3.getAnalogButton(RIGHT)>10){
          motor0.cw();
          motor1.ccw();
        }
        else if(PS3.getAnalogButton(LEFT)>10){
          motor0.ccw();
          motor1.cw();
        }
        else{
          motor0.stop();
          motor1.stop();
        }
      }
    }
  
   //アーム
   if((PS3.getAnalogButton(R1)>10 && PS3.getAnalogButton(L1)==0)
            || (PS3.getAnalogButton(TRIANGLE)>10 && PS3.getAnalogButton(CROSS)==0)){
      //上方向 
      motor3.cw();
   }else if((PS3.getAnalogButton(R1)==0 && PS3.getAnalogButton(L1)>10)
            || (PS3.getAnalogButton(TRIANGLE)==0 && PS3.getAnalogButton(CROSS)>10)){
      //下方向
      motor3.ccw();
   }else{
      motor3.stop();
   }
   
   //吸引スイッチ
   if(circleFlag==0){
        if(PS3.getAnalogButton(CIRCLE)>10){
           circleFlag=1;
            if(moveFlag==0){
               moveFlag=1;
            }else if(moveFlag==1){
               moveFlag=0;
            }   
         }
   }else if(circleFlag==1){
      if(PS3.getAnalogButton(CIRCLE)==0){
         circleFlag=0;
      }
   }
   
   if(R2Flag==0){
      if(PS3.getAnalogButton(R2)>10){
         R2Flag=1;
         if(moveFlag==0){
              moveFlag=1;
          }else if(moveFlag==1){
              moveFlag=0;
         } 
      }
    }else if(R2Flag==1){
       if(PS3.getAnalogButton(R2)==0){
         R2Flag=0;
        }
    }
       
      //吸引スイッチ
      if(moveFlag==1){
         motor2.cw();
         motor4.duty(-1);
      }else if(moveFlag==0){
         motor2.stop();
         motor4.duty(0);
      }
    }
     
    
    if (PS3.getButtonPress(PS) || PS3.getButtonPress(START)) {
       led.disconnect();
       motor0.stop();
       motor1.stop();
       motor2.stop();
       motor3.stop();
       motor4.duty(0);
       motor5.duty(0);
      PS3.disconnect();
      PS3.setLedOff();
    }
    
   if(fPitch!=PS3.getAngle(Pitch)){
     fPitch=PS3.getAngle(Pitch);
     fPitchTime=millis();
   }
   if(fRoll!=PS3.getAngle(Roll)){
     fRoll=PS3.getAngle(Roll);
     fRollTime=millis();
   }
   if(millis()-fPitchTime>500&&millis()-fRollTime>500){
     led.disconnect();
     motor0.stop();
     motor1.stop();
     motor2.stop();
     motor3.stop();
     motor4.duty(0);
     motor5.duty(0);
   }
  }
  else{
    led.disconnect();
    motor0.stop();
     motor1.stop();
     motor2.stop();
     motor3.stop();
     motor4.duty(0);
     motor5.duty(0);
  }
  
  motor0.cycle();
  motor1.cycle();
  motor2.cycle();
  motor3.cycle();

  motor4.cycle();
  motor5.cycle();

  led.cycle();
  //  digitalWrite(9,High);
}


