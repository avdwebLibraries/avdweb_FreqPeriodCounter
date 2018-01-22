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
  //Timer1.pwm(PWMpin, 300, 20000); // duty cycle [10 bit], period [us] <8388480
  Timer1.pwm(PWMpin, 300, 40); // duty cycle [10 bit], period [us] <8388480
}
void loop(void)
{ if(counter.poll()) Serial << endl << counter.period;
  //if(counter.poll()) Serial << endl << counter.level, counter.period, counter.pulseWidth, counter.pulseWidthLow;
  if(counter.elapsedTime > 50000) Serial << "No signal\n";
}
