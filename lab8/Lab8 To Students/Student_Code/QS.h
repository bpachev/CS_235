#include "QSInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <string.h>

class QS : public QSInterface
{
public:
  QS() : curr_size(0), next_index(0), arr(0)
  {}
  
  ~QS();
  void sortAll();
  int medianOfThree(int left, int right);
  int partition(int left, int right, int pivotIndex);
  string getArray();
  int getSize();
  void addToArray(int value);
  bool createArray(int size);
  void clear();
//private:
  int* arr;
  int curr_size;
  int next_index;
};