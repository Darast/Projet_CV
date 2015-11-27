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
  Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR); // Read the given image in color
  cvtColor(ims, ims, CV_BGR2HSV); // Convert to HSV color space: [0,180]x[0,255]x[0,255]
  
  Mat HSVchannels[3];
  split(ims, HSVchannels); // Split channels

  Mat H = HSVchannels[0]; // Extract H channel and apply thresholds
  Mat Hmin, Hmax, Hth, immask ;
  threshold(H, Hmin, thmin / 2, 255, THRESH_BINARY);
  imshow("Hmin", Hmin);
  threshold(H, Hmax, thmax / 2, 255, THRESH_BINARY_INV);
  imshow("Hmax", Hmax);

  Hth = (Hmax & Hmin);
  imshow("Thresholded hue", Hth);
  waitKey();
  
  //immask = (Hth & ims);
  //imshow("Thresholded image", immask);
}


void usage(const char* s){
	cerr<<"Usage: " << s << " ims-name th-mag\n" << endl;
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
