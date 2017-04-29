#include<iostream>
#include<math.h>
#include"point.h"

using namespace std;

point_3d::point_3d()
  {
    x = 0.0,y = 0.0,z = 0.0;
    cat = 0;
  }
void point_3d::set(float a, float b, float c)
  {
    x = a,y = b,z = c;
  }
void point_3d::set_cat(int K)
  {
    cat = K;
  }
int point_3d::get_cat()
  {
    return cat;
  }
float point_3d::get_x()
{
  return x;
}
float point_3d::get_y()
{
  return y;
}
float point_3d::get_z()
{
  return z;
}
void point_3d::print()
  {
    cout<<x<<' '<<y<<' '<<z<<endl;
  }
/*function to calculate eucledian distance between two points*/  
float distEuclid(point_3d A, point_3d B)
{
  return pow(A.get_x()-B.get_x(),2) + pow(A.get_y()-B.get_y(),2) + pow(A.get_z()-B.get_z(),2);
}

/*function to calculate difference between two points along a dimension*/
float sub(point_3d A,point_3d B,int dim)
{
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
  return (A.*fptr)() - (B.*fptr)();
}

/*Functions to find min and max along all the three dimensions*/
float getMinX(point_3d *pts, int PT_MAX)
{
  //int PT_MAX = sizeof(pts)/sizeof(point_3d);
  float min = pts[0].get_x();
  for(int i = 0; i<PT_MAX; i++)
    min = pts[i].get_x()<min?pts[i].get_x():min;
  return min;
}
float getMinY(point_3d *pts, int PT_MAX)
{
  //int PT_MAX = sizeof(pts)/sizeof(point_3d);
  float min = pts[0].get_y();
  for(int i = 0; i<PT_MAX; i++)
    min = pts[i].get_y()<min?pts[i].get_y():min;
  return min;
}
float getMinZ(point_3d *pts,int PT_MAX)
{
  //PT_MAX = sizeof(pts)/sizeof(point_3d);
  float min = pts[0].get_z();
  for(int i = 0; i<PT_MAX; i++)
    min = pts[i].get_z()<min?pts[i].get_z():min;
  return min;
}
float getMaxX(point_3d *pts,int PT_MAX)
{
  //PT_MAX = sizeof(pts)/sizeof(point_3d);
  float max = pts[0].get_x();
  for(int i = 0; i<PT_MAX; i++)
    max = pts[i].get_x()>max?pts[i].get_x():max;
  return max;
}
float getMaxY(point_3d *pts,int PT_MAX)
{
  //PT_MAX = sizeof(pts)/sizeof(point_3d);
  float max = pts[0].get_y();
  for(int i = 0; i<PT_MAX; i++)
    max = pts[i].get_y()>max?pts[i].get_y():max;
  return max;
}
float getMaxZ(point_3d *pts,int PT_MAX)
{
  //PT_MAX = sizeof(pts)/sizeof(point_3d);
  float max = pts[0].get_z();
  for(int i = 0; i<PT_MAX; i++)
    max = pts[i].get_z()>max?pts[i].get_z():max;
  return max;
}

void copyP(point_3d *A, point_3d *B)
{
  B->set(A->get_x(),A->get_y(),A->get_z());
}
