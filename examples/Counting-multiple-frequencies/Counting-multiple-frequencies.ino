#include <FreqPeriodCounter.h>
  
FreqPeriodCounter counter1(3, micros, 0);
FreqPeriodCounter counter2(4, micros, 0);
FreqPeriodCounter counter3(5, micros, 0);
  
void setup(void)
{
}
  
void loop(void)
{ counter1.poll();
  counter2.poll();
  counter3.poll();
  float f1 = (float)1 / counter1.period;
  float f2 = (float)1 / counter2.period; 
  float f3 = (float)1 / counter3.period; 
}
