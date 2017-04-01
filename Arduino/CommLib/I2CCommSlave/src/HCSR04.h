#include <StaticThreadController.h>
#include <Thread.h>
#include <ThreadController.h>
#include <NewPing.h>

class HCSR04 : public Thread
{
  private:
    int triggerPin, echoPin;
    unsigned long duration, pingTime;
    NewPing *sonar;
    
  public:
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
