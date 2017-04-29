#include"kdtree.h"
#include<math.h>
#include<iostream>
#include<string.h>
#include<limits.h>
using namespace std;


kdtree::kdtree()
  {
    root = NULL;
    k = 3;
  }
void kdtree::insert(point_3d pt, int ind)
  {
    node *newNode = new node(pt,ind);
    if(!root)
    {
      root = newNode;
      root->axis = 0;
      return;
    }
    int cd, depth = 0;
    node *temp = root;
    
    while(temp)
    {
      cd = depth%k;
      float(point_3d::*fptr)();
      switch(cd)
      {
	case 0 : fptr = &point_3d::get_x;
	         break;
	case 1 : fptr = &point_3d::get_y;
	         break;
	case 2 : fptr = &point_3d::get_z;
	         break;
      }
      if((newNode->pt.*fptr)()<(temp->pt.*fptr)())
      {
	if(!temp->left)
	{
	  newNode->axis = (cd+1)%k;
	  temp->left = newNode;
	  break;
	}
	else
	  temp = temp->left;
      }
      else
      {
	if(!temp->right)
	{
	  newNode->axis = (cd+1)%k;
	  temp->right = newNode;
	  break;
	}
	else
	  temp = temp->right;
      }
      depth++;	
    }//while
  }
  
void kdtree::knearest(point_3d query, node *root, int k, minHeap *result)
  {
    if(!root)
      return;
    float distance = distEuclid(query,root->pt);
    //cout<<distance<<endl;
    float dx = sub(root->pt,query,root->axis);
    //cout<<"queue size is now "<<result->size<<endl;
    if(result->size+1 < k || distance <= result->first[0])
    {
      result->insert(distance,root->pt,root->index);
      //cout<<"queue size is now "<<result->size<<endl;
      float temp;
      if(result->size+1>=k)
	temp = result->pop();
    }
    /*else{
      cout<<"result->size+1 "<<result->size+1<<endl;
      cout<<"distance <= result->first[0] "<<distance<<" "<<result->first[0]<<endl;
    }*/
    node *near = dx<=0 ? root->left:root->right;
    node *far = dx<=0 ? root->right:root->left;
    knearest(query,near,k,result);
    if((dx*dx) >= result->first[0])
      return;
    knearest(query,far,k,result);
  }
  
  
  
  
/*
 * **********  Graph functions *****************
 */
Graph::Graph(int N, int set, point_3d *ptsArr)
  {
    V = N + 2;
    Adjlist = new listNode*[V];
    for(int i = 0;i<V;i++)
      Adjlist[i] = NULL;
    switch(set)
    {
      case 0 : source.set(getMinX(ptsArr,N),getMinY(ptsArr,N),getMinZ(ptsArr,N));
	       sink.set(getMaxX(ptsArr,N),getMaxY(ptsArr,N),getMaxZ(ptsArr,N));
	       break;
      case 1 : source.set(getMaxX(ptsArr,N),getMinY(ptsArr,N),getMinZ(ptsArr,N));
	       sink.set(getMinX(ptsArr,N),getMaxY(ptsArr,N),getMaxZ(ptsArr,N));
	       break;
      case 2 : source.set(getMinX(ptsArr,N),getMaxY(ptsArr,N),getMinZ(ptsArr,N));
	       sink.set(getMaxX(ptsArr,N),getMinY(ptsArr,N),getMaxZ(ptsArr,N));
	       break;
      case 3 : source.set(getMaxX(ptsArr,N),getMaxY(ptsArr,N),getMinZ(ptsArr,N));
	       sink.set(getMinX(ptsArr,N),getMinY(ptsArr,N),getMaxZ(ptsArr,N));
	       break;
    }
    /*for(int i = 1;i<=N; i++)//connect all nodes to source nodes
    {
      listNode *newNode = new listNode(i,0.0);
      newNode->dist = distEuclid(ptsArr[i-1],source);
      newNode->next = Adjlist[0];
      Adjlist[0] = newNode;
    }*/
    for(int i = 1; i<V-1; i++)//connect sink node to all nodes
    {
      listNode *newNode = new listNode(V-1,0.0);
      newNode->dist = 1/distEuclid(ptsArr[i-1],sink);
      newNode->next = Adjlist[i];
      Adjlist[i] = newNode;
    }
  }//constructor

  
void Graph::insert(int u, int v, float dist)
  {
    listNode *newNode = new listNode(v+1,dist);
    newNode->next = Adjlist[u+1];
    Adjlist[u+1] = newNode;
  }
  
void Graph::print()
{
  for(int i = 0;i<V;i++)
  {
    cout<<"Adjacency list of "<<i<<endl;
    listNode *temp = Adjlist[i];
    while(temp)
    {
      cout<<temp->pt<<"--";
      temp = temp->next;
    }
    cout<<endl;
  }
}
  
/*
 * BFS - return true if there is a path between source and sink, updates a parent array for tracking the path
 */

bool bfs(Graph G_res, int parent[])
{
  int V = G_res.V;
  bool visited[V];
  memset(visited,false,V);
  
  /*implement queue**/
  listNode *head, *tail;
  head = NULL, tail = NULL;
  listNode *newNode = new listNode(0,0.0);
  head = newNode, tail = newNode;
  visited[0] = true;
  parent[0] = -1;
  
  while(tail && head)
  {
    int u = head->pt;
    listNode *temp = head;
    //cout<<"for "<<u<<endl;
    listNode *temp2 = G_res.Adjlist[u];
    while(temp2)
    { 
      //cout<<"while got true for "<<temp2->pt<<endl;
      if(!visited[temp2->pt] && temp2->dist > 0)
      {
	listNode *newNode = new listNode(temp2->pt,0);
	//push this node into queue
	tail->next = newNode;
	tail = tail->next;
	parent[temp2->pt] = u;
	visited[temp2->pt] = true;
	//cout<<"visited "<<temp2->pt<<endl;
      }
      temp2 = temp2->next;
    }//inner loop
    head = head->next;
    delete temp;
    //cout<<tail<<' '<<head<<endl;
  }//outer while
  return (visited[V-1]);
}

/*
 * DFS - returns all the nodes reachable from source
 */

void dfs(Graph G_res, bool visited[])
{
  visited[0] = true;
  listNode *temp = G_res.Adjlist[0];
  while(temp && temp->next)
  {
    temp = temp->next;
    if(temp->dist > 0)
      visited[temp->pt] = true;
  }
}

/*
 * Ford - fulkerson for finding mincut of the nearest neighbor graph
 */

bool* mincut(Graph G,int set, point_3d *ptsArr)
{
  /*
   *Create a residual graph
   *Initially it is the same as original graph   
   */
  
  int V = G.V;
  Graph G_res(V-2,set,ptsArr);
  
  /*clone the graph*/
  for(int i = 0;i<V;i++)
  {
    listNode *temp2 = NULL,*temp = G.Adjlist[i];
    if(temp)
      temp2 = new listNode(temp->pt,temp->dist);
    G_res.Adjlist[i] = temp2;
    while(temp && temp->next)
    {
      temp = temp->next;
      listNode *temp3 = new listNode(temp->pt,temp->dist);
      temp2->next = temp3;
      temp2 = temp3;
    }
  }
  cout<<"graph cloned"<<endl;
  /*A parent array for backtracking*/
  int parent[V];
  
  /*find path from source to sink and augment. Repeat till there is no path.*/
  while(bfs(G_res,parent))
  {
    cout<<"bfs done"<<endl;
    /*minimal residual capacity of the path*/
    int minFlow = INT_MAX;
    for(int v = V-1; v != -1; v = parent[v])
    {
      int u = parent[v];
      if(u != -1)
      {
      listNode *temp = G_res.Adjlist[u];
      while(temp)
      {
	if(temp->pt == v)
	{
	  minFlow = minFlow > temp->dist?temp->dist:minFlow;
	  break;
	}
	else
	  temp = temp->next;
      }
      }
    }
    cout<<"minflow "<<minFlow<<endl;
    /*update residual graph by changing the flow values for all*/
    for(int v = V-1; v != -1; v = parent[v])
    {
      int u = parent[v];
      //cout<<u<<endl;
      if(u != -1)
      {
      listNode *temp = G_res.Adjlist[u];//update forward edge
      while(temp)
      {
	if(temp->pt == v)
	{
	  temp->dist = temp->dist - minFlow;
	  break;
	}
	else
	  temp = temp->next;
      }
      
      
      /*listNode *temp2 = G_res.Adjlist[v];//update backward edge
      while(temp2)
      {
	if(temp2->pt == u)
	{
	  temp2->dist = temp2->dist + minFlow;
	  break;
	}
	else
	  temp2 = temp2->next;
      }*/
      }
    }//for loop
  }//while loop
  
  /*finding vertices reachable from source*/
  bool visited[V];
  memset(visited,false,V);
  dfs(G_res,visited);
  //for(int i = 0;i<V;i++)
    //cout<<visited[i]<<'\t';
  /*return the visited array*/
  return visited;
}