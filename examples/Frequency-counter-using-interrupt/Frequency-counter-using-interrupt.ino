#include <FreqPeriodCounter.h>
#include <Albert.h>
#include <Streaming.h>
#include <TimerOne.h>

/* Note: connect d3 to d9 */

const byte counterPin = 3; // connect d3 to d9
const byte counterInterrupt = 1; // = d3
const byte PWMpin = 9; // PWM only d9 or d10
FreqPeriodCounter counter(counterPin, micros, 0);
void setup(void)
{ Serial.begin(9600);
  pinMode(PWMpin, OUTPUT); 
  Timer1.initialize();
  Timer1.pwm(PWMpin, 300, 70); // duty cycle [10 bit], period [us] <8388480
  attachInterrupt(counterInterrupt, counterISR, CHANGE);
}
void loop(void)
{ if(counter.ready())
  { Serial << endl << counter.period;
    //Serial << endl << counter.level, counter.period, counter.pulseWidth, counter.pulseWidthLow;
  }
}
void counterISR()
{ counter.poll();
}
