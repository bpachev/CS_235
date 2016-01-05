#include "Station.h"
#include "intStack.h"

bool Station:: addToStation(int car)
{
  if (curr_car >= 0) return false;
  if (car < 0) return false;
  if (carStack->isDup(car)&&carStack->size) return false;
  if (carQueue->isDup(car)&&carQueue->size) return false;
  if (carDeque->isDup(car)&&carDeque->size) return false;
  if (carORDeque->isDup(car)&&carORDeque->size) return false;
  if (carIRDeque->isDup(car)&&carIRDeque->size) return false;
  curr_car = car;
  return true;
}

int Station::showCurrentCar()
{
  return curr_car;
}

bool Station:: removeFromStation()
{
  if (curr_car >= 0) 
  {
    curr_car = -1;
    return true;
  }
  else return false;
}

bool Station:: addToStack() 
{
  if (curr_car < 0||carStack->full()) return false;
  carStack->push(curr_car);
  curr_car = -1;
  return true;
}

bool Station:: removeFromStack() 
{
  if (curr_car >= 0 || carStack->empty()) return false;
  curr_car = carStack->top();
  carStack->pop();
  return true;
}

int Station::showTopOfStack() 
{
  if (carStack->empty()) return -1;
  else return carStack->top();
}

int Station::showSizeOfStack() 
{
  return carStack->size;
}

bool Station:: addToQueue() 
{
  if (curr_car < 0 || carQueue->full()) return false;
  carQueue->add(curr_car);
  curr_car = -1;
  return true;
}

bool Station:: removeFromQueue() 
{
  if (curr_car >= 0 || carQueue->empty()) return false;
  curr_car = carQueue->first();
  carQueue->remove();
  return true;
}

int Station::showTopOfQueue() 
{
  if (carQueue->empty()) return -1;
  else return carQueue->first();
}

int Station::showSizeOfQueue() 
{
  return carQueue->size;
}

bool Station:: addToDequeLeft() 
{
  if (curr_car < 0 || carDeque->full()) return false;
  carDeque->push_front(curr_car);
  curr_car = -1;
  return true;
}

bool Station:: addToDequeRight() 
{
  if (curr_car < 0 || carDeque->full()) return false;
  carDeque->push_back(curr_car);
  curr_car = -1;
  return true;  
}

bool Station:: removeFromDequeLeft() 
{
  if (curr_car >= 0 || carDeque->empty()) return false;
  curr_car = carDeque->front();
  carDeque->pop_front();
  return true;
}

bool Station:: removeFromDequeRight() 
{
  if (curr_car >= 0 || carDeque->empty()) return false;
  curr_car = carDeque->back();
  carDeque->pop_back();
  return true;
}

int Station::showTopOfDequeLeft() 
{
  return carDeque->front();
}

int Station::showTopOfDequeRight() 
{
  return carDeque->back();
}

int Station::showSizeOfDeque() 
{
  return carDeque->size;
}

bool Station:: addToIRDequeLeft()
{
  if (curr_car < 0 || carIRDeque->full()) return false;
  carIRDeque->push_front(curr_car);
  curr_car = -1;
  return true;  
}

bool Station:: removeFromIRDequeLeft()
{
  if (curr_car >= 0 || carIRDeque->empty()) return false;
  curr_car = carIRDeque->front();
  carIRDeque->pop_front();
  return true;  
}

bool Station:: removeFromIRDequeRight()
{
  if (curr_car >= 0 || carIRDeque->empty()) return false;
  curr_car = carIRDeque->back();
  carIRDeque->pop_back();
  return true;
}

int Station::showTopOfIRDequeLeft()
{
  return carIRDeque->front();
}

int Station::showTopOfIRDequeRight()
{
  return carIRDeque->back();
}

int Station::showSizeOfIRDeque()
{
  return carIRDeque->size;
}

bool Station:: addToORDequeLeft()
{
  if (curr_car < 0 || carORDeque->full()) return false;
  carORDeque->push_front(curr_car);
  curr_car = -1;
  return true;  
}

bool Station:: addToORDequeRight()
{
  if (curr_car < 0 || carORDeque->full()) return false;
  carORDeque->push_back(curr_car);
  curr_car = -1;
  return true;
}

bool Station:: removeFromORDequeLeft()
{
  if (curr_car >= 0 || carORDeque->empty()) return false;
  curr_car = carORDeque->front();
  carORDeque->pop_front();
  return true;  
}

int Station::showTopOfORDequeLeft()
{
  return carORDeque->front();
}

int Station::showSizeOfORDeque()
{
  return carORDeque->size;
}