#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>

#include <opencv.hpp>

using namespace cv;
using namespace std;



void process(const char* ims_name, const char* th_1, const char* th_2){
	Mat img = imread(ims_name, CV_LOAD_IMAGE_COLOR);
	Mat img_hsv;
	cvtColor(img, img_hsv, CV_BGR2HSV);

	int th1 = atoi(th_1)/2;
	int th2 = atoi(th_2)/2;

	//Extracting H channel
	Mat HSVchannels[3];
	split(img_hsv, HSVchannels);
	Mat H = HSVchannels[0];

	Mat H_range(H.size(), CV_8UC1);
	Mat H_thresh;
	
	// for(int i = 0; i < H.rows; ++i){
	// 	for(int j = 0; j < H.cols; ++j){
	// 		uchar val = H.at<uchar>(i,j);
	// 		H_range.at<uchar>(i,j) = ((val < th1) || (val > th2))? 0 : 255;
	// 	}
	// }

	Mat HSV_ranged[3];
	int low[3] = {th1, 100, 100};
	int up[3] = {th2, 200, 200};

	inRange(HSVchannels, low, up, HSV_ranged);

	Mat img_hsv_ranged;
	merge(HSV_ranged, 3, img_hsv_ranged);

	imshow("img_hsv_ranged", img_hsv_ranged);
	// Mat H_open;
	// int morph_size = 2;
	// Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2*morph_size+1, 2*morph_size+1));
	// morphologyEx(H_range, H_open, MORPH_OPEN, element);
	// imshow("H_open", H_open);

	// adaptiveThreshold(H_range, H_thresh, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 201, 8);
	
	// imshow("H_range", H_range);
	// imshow("H_thresh", H_thresh);
	// imwrite("H.png", H);

	// imshow("Canny", detected_edges);
	waitKey();

}


void usage(const char* s){
	cerr<<"Usage: " << s << " ims-name th_1 th_2\n" << endl;
	exit(EXIT_FAILURE);
}


#define param 3

int main(int argc,const char* argv[]){
	
	if (argc != (param + 1))
	{
		usage(argv[0]);
	}
	process(argv[1], argv[2], argv[3]);

	return EXIT_SUCCESS;
}