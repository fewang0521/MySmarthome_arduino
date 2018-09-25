/*********************************************************************
 **  Description:                                                    **
 **  This file is a sample code for your reference.                  **
 **                                                                  **
 **  Copyright (C) 2011 ElecFreaks Corp.                             **
 **  Created by ElecFreaks Robi.W /29 Sep 2011                      **
 **                                                                  **
 **  http://www.elecfreaks.com                                       **
 *********************************************************************/
#include <SoftwareSerial.h>
#include <SHT1x.h>
#include <Servo.h>

#define Pinout A0
#define servoPin 9
#define rxPin 2
#define txPin 3
#define LEDpin 13
#define dataPin  11
#define clockPin 10

//#define KEY   11   for HC-05 Bluetooth Module
SoftwareSerial mySerial(rxPin, txPin);
SHT1x sht1x(dataPin, clockPin);
Servo servo;
int angle = 0; // servo position in degrees = neutral
   
void setup()
{
   pinMode(rxPin, INPUT);
   pinMode(txPin, OUTPUT);
   mySerial.begin(9600);
   Serial.begin(9600);

   pinMode(LEDpin,OUTPUT);
   Serial.println("hi i'm port 7 blue arduino, slave role");
}
 
void loop()
{
  int i = 0;
  char someChar[32] = {0};
  // when characters arrive over the serial port...
  if(mySerial.available()) {
      do{
      someChar[i++] = mySerial.read();        // Note if use HC-06 there is not '/r/n' in the end.
      //As data trickles in from your serial port you are grabbing as much as you can, 
      //but then when it runs out (as it will after a few bytes because the processor 
      //is much faster than a 9600 baud device) you exit loop, which then restarts, 
      //and resets i to zero, and someChar to an empty array.So please be sure to keep this delay 
      delay(100); 
    }while (mySerial.available() > 0);
    Serial.println("Recive ----- "); 
    Serial.write(someChar);
    if (strncmp(someChar,"N",1)==0){
      mySerial.write("Turn on Success");
      digitalWrite(LEDpin,HIGH);
    }
    else if (strncmp(someChar,"F",1)==0){
      mySerial.write("Turn Off Success");
      digitalWrite(LEDpin,LOW);
    }
      else if (strncmp(someChar,"r",1)==0){
        if (analogRead(Pinout)>300){
          mySerial.write("Bon|");
          //below is for the debug, slave zigbee's serial port
          Serial.println(analogRead(Pinout));
        }
        else {
          mySerial.write("Bof|");
        }
        
      
    }
      else if (strncmp(someChar,"t",1)==0){
        float temp_c;
        char pChrBuffer[50];
        temp_c=sht1x.readTemperatureC();
        dtostrf(temp_c ,2 , 0, pChrBuffer);
          mySerial.write(pChrBuffer);
          mySerial.write("|");
          //below is for the debug, slave zigbee's serial port
          Serial.print("Temperature: ");
          Serial.print(temp_c, 1);  // Show one after the decimal point
          Serial.print("C / ");
        }
      else if (strncmp(someChar,"h",1)==0){
        float humidity;
        char pChrBuffer[50];
        humidity=sht1x.readHumidity();
        dtostrf(humidity ,2 , 0, pChrBuffer);
          mySerial.write(pChrBuffer);
          mySerial.write("|");
          //below is for the debug, slave zigbee's serial port
          Serial.print("F. Humidity: ");
          Serial.print(humidity);
          Serial.println("%");
        }        
        else if (strncmp(someChar,"S",1)==0){
            servo.attach(servoPin);
            for(angle = 50; angle < 100; angle++) 
              { 
                servo.write(angle); 
                delay(15); 
              } 
          servo.detach();
          mySerial.write("on");
          mySerial.write("|");
        } 
        else if (strncmp(someChar,"s",1)==0){
            servo.attach(servoPin);
            for(angle = 100; angle > 50; angle--) 
              { 
                servo.write(angle); 
                delay(15); 
              } 
          servo.detach(); 
          mySerial.write("off");
          mySerial.write("|");
        }  

    
    else {
      mySerial.write("fail to unknown command|");
    }
   
  }
    else if (Serial.available()) {
      do{
      someChar[i++] = Serial.read();        // Note if use HC-06 there is not '/r/n' in the end.
      //As data trickles in from your serial port you are grabbing as much as you can, 
      //but then when it runs out (as it will after a few bytes because the processor 
      //is much faster than a 9600 baud device) you exit loop, which then restarts, 
      //and resets i to zero, and someChar to an empty array.So please be sure to keep this delay 
      delay(100); 
    }while (Serial.available() > 0);
    Serial.println("Send ----- ");
    if (mySerial.println(someChar)){
    Serial.println(someChar);
    }
    }
}
 
  //while(mySerial.available()) 
     //Serial.print((char)mySerial.read());   



