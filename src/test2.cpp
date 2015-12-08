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
	int H_hist[180] = {0};
	uchar max_index = 0;

	int mat[5][5] = {{1,1,2,3,4}, 
					{5,6,78,9,2},
					{2,36,5,3,5},
					{1,5,5,2,2},
					{7,8,22,3,2}};

	for(int i = 0; i < H.rows; ++i){
		for(int j = 0; j < H.cols; ++j){
			uchar val = H.at<uchar>(i,j);
			++H_hist[val];
			if(H_hist[max_index] < H_hist[val]){
				max_index = val;
				cout << (int) max_index << endl;			
			}
		}
	}

	cout << "max_index : " << (int) max_index << endl;

	for(int i = 0; i < 180; i++){
		cout << "(" << i << ")" << (int) H_hist[i] << " ";
	}

	Mat H_th;
	inRange(H, max_index-10, max_index+20, H_th);

	imshow("H_th", H_th);
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