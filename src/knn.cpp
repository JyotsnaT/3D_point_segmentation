#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<math.h>
//#include"point.h"
//#include "kdtree.h"
//#include "vrml.h"
#include "imgio.h"
//#include "graph.h"

#define PT_MAX 100000

using namespace std;

int main(int argc, char *argv[])
{
  point_3d pts[PT_MAX];
  int k = 0;
  
  string outputdirectory = "../result/";
  string inputdirectory = "../original/";
  string ext = "xyz_label_conf";
  //string segment = "oakland_part2_ah";
  string segment = argv[1];
  
  ifstream img;
  string inp_file = inputdirectory + segment + "." +  ext;
  img.open(inp_file.c_str());
  string line;
  stringstream ss;
  while(getline(img,line))
  {
    if(line[0] != '#')
    {
      ss<<line;
      float a,b,c;
      int cl;
      ss>>a>>b>>c>>cl;
      ss.str( std::string() );
      ss.clear();
      pts[k].set(a,b,c);
      pts[k].set_cat(cl);
      k++;
    }
  }
  cout<<"file read"<<endl;
  /*for(int i = 0;i<PT_MAX;i++)
    pts[i].print();
  */
  
  /*
   * create a KD tree from all the points to find nearest neighbors
   */
  
  kdtree Tree;
  for(int i = 0;i<PT_MAX;i++)
     Tree.insert(pts[i],i);
 
  /*
   *Create a nearest neighbor graph on which min cut can be performed 
   */
 Graph G(PT_MAX,1, pts);
  //cout<<"Graph created"<<endl;
  
  int kn = 10;
  minHeap PQ1(1000);
  float thresh = 0.01;
  bool visited[PT_MAX];
  memset(visited,false,PT_MAX);
  
  visited[0] = true;
  Tree.knearest(G.source,Tree.root,1000,&PQ1);
  //int i = 0;
  //cout<<"nearest neighbors for "<<0<<endl;
  listNode *head, *pHead, *tail;
  int all = 0;
  head = NULL, tail = NULL;
  for(int i = 0;i<1000;i++)
  {
    //cout<<PQ1.third[i]<<endl;
    if(PQ1.third[i] != -2 && !visited[PQ1.third[i]])
    {
      listNode *newN = new listNode(PQ1.third[i],PQ1.first[i]);
      visited[PQ1.third[i]] = true;
      all++;
      if(!head)
      	head = newN, tail = newN, pHead = newN;
      tail->next = newN;
      tail =newN;
      //cout<<PQ1.third[i]<<endl;
      G.insert(-1,PQ1.third[i],1/PQ1.first[i]);
    }
  }
  while(head && tail)
  {
    minHeap PQ(kn);
    listNode *temp = head;
    head = head->next;
    Tree.knearest(pts[temp->pt],Tree.root,kn,&PQ);
    cout<<"nearest neighbors for "<<temp->pt<<endl;
    //delete temp;
    for(int i = 0;i<kn;i++)
    {
      if(PQ.third[i] != -2 && !visited[PQ.third[i]] && PQ1.first[i]<thresh)
      {
	listNode *newN = new listNode(PQ.third[i],PQ.first[i]);
	visited[PQ.third[i]] = true;
	all++;
	if(!head)
	  head = newN, tail = newN;
	tail->next = newN;
	tail = newN;
	G.insert(temp->pt,PQ.third[i],1/PQ.first[i]);
      }
    }
  }
  
  //G.print();
 // delete visited;
  
  /*bool *foreGround_pts = mincut(G,0,pts); 
  
  int finalPts = 0;
  for(int i = 0; i<PT_MAX; i++)
  {
    //cout<<foreGround_pts[i]<<'\t';
    if(foreGround_pts[i])
      finalPts++;
  }
  cout<<finalPts<<endl;
  point_3d ptsArr[finalPts];
  
  int s = 0;
  for(int i = 0; i<PT_MAX; i++)
  {
    //cout<<"here "<<foreGround_pts[i]<<endl;
    if(foreGround_pts[i])
    {
      //cout<<"yay!"<<endl;
      ptsArr[s++].set(pts[i].get_x(),pts[i].get_y(),pts[i].get_z());
      pts[i].print();
    }
  } */  

  /*
   * VRML File writing
   */ 
  cout<<"Total "<<all<<" points"<<endl;
  point_3d ptsArr[all];
  int c = 0;
  listNode *temp = pHead;
  while(temp)
  {
    copyP(&pts[temp->pt],&ptsArr[c++]);
    temp = temp->next;
  }
  
  string file = outputdirectory + segment + ".wrl";
  writeVrml(file,ptsArr,all);
  
  /*
   * Writing file in an image
   */
  string file2 = outputdirectory + segment + ".jpg";
  writeI(file2,ptsArr,all);

  
  return 0;
}
