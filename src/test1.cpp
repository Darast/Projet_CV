#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <cstdio>

#include <opencv.hpp>

using namespace cv;
using namespace std;


void process(const char* imsname, const int thmin, const int thmax){
  Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR), HSV; // Read the given image in color

  struct timeval t0, tf;
  unsigned long dt;
  gettimeofday( &t0, NULL);

  //imshow("Original image", ims);
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
  //imshow("Thresholded hue before morph", Hth);

  Mat seO = getStructuringElement(MORPH_RECT, Size(5, 5));
  morphologyEx(Hth, Hth, MORPH_OPEN, seO, Point(-1, -1), 1, BORDER_CONSTANT, Scalar(0));
  morphologyEx(Hth, Hth, MORPH_CLOSE, seO, Point(-1, -1), 1, BORDER_CONSTANT, Scalar(0));
  imshow("Thresholded hue after morph", Hth);

  //* @HULL
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  findContours( Hth, contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );  
  cout << contours.size() << " contours have been identified." << endl;

  double ath = ims.cols * ims.rows / 4;
  vector< vector<Point> > hulls(contours.size());
  Mat mask = Mat::zeros( Hth.size(), CV_8UC1 );
  Scalar color = Scalar(255);

  for( size_t i = 0; i < contours.size(); i++ ){
    double area = contourArea(contours[i]);
    if (ath < area){
      convexHull( Mat(contours[i]), hulls[i], false );    
      drawContours(mask, hulls, i, color, CV_FILLED);
    }
  }
  //@HULL */

  gettimeofday( &tf, NULL);
  dt = (tf.tv_sec - t0.tv_sec) * 1000000L + tf.tv_usec - t0.tv_usec;
  cout << "Processing time of " << dt << " microseconds" << endl;

  //* @SHOW
  imshow("Original image", ims);
  //imshow("Mask", mask );
  Mat imth;
  ims.copyTo(imth, mask);
  imshow("Extracted part of the image", imth);
  // @SHOW */
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
