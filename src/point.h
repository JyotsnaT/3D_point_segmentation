class point_3d
{
  float x,y,z;
  int cat;
public :
  point_3d();
  void set(float a, float b, float c);
  float get_x();
  float get_y();
  float get_z();
  void set_cat(int K);
  int get_cat();
  void print();
};

void copyP(point_3d *A, point_3d *B);

float distEuclid(point_3d A, point_3d B);
float sub(point_3d A,point_3d B,int dim);

float getMinX(point_3d *pts, int N);
float getMinY(point_3d *pts, int N);
float getMinZ(point_3d *pts, int N);
float getMaxX(point_3d *pts, int N);
float getMaxY(point_3d *pts, int N);
float getMaxZ(point_3d *pts, int N);