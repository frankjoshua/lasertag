#include "Arduino.h"
#include "spikesensor.h"

const int arraySize = 10;
int arrayPointer = 0;
int arrayData[] = {0,0,0,0,0,0,0,0,0,0};
int median = 0;
long startOfDip = 0;
float sensitivity = 0.05f; 
int maxDipMillis = 500;

int SpikeSensor::addReading(int reading, long readingTime){
  long timeSinceStart = readingTime - startOfDip;
  int dip = 0;
  //Check for max time
  if(timeSinceStart > maxDipMillis){
    //Too much time passed start looking for a new dip
    startOfDip = 0;
  }
  //Check for start of dip
  if(startOfDip == 0 && reading < median * (1.0f - sensitivity)){
    startOfDip = readingTime;
  } else if(startOfDip != 0 && reading > median * (1.0f + sensitivity)) {
    dip = timeSinceStart;
    startOfDip = 0;
  }

  //Save reading
  arrayData[arrayPointer] = reading;
  arrayPointer++;
  if(arrayPointer > arraySize){
    arrayPointer = 0;
  }
  //Bubble sort
  for(int j = 0; j < arraySize; j++){
    for(int i = 0; i < arraySize - 1; i++){
      if(arrayData[i] < arrayData[i + 1]){
        swapArrayElements(arrayData, i, i + 1);
      }
    }
  }
  //update median
  median = arrayData[arraySize / 2];

  return dip;
}

// function to swap two elements of an array
void SpikeSensor::swapArrayElements (int digits[], int index1, int index2) {
    int temp = 0;
    temp = digits[index1];
    digits[index1] = digits[index2];
    digits[index2] = temp;
}

