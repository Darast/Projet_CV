#include <iostream>
#include <cstdlib>

// #include <opencv.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void 
process(const char* imsname_1, const char* imsname_2/*, const char* imdname*/)
{
  Mat img1 = imread(imsname_1, CV_LOAD_IMAGE_GRAYSCALE);
  Mat img2 = imread(imsname_2, CV_LOAD_IMAGE_GRAYSCALE);

  // Mat diff(img1.size(), CV_8UC1);
  int faux_positif = 0;
  int faux_negatif = 0;

    for (int i = 0; i < img1.rows; ++i){
        for(int j = 0; j < img1.cols; ++j){
            // int tmp = (int)img1.at<uchar>(i,j) - (int)img2.at<uchar>(i,j);
            // diff.at<uchar>(i,j) = (uchar) (tmp < 0)?0:(tmp>255)?255:tmp;
          if((int)img1.at<uchar>(i,j) > (int)img2.at<uchar>(i,j))
            faux_positif++;
          else if((int)img1.at<uchar>(i,j) < (int)img2.at<uchar>(i,j))
            faux_negatif++;
        }
    }

    // imwrite(imdname, diff);
    int count = faux_negatif+faux_positif;
    int area = img1.rows*img1.cols;
    float percent = 100 - (count*100.0/area);
    float percent_positif = (faux_positif*100.0/area);
    float percent_negatif = (faux_negatif*100.0/area);

    cout << "Nombre de pixels de différence : " << count << endl;
    cout << "Faux positifs : " << faux_positif << endl;
    cout << "Faux négatifs : " << faux_negatif << endl;
    cout << "Matching : " << percent << "%" << endl; 
    cout << "dont faux positifs : " << percent_positif << "%" << endl; 
    cout << "dont faux négatifs : " << percent_negatif << "%" << endl << endl; 

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

