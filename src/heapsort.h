#include<iostream>
//#include"point.h"
#include "kdtree.h"
using namespace std;

void heapsort(point_3d *pts, int n, int dim);
void heapify(point_3d *pts, int n, int i, int dim);
void swap(point_3d *pts, int i, int j);
int binary_search(point_3d *arr, float key, int beg, int end, int dim);

void heapsort(point_3d *pts, int n, int dim)
{
  for(int i = n/2-1; i>=0;i--)
    heapify(pts,n,i,dim);
  for (int i=n-1; i>=0; i--)
    {
        swap(pts,0,i);
	heapify(pts,i,0,dim);
    }
}
void heapify(point_3d *pts, int n, int i, int dim)
{
  int largest = i;
  int left = i*2+1;
  int right = i*2+2;
  //cout<<"heapify "<<i<<endl;
  float(point_3d::*fptr)();
  switch(dim)
  {
    case 0 : fptr = &point_3d::get_x;
	     break;
    case 1 : fptr = &point_3d::get_y;
	     break;
    case 2 : fptr = &point_3d::get_z;
	     break;
  }
  if (left < n && (pts[left].*fptr)() > (pts[largest].*fptr)())
        largest = left;
 
  if (right < n && (pts[right].*fptr)() > (pts[largest].*fptr)())
        largest = right;
  if(largest != i)
  {
    swap(pts,largest,i);
    heapify(pts,n,largest,dim);
  }
}
void swap(point_3d *pts, int i, int j)
{
  float a1,a2,b1,b2,c1,c2;
  a1 = pts[i].get_x();
  a2 = pts[j].get_x();
  b1 = pts[i].get_y();
  b2 = pts[j].get_y();
  c1 = pts[i].get_z();
  c2 = pts[j].get_z();
  pts[i].set(a2,b2,c2);
  pts[j].set(a1,b1,c1);
  //cout<<"swap done"<<endl;
}

int binary_search(point_3d *arr, float key, int beg, int end, int dim)
{
  int mid = (beg + end)/2;
    float(point_3d::*fptr)();
  switch(dim)
  {
    case 0 : fptr = &point_3d::get_x;
	     break;
    case 1 : fptr = &point_3d::get_y;
	     break;
    case 2 : fptr = &point_3d::get_z;
	     break;
  }
  if((arr[mid].*fptr)() == key)
    return mid;
  if((arr[mid].*fptr)() > key)
    return binary_search(arr,key,beg,mid-1,dim);
  else
    return binary_search(arr,key,mid+1,end,dim);
}
