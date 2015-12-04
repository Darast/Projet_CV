#include <iostream>
#include <sys/time.h>
using namespace std;

#include <opencv.hpp>
using namespace cv;


#define disp false

void process(const char* imsname, const char* imdname){
  Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR), HSV; // Read the given image in color

  struct timeval t0, tf; // Objects used to time the whole process
  unsigned long dt;
  gettimeofday( &t0, NULL);

  cvtColor(ims, HSV, CV_BGR2HSV); // Convert to HSV color space: [0,180]x[0,255]x[0,255]
  int iLowH = 23, iHighH = 63;    // Intervals used to threshold the channels
  int iLowS = 38, iHighS = 255;   // These values should filter most of the non-field parts of the image
  int iLowV = 25, iHighV = 133;
  
  Mat imth; // Apply those thresholds on the HSV image to get a binary mask
  inRange(HSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imth);

  // Apply various morphological operations to clean up the mask from basic noise
  Mat ell7 = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
  Mat ell5 = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
  erode(imth, imth, ell7);
  dilate(imth, imth, ell5);
  morphologyEx(imth, imth, MORPH_CLOSE, ell5, Point(-1, -1), 1, BORDER_CONSTANT, Scalar(0));

  if (disp)
    imshow("Threshold mask after morph", imth);

  //* @HULL
  vector<vector<Point> > contours; // Extract the contours from the binary mask
  vector<Vec4i> hierarchy;
  findContours( imth, contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );  

  double ath = ims.cols * ims.rows / 4; // Area threshold: one quarter of the total image
  vector< vector<Point> > hulls(contours.size());
  Mat mask = Mat::zeros( imth.size(), CV_8UC1 ); // Field mask : start with a black-filled image
  Scalar color = Scalar(255); // Pure white

  // Find contours having an area bigger than the area threshold
  // and fill the mask based on their convex hulls
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

  if (disp) {
    imshow("Original image", ims);
    imshow("Mask", mask );
    Mat imcut;
    ims.copyTo(imcut, mask);
    imshow("Extracted part of the image", imcut);
    waitKey();
  }

  imwrite(imdname, mask);
}

void usage(const char* s){
	cerr << "Usage: " << s << "test1 ims-name imd-name\n" << endl;
	exit(EXIT_FAILURE);
}


#define param 2

int main(int argc,const char* argv[]){
	
	if (argc != (param + 1))
	{
		usage(argv[0]);
	}
	process(argv[1], argv[2]);

	return EXIT_SUCCESS;
}
