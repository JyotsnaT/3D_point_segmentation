#include"priority_queue.h"
#include<cstdlib>

struct node
{
  point_3d pt;
  int index;
  int axis;
  node *left, *right;
  node(point_3d arr, int ind)
  {
    pt.set(arr.get_x(),arr.get_y(),arr.get_z());
    left = NULL, right = NULL;
    axis = -1;
    index = ind;
  }
};

class kdtree
{
  public:
  node *root;
  int k;

  kdtree();
  void insert(point_3d pt, int ind);
  void knearest(point_3d query, node *root, int k, minHeap *result);
};

struct listNode
{
  int pt;
  float dist;
  listNode *next;
  listNode(int ind, float d)
  {
    pt = ind;
    dist = d;
    next = NULL;
  }
};

class Graph
{
 public:
  int V;
  point_3d source, sink;
  listNode **Adjlist;
  Graph(int N, int set, point_3d *ptsArr);  
  void insert(int u, int v, float dist);
  void print();
};

bool bfs(Graph G_res, int parent[]);
void dfs(Graph G_res, bool visited[]);
bool* mincut(Graph G,int set, point_3d *ptsArr);