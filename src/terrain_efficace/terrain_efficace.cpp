#include <iostream>
#include <sys/time.h>
using namespace std;

#include <opencv.hpp>
using namespace cv;


#define disp false


void process(const char* imsname, const char* imdname){
  Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR), HSV; // Read the given image in color

  if (!ims.data) {
    cerr << "Aborting calibration..." << endl;
    exit (EXIT_FAILURE);
  }

  int iLowH = 23, iHighH = 63;    // Intervals used to threshold the channels
  int iLowS = 38, iHighS = 255;   // These values should filter most of the non-field parts of the image
  int iLowV = 25, iHighV = 133;

  Mat imth; // Apply those thresholds on the HSV image to get a binary mask
  Mat rect; // Kernel for morpholical operation
  Mat rect3 = getStructuringElement(MORPH_ELLIPSE, Size(3, 3)); // Kernel for final dilatation

  // Vector for extract the contours from the binary mask
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  vector< vector<Point> > hulls(1); // Pseudo-container for convex hull contours
  Scalar color = Scalar(255); // Pure white

  struct timeval t0, tf; // Objects used to time the whole process
  unsigned long dt;
  gettimeofday( &t0, NULL);

  cvtColor(ims, HSV, CV_BGR2HSV); // Convert to HSV color space: [0,180]x[0,255]x[0,255]
  inRange(HSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imth);

  // Apply various morphological operations to clean up the mask from coarse noise
  for (int i = 1; i<15; i+=2)
  {
      rect = getStructuringElement(MORPH_RECT, Size(i, i));
      morphologyEx(imth, imth, MORPH_OPEN, rect, Point(-1, -1), 1, BORDER_REPLICATE, Scalar(0));

      if (disp)
        imshow("Threshold mask after OPEN", imth);

      morphologyEx(imth, imth, MORPH_CLOSE, rect, Point(-1, -1), 1, BORDER_REPLICATE, Scalar(0));

      if (disp)
      {
        imshow("Threshold mask after morph", imth);
        waitKey(0);
      }
  }

  findContours( imth, contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );  

  Mat mask = Mat::zeros( imth.size(), CV_8UC1 ); // Field mask : start with a black-filled image

  // Find the contour with the bigger area
  double amax = 0, area;
  int imax = -1;
  for( size_t i = 0; i < contours.size(); i++ ){
    area = contourArea(contours[i]);
    if (amax < area){
      imax = i;
      amax = area;
    }
  }
  // Fill the mask based on its convex hulls
  convexHull( Mat(contours[imax]), hulls[0], false );
  drawContours(mask, hulls, 0, color, CV_FILLED);

  // Apply a final dilation to expand the hull by one pixel in each direction
  dilate(mask, mask, rect3);

  gettimeofday( &tf, NULL);
  dt = (tf.tv_sec - t0.tv_sec) * 1000000L + tf.tv_usec - t0.tv_usec;
  cout << "Processing time of " << dt << " microseconds" << endl;

  if (disp) {
    // imshow("Original image", ims);
    // imshow("Mask", mask );
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
