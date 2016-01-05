#include "QS.h"
#include <iostream>
#define SWAP(a,b) temp = a; a = b; b = temp;

void recur_sort(int left, int right, QS* self);

void recur_sort(int left, int right, QS* self)
{
  if (right >= self->curr_size || left < 0 || right < 0 || left >= self->curr_size) return;
  int len = right - left;
  int temp;
  if (len <= 0 ) return;
  
  if (len == 1)
  {
    if(self->arr[left] > self->arr[right]) 
    {
      SWAP(self->arr[left],self->arr[right]);
      cout << "left " << self->arr[left] << " right " << self->arr[right] << endl;
    }
  }
  
  if (len == 2)
  {
    self->medianOfThree(left, right);
    return;
  }
  
  int middle = self->medianOfThree(left,right);
  int pindex = self->partition(left,right,middle);
  
 // cout << "pindex " << pindex << endl;
  if(pindex == -1) return;
  recur_sort(left,pindex,self);
  recur_sort(pindex+1,right,self);
  return;
}

//member functions

QS::~QS()
{
  free(arr);
}

void QS::sortAll()
{
  recur_sort(0,next_index-1,this);
}

int QS::medianOfThree(int left, int right)
{
  if (left >= right || right >= curr_size || left >= curr_size || right < 0 || left < 0) return -1;
  
  int middle = (left + right) / 2;
  int templ = arr[left];
  int tempm = arr[middle];
  int tempr = arr[right];
  
  arr[left] = (templ < tempm) ? ( (templ < tempr) ? templ : tempr ) : ( (tempm < tempr) ? tempm : tempr );
  arr[middle] = (templ < tempm) ? ( (templ > tempr) ? templ : ( (tempm < tempr) ? tempm : tempr ) ) : ( (tempm > tempr) ? tempm : ( (templ>tempr) ? tempr : templ) ); 
  arr[right] = (templ > tempm) ? ( (templ > tempr) ? templ : tempr ) : ( (tempm > tempr) ? tempm : tempr ); 
  
  return middle;
}

int QS::partition(int left, int right, int pivotIndex)
{  
  if (left >= right || right >= curr_size || left >= curr_size || right < 0 || left < 0 || pivotIndex >= right || pivotIndex <= left) return -1;
  //cout << "left " << left << " right " << right << " pivot " << arr[pivotIndex] << endl;

  int temp;
  int up = left + 1;
  int down  = right;
  int pivotValue = arr[pivotIndex];
  //cout << getArray() << endl;  
  SWAP(arr[left],arr[pivotIndex])
 // cout << getArray() << endl;
  
  while (up < down)
  {
    while (arr[up] < pivotValue)
    {
      up++;
      if (up == right) break;
    }
    
    while (arr[down] >= pivotValue)
    {
      down--;
      if (down == left) break;
    }
    
    if (up < down) 
    {
    //  cout << "Swapping " << arr[up] << " and " << arr[down] << endl; 
      SWAP(arr[up],arr[down]);
    }
   // cout << getArray() << endl;
    
  }
  SWAP(arr[left],arr[down]);
 // cout << "pvalue " << pivotValue << endl;
  //cout << getArray() << endl;
  return down;  
}

string QS::getArray()
{
  if (!next_index) return "";
  
  char buf1[20];
  snprintf(buf1, sizeof(buf1), "%d", arr[0]);
  string str = string(buf1);
  
  for (int i = 1; i < next_index; i++)
  {
    char buf2[20];
    snprintf(buf2, sizeof(buf2), "%d", arr[i]);
    str += ",";
    str += string(buf2);
  }
  
  return str;
}

int QS::getSize()
{
  return curr_size;
}

void QS::addToArray(int value)
{
  if (next_index == curr_size) return;
  
  arr[next_index++] = value;
}

bool QS::createArray(int size)
{
  if (size <= 0) return false;
  if (arr) free(arr);
  arr = (int*)malloc(size*sizeof(int));
  curr_size = size;
  next_index = 0;
  if (!arr) return false;
  else return true;
}

void QS::clear()
{
  free(arr);
  arr = 0;
  curr_size = 0;
  next_index = 0;
}
