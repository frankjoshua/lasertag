#ifndef spikesensor_h
#define spikesensor_h

#include "Arduino.h"

class SpikeSensor {

  public:
    int addReading(int reading, long readingTime);

  private:
    void swapArrayElements (int digits[], int index1, int index2);
    
};

#endif
