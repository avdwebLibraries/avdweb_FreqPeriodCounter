/* FreqPeriodCounter
 * Version 28-5-2013
 * Copyright (C) 2011  Albert van Dalen http://www.avdweb.nl
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses

Release Notes
17-12-2011 timeFunctionPtr to select millis or micros instead of bool variable
17-12-2011 New function ready()
22-04-2012 poll() counts all transients instead of low-high transients
5-5-2013 if(transientCount >= 2) // the first 2 measurements are invalid
28-5-2013 measurements are valid from start, added synchronize()
7-2-2017 Versatile by omitting the input pin, added poll(bool _level) and added constructor

 
               <------------- period ------------>
                  pulseWidth
                 _____________                      ______________                     
               ||             ||                  ||              ||  
               ||             ||  pulseWidthLow   ||              ||              |
 ______________||             ||__________________||              ||______________|
          
 transientCount 1             2                   1               2               1
 transientTime ^              ^                   ^               ^
 level                1                 0                  1                0       
 debounceTime  <-->           <-->                <-->            <--> 
                                                                  <- elapsedTime ->
*/
          
#include "FreqPeriodCounter.h"

FreqPeriodCounter::FreqPeriodCounter(byte pin, unsigned long (*timeFunctionPtr)(), unsigned debounceTime):
pin(pin), debounceTime(debounceTime), timeFunctionPtr(timeFunctionPtr) 
{ synchronize();
}

FreqPeriodCounter::FreqPeriodCounter(unsigned long (*timeFunctionPtr)(), unsigned debounceTime):
debounceTime(debounceTime), timeFunctionPtr(timeFunctionPtr) 
{ synchronize();
}

bool FreqPeriodCounter::poll(bool _level) 
{ level = _level;
  time = timeFunctionPtr();
  elapsedTime = time - transientTime; 
  bool returnVal = false;
  if((level != lastLevel) && (elapsedTime > debounceTime)) // if transient
  { transientCount++;
    lastLevel = level;
    transientTime = time;   
    if(level == HIGH) pulseWidthLow = elapsedTime;
    else pulseWidth = elapsedTime;  
    if(transientCount >= 2) 
    { period = pulseWidth + pulseWidthLow;
      transientCount = 0; 
      readyVal = true;
      returnVal = true; // return true if a complete period is measured
    }
  }
  return returnVal;
}

bool FreqPeriodCounter::poll() // input pin
{ return poll(digitalRead(pin));
}

bool FreqPeriodCounter::ready()
{ bool returnVal = readyVal; 
  readyVal = false; // reset after read
  return returnVal;
}

unsigned long FreqPeriodCounter::hertz(unsigned int precision)
{ if (timeFunctionPtr == micros) return (unsigned long)precision*1000000/period;
  else return (unsigned long)precision*1000/period;
}

void FreqPeriodCounter::synchronize()
{ transientCount = -2; // skip first two invalid measurements
}



