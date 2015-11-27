#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>

#include <opencv.hpp>

using namespace cv;
using namespace std;


void process(const char* imsname, const int thmin, const int thmax){
  Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR), HSV; // Read the given image in color
  cvtColor(ims, HSV, CV_BGR2HSV); // Convert to HSV color space: [0,180]x[0,255]x[0,255]
  
  Mat HSVchannels[3];
  split(HSV, HSVchannels); // Split channels

  Mat H = HSVchannels[0]; // Extract H channel and apply thresholds
  Mat Hmin, Hmax, Hth;
  threshold(H, Hmin, thmin / 2, 255, THRESH_BINARY);
  //imshow("Hmin", Hmin);
  threshold(H, Hmax, thmax / 2, 255, THRESH_BINARY_INV);
  //imshow("Hmax", Hmax);

  Hth = (Hmax & Hmin);
  //imshow("Thresholded hue", Hth);
  imshow("Original image", ims);

  /*Mat Heq;
  equalizeHist(H, Heq);
  imwrite("Heq.png", Heq);

  threshold(Heq, Hmin, thmin, 255, THRESH_BINARY);
  //imshow("Hmin", Hmin);
  threshold(Heq, Hmax, thmax, 255, THRESH_BINARY_INV);
  //imshow("Hmax", Hmax);

  Hth = (Hmax & Hmin);
  imshow("Thresholded hue", Hth);
  
  Mat immask2;
  ims.copyTo(immask2, Hth);
  imshow("Thresholded image", immask2); */
  
  Mat imcopy = ims.clone();
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  findContours( Hth, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  vector<vector<Point> >hull( contours.size() );
  for( size_t i = 0; i < contours.size(); i++ ){
    convexHull( Mat(contours[i]), hull[i], false ); }

  double amax = 0;
  int imax = 0;
  for( size_t i = 0; i< contours.size(); i++ ){
    double area = contourArea(hull[i]);
    if (amax < area){
      amax = area;
      imax = (int) i;
    }
  }
  
  Mat mask = Mat::zeros( Hth.size(), CV_8UC1 );
  Scalar color = Scalar(255);
  //drawContours( drawing, contours, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
  drawContours(mask, hull, imax, color, CV_FILLED);//, 8, vector<Vec4i>(), 0, Point() );
  //imshow("Hull", mask );

  Mat imth;
  ims.copyTo(imth, mask);
  imshow("Thresholded image", imth);
  waitKey();
}


void usage(const char* s){
	cerr<<"Usage: " << s << " ims-name th-min th-max\n" << endl;
	exit(EXIT_FAILURE);
}


#define param 3

int main(int argc,const char* argv[]){
	
	if (argc != (param + 1))
	{
		usage(argv[0]);
	}
	process(argv[1], atoi(argv[2]), atoi(argv[3]));

	return EXIT_SUCCESS;
}
