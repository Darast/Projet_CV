#include <iostream>
#include <cstdlib>

#include <sys/time.h>
#include <opencv.hpp>

using namespace cv;
using namespace std;

void process(const char* imsname)
{


    struct timeval tbegin,tend;
    double texec=0.;

    gettimeofday(&tbegin,NULL);
    // do something
    // ...
    Mat image;
    image = imread(imsname, CV_LOAD_IMAGE_COLOR);


    int iLowH = 23;
    int iHighH = 63;

    int iLowS = 38;
    int iHighS = 255;

    int iLowV = 25;
    int iHighV = 133;

    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);

    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);

    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    Mat imgHSV;
    Mat imgThresholded;

    while (true)
    {
        cvtColor(image, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

        //morphological opening (remove small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );

        //morphological closing (fill small holes in the foreground)
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)) );

        imshow("Thresholded Image", imgThresholded); //show the thresholded image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }




    gettimeofday(&tend,NULL);
    texec=((double)(1000*(tend.tv_sec-tbegin.tv_sec) + ((tend.tv_usec-tbegin.tv_usec)/1000)))/1000.;

    cout << "Access with ’at’ method ... takes " << texec << endl;

    waitKey(0);
}

void usage(const char *s)
{
    std::cerr<<"Usage: "<<s<<" imsname \n"<<std::endl;
    exit(EXIT_FAILURE);
}

#define param 1

int main( int argc, char* argv[] )
{
    if(argc != (param+1))
        usage(argv[0]);
    process(argv[1]);
    return EXIT_SUCCESS;
}
