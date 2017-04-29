#include<iostream>
#include"priority_queue.h"

using namespace std;

minHeap::minHeap(int cap)
  {
    size = 0;
    capacity = cap;
    first = new float[cap];
    second = new point_3d[cap];
    third = new int[cap];
    for(int i = 0;i<cap;i++)
      third[i] = -2;
  }
  void minHeap::insert(float dist, point_3d pt, int ind)
  {
    //cout<<"inserting "<<dist<<' ';
    //pt.print();
    if(size == capacity-1)
      return;
    first[size] = dist;
    second[size].set(pt.get_x(),pt.get_y(),pt.get_z());
    third[size++] = ind;
    heapUp(size-1);
    //cout<<"insertion done"<<endl;
  }
  float minHeap::pop()
  {
    if(size == 0)
      return 0.0;
    float max = first[0];
    first[0] = first[--size];
    second[0].set(second[size].get_x(),second[size].get_y(),second[size].get_z());
    minHeapify(0);
    return max;
  }
  void minHeap::minHeapify(int ind)
  {
    if(size == 0 || size == 1)
      return;
    int left = ind*2+1;
    int right = ind*2+2;
    
    int smallest = ind;
    if(left<size && first[left]<first[ind])
      smallest = left;
    if(right<size && first[right]<first[smallest])
      smallest = right;
    if(smallest != ind)
    {
      swap(ind,smallest);
      minHeapify(smallest);
    }
  }
  void minHeap::heapUp(int ind)
  {
    if(size == 0 || ind == 0 || ind > size-1)
      return;
    int temp = ind;
    int parent = (ind - 1)/2;
    while(first[parent]>first[temp])
    {
      swap(parent,temp);
      temp = parent;
      parent = (parent - 1)/2;
    }
  }
  void minHeap::swap(int i, int j)
  {
    float a1,a2,b1,b2,c1,c2;
    a1 = second[i].get_x();
    a2 = second[j].get_x();
    b1 = second[i].get_y();
    b2 = second[j].get_y();
    c1 = second[i].get_z();
    c2 = second[j].get_z();
    second[i].set(a2,b2,c2);
    second[j].set(a1,b1,c1);
    float temp = first[i];
    first[i] = first[j];
    first[j] = temp;
    int temp2 = third[i];
    third[i] = third[j];
    third[j] = temp2;
  }