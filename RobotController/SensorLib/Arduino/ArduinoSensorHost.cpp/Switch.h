#include <Arduino.h>
#include <Thread.h>
#include <Bounce2.h>

class Switch : public Thread
{
  uint8_t inputPin;
  Bounce debouncer;
  bool currentValue;
  
  public:
    Switch(uint8_t _inputPin)
    {
      inputPin=_inputPin;
      debouncer=Bounce();
      pinMode(inputPin,INPUT_PULLUP);
      debouncer.attach(inputPin);
      debouncer.interval(15);
      setInterval(1000);
    }

    void processSwitch()
    {
      debouncer.update();
      currentValue=debouncer.read();      
    }

    bool getValue()
    {
      return currentValue;
    }

    void run()
    {
      processSwitch();
      runned();
    }
};

