#include <iostream>
#include <cstdlib>

// #include <opencv.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void 
process(const char* imsname_1, const char* imsname_2)
{
  Mat img1 = imread(imsname_1, CV_LOAD_IMAGE_GRAYSCALE);
  Mat img2 = imread(imsname_2, CV_LOAD_IMAGE_GRAYSCALE);

  int faux_positif = 0;
  int faux_negatif = 0;

  Mat result(img1.size(), CV_8UC3);

    for (int i = 0; i < img1.rows; ++i){
        for(int j = 0; j < img1.cols; ++j){
          if((int)img1.at<uchar>(i,j) > (int)img2.at<uchar>(i,j)){
            faux_positif++; 
            result.at<Vec3b>(i,j)[0] = 255;
          }
          else if((int)img1.at<uchar>(i,j) < (int)img2.at<uchar>(i,j)){
            faux_negatif++;
            result.at<Vec3b>(i,j)[2] = 255;
          }
          else{
            result.at<Vec3b>(i,j)[0] = result.at<Vec3b>(i,j)[1] = result.at<Vec3b>(i,j)[2] = img2.at<uchar>(i,j);
          }

        }
    }

    int count = faux_negatif+faux_positif;
    int area = img1.rows*img1.cols;
    float percent = 100 - (count*100.0/area);
    float percent_positif = (faux_positif*100.0/area);
    float percent_negatif = (faux_negatif*100.0/area);

    cout << "Number of different pixels: " << count;
    cout << ", False positive: " << faux_positif;
    cout << ", False negative: " << faux_negatif << endl;
    cout << "Matching: " << percent << "%"; 
    cout << ", False positive: " << percent_positif << "%"; 
    cout << ", False negative: " << percent_negatif << "%" << endl << endl; 

    imwrite("Result.png", result);
    imshow("Result", result);
    waitKey();
} 

void 
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims1 ims2"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int 
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
process(argv[1], argv[2]);
return EXIT_SUCCESS;  
}

