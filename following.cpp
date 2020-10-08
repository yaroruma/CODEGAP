#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "car_lib.h"

#define nw 320
#define nh 180

extern "C"{
using namespace cv;
using namespace std;

void follow()
{
    
    int LowH = 170;
    int HighH = 179;
    int LowS = 150;
    int HighS = 255;
    int LowV = 60;
    int HighV = 255;
    Mat imgOriginal;
    Mat imgHSV;
    Mat imgThresholded;
    
    VideoCapture cap(-1);
    cap.read(imgOriginal);
     

    cvtColor(imgOriginal, imgHSV, CV_BGR2HSV);          //opencv2.4.9.ver
        //cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

    inRange(imgHSV, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), imgThresholded);
    rectangle(imgThresholded, Point(0, 0), Point(640, 180), Scalar(0, 0, 0), -1);

    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    Moments oMoments = moments(imgThresholded);

    double dM01 = oMoments.m01;
    double dM10 = oMoments.m10;
    double dArea = oMoments.m00;

    Mat dst1, dst2;
    printf("%d\n", dArea);
    if (dArea > 100000)
    {
        int posX = 640 - dM10 / dArea;
        int posY = dM01 / dArea;
	printf("서\n");
	printf("종현\n");
            
    }

}
}
