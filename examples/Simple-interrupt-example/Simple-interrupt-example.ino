#include <FreqPeriodCounter.h>
  
const byte counterPin = 3;
const byte counterInterrupt = 1; 
FreqPeriodCounter counter(counterPin, micros);
  
void setup(void)
{ attachInterrupt(counterInterrupt, counterISR, CHANGE);
}
  
void loop(void)
{ int period;
  if(counter.ready()) period = counter.period;
}
  
void counterISR()
{ counter.poll();
}
