#include <FreqPeriodCounter.h>
  
const byte counterPin = 3;
FreqPeriodCounter counter(counterPin, micros);
  
void setup(void)
{
}
  
void loop(void)
{ counter.poll();
  float f = (float)1 / counter.period;
}
