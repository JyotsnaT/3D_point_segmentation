#include<opencv2/core/core.hpp>
//#include<opencv2/contrib/contrib.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/core/mat.hpp>
#include<opencv2/opencv.hpp>


#include<iostream>
#include<string>
#include<sstream>
//#include "point.h"
//#include "heapsort.h"
#include "vrml.h"

using namespace std;
using namespace cv;

void writeI(string filename, point_3d *pts, int N)
{
  
  //int N = sizeof(pts)/sizeof(point_3d);
  cout<<N<<endl;
  /*float arr[N][N];
  for(int i = 0;i<N;i++)
    for(int j = 0;j<N;j++)
      arr[i][j] = 0.0;
 */
  float minx = getMinX(pts,N);
  float miny = getMinY(pts,N);
  float maxx = getMaxX(pts,N);
  float maxy = getMaxY(pts,N);
  cout<<maxx<<' '<<maxy<<endl;
  cout<<minx<<' '<<miny<<endl;
  int sizex = maxx-minx + 1;
  int sizey = maxy-miny + 1;
  
  Mat img(sizex,sizey, CV_8UC3, Scalar(0, 0, 0));
  Size size(8*sizex,8*sizey);
  Mat image;//dst image
  resize(img,image,size);//resize image

  //Rect const box(minx,miny,maxx,maxy);
  //Mat img = image(box);
  
  //Mat image = Mat::zeros( N, N, CV_32FC1 )
  cout<<"printing image"<<endl;
  for(int i = 0;i<N;i++)
  {
    int thickness = -1;
    int lineType = 8;
    Point pt =  Point((pts[i].get_x()-minx)*8,(pts[i].get_y()-miny)*8);
    //cout<<i<<' '<<pt<<endl;
    circle( image, pt, 1, Scalar( 0, 255, 0 ), thickness, lineType );
  }
  /*circle( img, Point(1,1), 50, Scalar( 0, 0, 255 ), -1, 8 );
  circle( img, Point(2,2), 50, Scalar( 0, 0, 255 ), -1, 8 );
  circle( img, Point(3,3), 50, Scalar( 0, 0, 255 ), -1, 8 );
  circle( img, Point(4,4), 50, Scalar( 0, 0, 255 ), -1, 8 );
  circle( img, Point(5,5), 50, Scalar( 0, 0, 255 ), -1, 8 );*/
  
 

  

  vector<int> compression_params;
  compression_params.push_back(IMWRITE_JPEG_QUALITY);
  compression_params.push_back(95);
  imwrite( filename.c_str(), image, compression_params );
  //imwrite(filename.c_str(),  cv::Mat(N, N, CV_32FC1, arr));
  //Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    //cout << "C = " << endl << " " << C << endl << endl;
  
  //namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  //imshow( "Display window", img );                   // Show our image inside it.  
  //waitKey(0); 
}