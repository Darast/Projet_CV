#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>

#include <opencv.hpp>

using namespace cv;
using namespace std;



void process(const char* ims_name, const char* th_val){
	Mat img = imread(ims_name, CV_LOAD_IMAGE_COLOR);
	Mat img_hsv;
	cvtColor(img, img_hsv, CV_BGR2HSV);

	//Extracting H channel
	Mat HSVchannels[3];
	split(img_hsv, HSVchannels);
	Mat H = HSVchannels[0];

	// Treshold on green hue
	adaptiveThreshold(H, H, 90, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 201, 8);
	imshow("H_threshold", H);

	// int edgeThresh = 1;
	int lowThreshold;
	// int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;
	// char* window_name = "Edge Map";


	Mat dst, detected_edges;

	//Gaussian blur
	blur(H, detected_edges, Size(3,3) );
	//Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

	imshow("Canny", detected_edges);
	waitKey();

}


void usage(const char* s){
	cerr<<"Usage: " << s << " ims-name th-mag\n" << endl;
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