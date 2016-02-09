/*
An Arduino code example for interfacing with the HMC5883

by: Jordan McConnell
SparkFun Electronics
created on: 6/30/11
license: OSHW 1.0, http://freedomdefined.org/OSHW

Analog input 4 I2C SDA
Analog input 5 I2C SCL
*/

//Modified by Owen Duffy 2013/12/10 for Arduino 1.05 compatibility

#include <Wire.h> //I2C Arduino Library
#include "axis.h"

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

Axis xaxis('x');
Axis yaxis('y');
Axis zaxis('z');

void setup(){
//Initialize Serial and I2C communications
    Serial.begin(115200);
    Wire.begin();
    
    //Put the HMC5883 IC into the correct operating mode
    Wire.beginTransmission(address); //open communication with HMC5883
    Wire.write(0x00); //select CRA register
//    Wire.write(0x78); //8-average, 15 Hz default, normal measurement
    Wire.write(0x18); //1-average, 75 Hz default, normal measurement
    Wire.endTransmission();

    Wire.beginTransmission(address); //open communication with HMC5883
    Wire.write(0x01); //select CRB register
    Wire.write(0xA0); //Gain=5, or any other desired gain
    Wire.endTransmission();

    Wire.beginTransmission(address); //open communication with HMC5883
    Wire.write(0x02); //select mode register
    Wire.write(0x00); //continuous measurement mode
    Wire.endTransmission();

    delay(6);

    //pinMode(pin, INPUT);
    //attachInterrupt(digitalPinToInterrupt(pin), readdata, CHANGE);    
}

void loop(){

    int x,y,z; //triple axis data

    //Tell the HMC5883 where to begin reading data
    Wire.beginTransmission(address);
    Wire.write(0x03); //select register 3, X MSB register
    Wire.endTransmission();
    
    
    //Read data from each axis, 2 registers per axis
    Wire.requestFrom(address, 6);
    if(6<=Wire.available()){
        x = Wire.read()<<8; //X msb
        x |= Wire.read(); //X lsb
        z = Wire.read()<<8; //Z msb
        z |= Wire.read(); //Z lsb
        y = Wire.read()<<8; //Y msb
        y |= Wire.read(); //Y lsb
/*
        Serial.print("x|"); Serial.print(x - xaxis.prevValue());
        Serial.print("|y|"); Serial.print(y - yaxis.prevValue());
        Serial.print("|z|"); Serial.println(z - zaxis.prevValue());
  */
/*        Serial.print("x|"); Serial.print(x);
        Serial.print("|y|"); Serial.print(y);
        Serial.print("|z|"); Serial.println(z);
  */
        xaxis.Set(x);
        yaxis.Set(y);
        zaxis.Set(z);
            
        delay(14);
    }


}

void readdata(){

  Serial.println("readdata");
}


