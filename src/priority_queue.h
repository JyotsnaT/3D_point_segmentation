#include "point.h"

class minHeap
{
  public:
  float *first;
  point_3d *second;
  int *third; 
  int size, capacity;

  minHeap(int cap);
  void insert(float dist, point_3d pt, int ind);
  float pop();
  void minHeapify(int ind);
  void heapUp(int ind);
  void swap(int i, int j);

};