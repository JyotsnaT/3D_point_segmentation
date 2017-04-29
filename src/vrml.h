#include<fstream>
//#include"point.h"
#include "heapsort.h"

using namespace std;
void writeVrml(string filename,point_3d *ptsArr, int N)
{
  
  ofstream of;
  of.open(filename.c_str());
  of<<"#VRML V1.0 ascii"<<endl;
  of<<"\nSeparator { \n  MaterialBinding { \n         value PER_VERTEX_INDEXED \n  }";
  of<<"\n\n  Material { \n    diffuseColor [ \n";
  
  for(int i = 0;i<N-1;i++)
    of<<"      0 1 0,\n";
  of<<"      0 1 0]\n  }\n\n";
  of<<"  Coordinate3 {\n    point [\n";
  for(int i = 0;i<N-1;i++)
    of<<"      "<<ptsArr[i].get_x()<<' '<<ptsArr[i].get_y()<<' '<<ptsArr[i].get_z()<<",\n";
  of<<"      "<<ptsArr[N-1].get_x()<<' '<<ptsArr[N-1].get_y()<<' '<<ptsArr[N-1].get_z()<<"]\n}\n\n";
  of<<"  PointSet { "<<endl;
  of<<"    startIndex 0"<<endl; 
  of<<"    numPoints "<<N<<"\n  }\n}";
}