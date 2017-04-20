#define TEENSY3X        // Use TEENSY 3X series
//#define TEENSYLC        // Use TeensyLC with FT5206_TOUCH
//#define DUE        // USE DUE
#define ___TEENSYES

#if defined(TEENSY3X)
  #include <core_pins.h>
  #define __MK20DX256__
  #undef ___DUESTUFF
  #undef __MKL26Z64__
#elif defined(TEENSYLC)
  #define __MKL26Z64__
#elif defined(DUE)
  #define ___DUESTUFF
#endif

#define DEBUG       // use debugging via serial port, if undef saves mem and cycles
