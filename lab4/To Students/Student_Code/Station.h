#pragma once
#include "StationInterface.h"
#include "StationInterfaceExtra.h"
#include "intStack.h"
#include "intQueue.h"
#include "intDeque.h"
#include "intIRDeque.h"
#include "intORDeque.h"

#define MAX_CAPACITY 5


class Station : public StationInterfaceExtra
{
public:
  Station(): curr_car(-1), carStack(new intStack(MAX_CAPACITY)), carQueue(new intQueue(MAX_CAPACITY)), carDeque(new intDeque(MAX_CAPACITY)), carIRDeque(new intIRDeque(MAX_CAPACITY)), carORDeque(new intORDeque(MAX_CAPACITY)) 
  {}
  bool addToStation(int car);
  int showCurrentCar();
  bool removeFromStation();
  bool addToStack();
  bool removeFromStack();
  int showTopOfStack();
  int showSizeOfStack();
  bool addToQueue();
  bool removeFromQueue();
  int showTopOfQueue();
  int showSizeOfQueue();
  bool addToDequeLeft();
  bool addToDequeRight();
  bool removeFromDequeLeft();
  bool removeFromDequeRight();
  int showTopOfDequeLeft();
  int showTopOfDequeRight();
  int showSizeOfDeque();
  bool addToIRDequeLeft() ;
  bool removeFromIRDequeLeft() ;
  bool removeFromIRDequeRight() ;
  int showTopOfIRDequeLeft() ;
  int showTopOfIRDequeRight() ;
  int showSizeOfIRDeque() ;
  bool addToORDequeLeft() ;
  bool addToORDequeRight() ;
  bool removeFromORDequeLeft() ;
  int showTopOfORDequeLeft() ;
  int showSizeOfORDeque() ;

 private:
  int curr_car;
  intStack* carStack;
  intQueue* carQueue;
  intDeque* carDeque;
  intIRDeque* carIRDeque;
  intORDeque* carORDeque;
};