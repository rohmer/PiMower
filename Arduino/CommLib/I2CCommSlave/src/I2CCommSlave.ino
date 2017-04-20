#include <Arduino.h>

#include <Wire.h>
#include <EasyTransferI2C.h>
#include <string>
#include <vector>
#include <Thread.h>
#include <ThreadController.h>
#include <StaticThreadController.h>
#include "HCSR04.h"
#include "UI/BaseItems/WindowManager.h"
#include "Settings.h"

#define I2C_SLAVE_ADDRESS 9

enum eMessageType
{
  NOOP                = 0,
  DISTANCE_REQUEST    = 1,
  DISTANCE_SETUP      = 2,
  ACK                 = 3,
  ERR                 = 4,
  WARN                = 5,
  BATTERY_PCT         = 6
};

struct SONOR_STRUCT
{
  uint8_t triggerPin, echoPin;
  HCSR04* sensor;
  uint16_t rawDistance;
};

struct SEND_DATA_STRUCTURE
{
  eMessageType messageType;
  uint16_t intData[8];
  float floatData[8];
  String stringData[4];
};
struct RECEIVE_DATA_STRUCTURE
{
  eMessageType messageType;
  uint8_t intData[4];
  float floatData[4];
  String stringData[4];
};

RECEIVE_DATA_STRUCTURE rxData;
SEND_DATA_STRUCTURE txData;
EasyTransferI2C etReceive, etSend;
std::vector<SONOR_STRUCT> sonorSensors;
ThreadController threadManager=ThreadController();

void abort()
{
  while(1);
}

void setup()
{
  Wire.begin(I2C_SLAVE_ADDRESS);
  etReceive.begin(details(rxData), &Wire);
  etSend.begin(details(txData), &Wire);
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("I2CCommSlave Setup");
#endif
}

/*******************************************
 * Process Distance Request is as follows:
 * INPUT:
 * NONE
 * OUTPUT:
 * int[0] - Raw Distance for Sensor 0
 * ..
 * int[x] - Raw Distance for Sensor X
 */
void processDistanceRequest()
{
  if(sonorSensors.size()==0)
  {
      sendWarning("No Proximity Sensors defined!");
  #ifdef DEBUG
      Serial.println("No Proximity Sensors defined!");
  #endif
      return;
  }
  for(unsigned int i=0; i<=7; i++)
  {
    if(i<sonorSensors.size())
    {
      txData.intData[i]=sonorSensors[i].rawDistance;
    } else
    {
      txData.intData[i]=0;
    }
  }

  txData.messageType=eMessageType::DISTANCE_REQUEST;
}

/*******************************************
 * Distance Setup is as Follows:
 * INPUT
 * int[0] - Trigger Pin
 * int[1] - Echo Pin
 * OUTPUT
 * Potentially a warning
 *******************************************/
void processDistanceSetup(RECEIVE_DATA_STRUCTURE rxData)
{
#ifdef DEBUG
  Serial.println("Receieved Distance Setup Message");
#endif
  for(unsigned int i=0; i<sonorSensors.size(); i++)
  {
    if(sonorSensors[i].triggerPin==rxData.intData[0])
    {
      String msg="Trigger Pin: ";
      msg+=rxData.intData[0];
      msg+=" previously defined";

      sendWarning(msg);
#ifdef DEBUG
      Serial.println(msg);
#endif
      return;
    }

    if(sonorSensors[i].echoPin==rxData.intData[1])
    {
      String msg="Echo Pin: ";
      msg+=rxData.intData[0];
      msg+=" previously defined";

      sendWarning(msg);
#ifdef DEBUG
      Serial.println(msg);
#endif
      return;
    }
    if(sonorSensors.size()>=8)
    {
      String msg="Only 8 Sonor Sensors allowed, currently: ";
      msg+=sonorSensors.size();
      msg+=", defined.  This one will *NOT* be added";
      sendWarning(msg);
#ifdef DEBUG
      Serial.println(msg);
#endif
      return;
    }
    uint8_t triggerPin=rxData.intData[0];
    uint8_t echoPin=rxData.intData[1];

    if(triggerPin<1 || echoPin <1 || triggerPin>57 || echoPin>57)
    {
      String msg="Invalid trigger or echo pin, current values: Trigger(";
      msg+=triggerPin;
      msg+="), Echo(";
      msg+=echoPin;
      msg+=")";
      sendWarning(msg);
#ifdef DEBUG
      Serial.println(msg);
#endif
      return;
    }


    // Okay, at this point we have a legit sonor sensor setup
    // lets add it
    SONOR_STRUCT sonor;

    sonor.sensor=new HCSR04(triggerPin, echoPin);
    sonor.triggerPin=triggerPin;
    sonor.echoPin=echoPin;
    pinMode(triggerPin,OUTPUT);
    pinMode(echoPin,INPUT);
    sonorSensors.emplace(sonorSensors.end(),sonor);
    threadManager.add(sonor.sensor);
  }
}

void processMessage(RECEIVE_DATA_STRUCTURE rxData)
{
  if(rxData.messageType==eMessageType::DISTANCE_SETUP)
  {
    processDistanceSetup(rxData);
  }
  if(rxData.messageType==eMessageType::DISTANCE_REQUEST)
  {
    processDistanceRequest();
  }
}

void sendAck()
{
  txData={};
  txData.messageType=eMessageType::ACK;
  etSend.sendData(I2C_SLAVE_ADDRESS);
}

void sendWarning(String message)
{
  txData.messageType=eMessageType::WARN;
  txData.stringData[0]=message;
  txData.stringData[1]="";
  txData.stringData[2]="";
  txData.stringData[3]="";
  etSend.sendData(I2C_SLAVE_ADDRESS);
}

void loop()
{
  for(int i=0; i<5; i++)
  {
    etReceive.receiveData();
    if(rxData.messageType!=eMessageType::NOOP)
    {
      processMessage(rxData);
    }
  }
}
