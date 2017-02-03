#include <StaticThreadController.h>
#include "HCSR04.h"
#include "Switch.h"
#include <Thread.h>
#include <ThreadController.h>

#include <Wire.h>
#include <stdarg.h>

unsigned int sensorInputPins[8];
unsigned int sensorTriggerPins[8];
uint8_t sensorInputs=0;
unsigned long distanceRaw[8];
unsigned long pingTime[8];
HCSR04 *sensors[8];
uint8_t switchInputPins[16];
uint8_t switchInputs=0;
Switch *switches[16];
bool switchVal[16];

ThreadController sensorThreadController=ThreadController();

void setup() {
  Serial.begin(9600);
  Wire.begin(0x44);
  Wire.onRequest(requestData);
  Wire.onReceive(receivedData);
  Wire.endTransmission();
  for(int a=0; a<16; a++)
  {
    switchInputPins[a]=0;
  }
}

void loop() 
{  
  sensorThreadController.run();
  for(int a=0; a<sensorInputs; a++)
  {    
    distanceRaw[a]=sensors[a]->getDuration();    
    pingTime[a]=sensors[a]->getTime();
  }  
  for(int a=0; a<switchInputs;a++)
  {
    switchVal[a]=switches[a]->getValue();
  }
  delay(50);
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

// Received data defines the pins we have sensors for
// Format: 
// P|UINT,UINT|UINT,UINT...
// Where:
//  P - defines a proximity sensor which sends:
//    UINT Pairs, first is triggerPin, second is echoPin for each 
//    proximity sensor
void receivedData(int length)
{  
   int a=0;
   char b[256];   
   String msg;
   while(Wire.available())
   {
    msg+=(char)Wire.read();
   }
 
   // We received something like: 
   // P|12,13   <- 12 trigged, 13 sensor pin
   // or
   // P|12,13,14 <- 12 trigger, 13 & 14 sensor pins

   // Need to parse it
   if(msg.substring(0,1)=="P")
   {
    parseProximityMsg(msg);
   }
   if(msg.substring(0,1)=="S")
   {
    parseSwitchMsg(msg);
   }
      
   
}

// SWITCH MSG FORMAT:
// S10,11,12,13,14 
// Where:
// S defines switch formal
// numbers are the switch toggle pins
void parseSwitchMsg(String msgPayload)
{
  for(int a=0; a<sensorThreadController.size(false); a++)
  {
    if(sensorThreadController.get(a)->ThreadName=="Switch")
    {
      sensorThreadController.remove(a);
    }
  }
  for(int a=0; a<16; a++)
  {
    if(switches[a]!=NULL)
    {
      delete(switches[a]);
    }
  }
  String msg;  
  int tPin;
  String s="";
  if(msgPayload.indexOf(",",1))
  {
    s=getValue(msgPayload.substring(1),',',0);
  } else
  {
    s=msgPayload.substring(1);
  }
  int switchNum=0;
  int counter=0;
  while(s.length()>0)
  {
    int pinVal=s.toInt();
    if(pinVal>0)
    {
      bool exists=false;
      for(int a=0; a<switchInputs; a++)
      {
        if(switchInputPins[a]==pinVal)
        {
          exists=true;
        }
      }
      if(!exists)
      {
        switchInputPins[switchNum]=pinVal;        
        switches[switchNum]=new Switch(pinVal);
        switches[switchNum]->ThreadName="Switch";
        sensorThreadController.add(switches[switchNum]);              
        switchInputs++;
      }
    }
    counter++;
    s=getValue(msgPayload.substring(1),',',1);
  }
  
}

void parseProximityMsg(String msgPayload)
{  
  for(int a=0; a<sensorThreadController.size(false); a++)
  {
    if(sensorThreadController.get(a)->ThreadName=="HCSR04")
    {
      sensorThreadController.remove(a);
    }
  }
  for(int a=0; a<7; a++)
  {
    if(sensors[a]!=NULL)
    {
      delete(sensors[a]);
      distanceRaw[a]=0;
    }
  }  
  int tPin;
  //int inputPins[8]= { -1, -1, -1, -1, -1, -1, -1, -1 };
    
  int counter=0;
  Serial.println("MsgPayload: "+msgPayload);
  String s=getValue(msgPayload.substring(1),'|',0);  
  
  int sensorNum=0;  
  while(s.length()>0)
  {     
    Serial.println("S: "+s);
    String sVal=getValue(s,',',0);
    String msg="";   
    int triggerPin=sVal.toInt();
    sVal=getValue(s,',',1);
    int echoPin=sVal.toInt();  
    bool found=false;
    for(int b=0; b<8; b++)
    {
      if(sensorInputPins[b]==echoPin)
        found=true;
    }

    if(!found)
    {      
      if(echoPin>0 && triggerPin>0)    
      {    
        sensorTriggerPins[sensorNum]=triggerPin;
        sensorInputPins[sensorNum]=echoPin;
        pinMode(sensorTriggerPins[sensorNum],OUTPUT);
        pinMode(sensorInputPins[sensorNum],INPUT);
        sensors[sensorNum]=new HCSR04(sensorTriggerPins[sensorNum],sensorInputPins[sensorNum]);
        sensors[sensorNum]->setInterval(250);
        sensors[sensorNum]->ThreadName="HCSR04";
        sensorThreadController.add(sensors[sensorNum]);      
         msg="Echo pin: ";
        msg+=echoPin;
        msg+=" defined";
        Serial.println(msg);
        sensorInputs++;
        sensorNum++;    
      }
    }
    counter++;    
    s=getValue(msgPayload,'|',counter);   
    Serial.println("S2: "+s);
  }    
  
}

bool testSensor(uint8_t triggerPin, uint8_t echoPin)
{
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);

  long startTime=micros();

  while(digitalRead(echoPin)==LOW)
  {    
    if(micros() - startTime > 10000)
    {
      return false;
      break;
    }
  }
  return true;
}


void requestData()
{
  // Data is sent back: PECHOPin,rawDist1,pingTime|ECHOPin,rawDist2,pingTime...~BPin,0/1|Pin,0/1\n
  // ex: P13,5555,1111111|14,6666,5555555~B15,0|16,1
  String buffer="";
  if(sensorInputs>0)
  {
    buffer+="P";
    for(int a=0; a<sensorInputs; a++)
    {
      if(sensorInputPins[a]>0)
      {
        if(a!=0)
        {
          buffer+="|";
        } 
          
        buffer+=sensorInputPins[a];
        buffer+=",";
        if(distanceRaw[a]==0 || distanceRaw[a]>20000)
        {
          delay(50);
          distanceRaw[a]=sensors[a]->getDuration();    
        }
        buffer+=distanceRaw[a];    
        buffer+=",";
        buffer+=pingTime[a];
      }
    }
  } 
  if(switchInputs>0)
  {
    if(buffer.length()>0)
      buffer+="~";
    buffer+="B";
    for(int a=0; a<switchInputs; a++)
    {
      if(a>0)
      {
        buffer+="|";
      }
      buffer+=switchInputPins[a];
      buffer+=",";
      if(switchVal[a])
      {
        buffer+="1";
      } else
      {
        buffer+="0";
      }
    }
  } 
  buffer+='\n';
  Serial.println(buffer);
  Wire.write(buffer.c_str()); 
}

