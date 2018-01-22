# avdweb_FreqPeriodCounter
Smart library with comprehensive functions for counting (multiple) frequencies and period-times. For Arduino Uno and Zero.
http://www.avdweb.nl/arduino/libraries/frequency-period-counter.html

FreqPeriodCounter facts
- The frequency counter can be used in two ways:
Interrupt triggered by the input signal.
Polled regularly in a loop.
The FreqPeriodCounter is equipped with synchronization so that also the first measurements are valid.
The maximum frequency with polling is approximately 25kHz.
The measurement can be done in milli seconds or micro seconds. The constructor has a function as argument, here we pass the required function: millis or micros.
We can take a debounce time of about 10ms if the frequency comes from a mechanically switch: counter(counterPin, micros, 10);.
