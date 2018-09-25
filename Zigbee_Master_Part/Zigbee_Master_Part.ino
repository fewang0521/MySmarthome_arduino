/*********************************************************************
 **  Description:                                                    **
 **  This is generated based on ElecFreaks codes of xbee             **
 **                                                                  **
 **  Copyright (C) 2011 ElecFreaks Corp.                             **
 **  Created by ElecFreaks Robi.W /29 Sep 2011                      **
 **                                                                  **
 **  http://www.elecfreaks.com                                       **
 *********************************************************************/
#include <SoftwareSerial.h>

//define pin modes for tx, rx pins for Zigbee
#define rxPin 2
#define txPin 3
SoftwareSerial mySerial(rxPin, txPin);
//
   
void setup()
{
   //run Zigbee communication
   pinMode(rxPin, INPUT);
   pinMode(txPin, OUTPUT);
   mySerial.begin(9600);

   //setting serial communication between computer and arduino
   Serial.begin(9600);
 
   //Timer1.initialize(2000000);             // setting callback is 2s
   //Timer1.attachInterrupt(Callback); 
   //Serial.println("hi i'm port 5 geen arduino");
}
 
void loop()
{
  int i = 0;
  char someChar[32] = {0};
  //Recieve message by Zigbee
  if(mySerial.available()) {
      do{
      someChar[i++] = mySerial.read();
      delay(100); 
    }while (mySerial.available() > 0);
    //Serial.println("Recive ----- "); 
    Serial.write(someChar);
 
  }
  //Receieve message by serial communication
  //first get, message from web server by serial  
    else if (Serial.available()) {
      do{
      someChar[i++] = Serial.read(); 
      delay(100); 
    }while (Serial.available() > 0);
    //Serial.println("Send ----- ");
   //second, send the message by Zigbee
    mySerial.write(someChar);
    //Serial.write(someChar);
    }
}



