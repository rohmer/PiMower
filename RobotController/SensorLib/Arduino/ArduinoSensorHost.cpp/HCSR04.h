#include <Arduino.h>
#include <Thread.h>
#include <NewPing.h>

class HCSR04 : public Thread
{
  private:
    int triggerPin, echoPin;
    unsigned long duration, pingTime;
    NewPing *sonar;
    /*void sendCommand()
    {
      digitalWrite(triggerPin,LOW);
      delayMicroseconds(2);
      digitalWrite(triggerPin,HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin,LOW);
    }

    bool awaitResponse()
    {
      long startTime=micros();

      while(digitalRead(echoPin)==LOW && micros() - startTime<1000)
      {
        if(micros() - startTime > 1000)
        {
          return false;
          break;
        }
      }
      return true;
    }
    */
    public:
      /*String getType()
      {
        return "HCSR04";
      }
      */
      ~HCSR04()
      {
        if(sonar)
          delete(sonar);
      }
      HCSR04(int _triggerPin, int _echoPin)
      {
        sonar=new NewPing(_triggerPin, _echoPin, 400);
        triggerPin=_triggerPin;
        echoPin=_echoPin;

        setInterval(250);
      }

      long getDuration()
      {
        return duration;
      }

      long getTime()
      {
        return pingTime;
      }
      
      long readDuration()
      {
        duration=sonar->ping_median(5);
        pingTime=micros();
        return duration;
      }

      // Thread implementation
      void run()
      {
        readDuration();
        runned();
      }
};


