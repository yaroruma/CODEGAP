
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
//#include <sys/time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/gpu/device/utility.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "car_lib.h"


#define PI 3.1415926

using namespace std;
using namespace cv;
extern int line_l[];
extern int line_r[];
extern float s_angle;
extern "C" {


//----------------------------------------------------------------------------------------------------


void vertical_parking(void)
{
	
	int angle, speed;
	//PositionControlOnOff_Write(CONTROL);
	angle = 1000;
	speed = -80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 1000)
	{
		printf("%d\n",EncoderCounter_Read());
	}
	angle = 1500;
	speed = -80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 500)
	{
		printf("%d\n",EncoderCounter_Read());
	}

	angle = 1500;
	speed = 0;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	sleep(3);

	angle = 1500;
	speed = 80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 500)
	{
		printf("%d\n",EncoderCounter_Read());
	}

	angle = 1000;
	speed = 80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 1300)
	{
		printf("%d\n",EncoderCounter_Read());
	}
	
}

void horizental_parking(void)
{
	
	int angle, speed; 
	//PositionControlOnOff_Write(CONTROL);
	angle = 1000;
	speed = -80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);
	
	while (abs(EncoderCounter_Read()) < 1000)
	{
		printf("encoder value1 : %d\n", abs(EncoderCounter_Read()));
	}

	angle = 1500;
	speed = 80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);
	
	while (abs(EncoderCounter_Read()) < 200)
	{
		printf("encoder value2 : %d\n", abs(EncoderCounter_Read()));
	}


	angle = 2000;
	speed = -80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);
	
	while (abs(EncoderCounter_Read()) < 900)
	{
		printf("encoder value3 : %d\n", abs(EncoderCounter_Read()));
	}


	angle = 2000;
	speed = 0;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	sleep(3);
	

	
	angle = 2000;
	speed = 80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 800)
	{
		
	}

	angle = 1500;
	speed = -80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 300)
	{
		
	}


	angle = 1000;
	speed = 80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 800)
	{

	}

	angle = 1500;
	speed = 80;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 400)
	{

	}

}



void tunnel_right(int d1,int d2)                                    //터널주행
{
	int d3 = d2 + 170;
	int angle;
	if(d1<d3) //우회전
	{
		angle = (int)(1500 - abs(d3-d1)/2);
		if(angle < 1000)
		angle = 1000;
	}
	else //직진과 좌회전
	{
		angle = (int)(1500 + abs(d1-d3)/2);
		if(angle > 2000)
		angle = 2000;
	}

	int speed = 90;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

}

void left_choowol(void) {                                           //왼쪽 차로로 추월
    int angle;
    int speed;

    angle = 1500;
    speed = -50;
    SteeringServoControl_Write(angle);
    DesireSpeed_Write(speed);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 300)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 2000;
    speed = 80;
    SteeringServoControl_Write(angle);
    DesireSpeed_Write(speed);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 600)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 1000;
    SteeringServoControl_Write(angle);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 600)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 1500;
    SteeringServoControl_Write(angle);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 300)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 1000;
    SteeringServoControl_Write(angle);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 650)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 2000;
    SteeringServoControl_Write(angle);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 650)
    {
    printf("%d\n", EncoderCounter_Read());
    }
}

void right_choowol(void) {                                      //오른쪽 차로로 추월
    int angle;
    int speed;

    angle = 1500;
    speed = -50;
    SteeringServoControl_Write(angle);
    DesireSpeed_Write(speed);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 300)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 1000;
    speed = 100;
    SteeringServoControl_Write(angle);
    DesireSpeed_Write(speed);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 600)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 2000;
    speed = 100;
    SteeringServoControl_Write(angle);
    DesireSpeed_Write(speed);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 550)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 1500;
    speed = 100;
    SteeringServoControl_Write(angle);
    DesireSpeed_Write(speed);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 300)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 2000;
    speed = 100;
    SteeringServoControl_Write(angle);
    DesireSpeed_Write(speed);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 600)
    {
    printf("%d\n", EncoderCounter_Read());
    }

    angle = 1000;
    speed = 100;
    SteeringServoControl_Write(angle);
    DesireSpeed_Write(speed);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 650)
    {
    printf("%d\n", EncoderCounter_Read());
    }
}


//-----------------------------------------------------------------------------------------------------------


short start_signal(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf, int nw, int nh) //시작 신호 인지
{   
    Mat dstRGB(nh, nw, CV_8UC3, outBuf);
    
    Mat imgOriginal(ih, iw, CV_8UC3, srcBuf);

    int LowH = 170;
    int HighH = 179;
    int LowS = 150; 
    int HighS = 255;
    int LowV = 60;
    int HighV = 255;

    Mat imgHSV;
    Mat imgThresholded;    
    cv::cvtColor(imgOriginal, imgHSV, CV_BGR2HSV);          //opencv2.4.9.ver
        //cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 
    cv::inRange(imgHSV, cv::Scalar(LowH, LowS, LowV, 0), cv::Scalar(HighH, HighS, HighV, 0), imgThresholded);
   

    cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, Size(5, 5)));
    cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, Size(5, 5)));

    cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, Size(5, 5)));
    cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, Size(5, 5)));

    cv::Moments oMoments = cv::moments(imgThresholded);

    double dArea = oMoments.m00;

    if (dArea > 1000000)                                //빨간색이 일정 크기 이상이면 start
    {
	return 1;
    }

    return 0;
}

//-----------------------------------------------------------------------------------------------

void trace_color(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf, int nw, int nh) //특정색 따라가기
{   
  
    Scalar lineColor = cv::Scalar(255,255,255);
    
    Mat dstRGB(nh, nw, CV_8UC3, outBuf);
    
    Mat imgOriginal(ih, iw, CV_8UC3, srcBuf);
    int LowH = 170;
    int HighH = 179;
    int LowS = 150; 
    int HighS = 255;
    int LowV = 60;
    int HighV = 255;
    Mat imgHSV;
    Mat imgThresholded;    
    cv::cvtColor(imgOriginal, imgHSV, CV_BGR2HSV);          //opencv2.4.9.ver
        //cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 
    cv::inRange(imgHSV, cv::Scalar(LowH, LowS, LowV, 0), cv::Scalar(HighH, HighS, HighV, 0), imgThresholded);
   

    cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, Size(5, 5)));
    cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, Size(5, 5)));

    cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, Size(5, 5)));
    cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, Size(5, 5)));

    cv::Moments oMoments = cv::moments(imgThresholded);

    double dM01 = oMoments.m01;
    double dM10 = oMoments.m10;
    double dArea = oMoments.m00;

    Mat dst1, dst2;
    if (dArea > 100000)
    {
        int posX = 640 - dM10 / dArea;
        int posY = dM01 / dArea;
	int speed = (2000000 - dArea)/6000;
        int angle =1500 - (490 - posX);
	DesireSpeed_Write(speed);
	SteeringServoControl_Write(angle);	
	
    }
    else
    {
  	DesireSpeed_Write(0);
    }
    
    cv::resize(imgThresholded, dstRGB, cv::Size(nw, nh), 0, 0, CV_INTER_LINEAR);
}

//-----------------------------------------------------------------------------------------------

int line_tracing(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf)              //OpenCV로 노란색만 라인트레이싱
{

    // 이미지 불러오기, 세팅 //
	Mat dstRGB(ih, iw, CV_8UC3, outBuf);
    Mat img_color(ih, iw, CV_8UC3, srcBuf);
    Mat img_hsv; cvtColor(img_color, img_hsv, CV_BGR2HSV);
    
    //노란색 검출//
   Scalar lower_white = Scalar(200, 200, 200);
	Scalar upper_white = Scalar(255, 255, 255);
	Mat  img_mask1; inRange(img_color, lower_white, upper_white, img_mask1);
	Mat img_white; bitwise_and(img_color, img_color, img_white, img_mask1);

	Scalar lower_yellow = Scalar(20, 70, 70);
	Scalar upper_yellow = Scalar(40, 255, 255);
	Mat  img_mask2; inRange(img_hsv, lower_yellow, upper_yellow, img_mask2);
		
	Mat img_yellow;  bitwise_and(img_color, img_color, img_yellow, img_mask2);
	Mat roi_m; addWeighted(img_yellow, 1.0, img_white, 1.0, 0.0, roi_m);

    //캐니(차선 외곽선만 검출)//
    Mat img_gray;
    cvtColor(img_yellow, img_gray, CV_BGR2GRAY);
    GaussianBlur(img_gray, img_gray, Size(5, 5), 0, 0);
    Mat edges;
    Canny(img_gray, edges, 50, 150);
    //roi 잘라내기//
    int div = 2;
    int atan_x = 0, atan_y = ih/16;
    Mat roi = edges(Rect(0, 80, iw, 100));		//0  100  iw  80

   int line_bool = 15;
    for (int i = 1; i > -1; i--)
    {
        Mat div_l = roi(Rect(line_l[i]-29, (2*i+1) * 10+5 , 58, 3));
        Mat div_r = roi(Rect(line_r[i]-29, (2*i+1) * 10+5 , 58, 3));		//20+15
        vector<Point> indices_l; 
        vector<Point> indices_r; 
        if (countNonZero(div_l) != 0)
        {
            findNonZero(div_l, indices_l);
            line_l[i] += (indices_l.back().x-29);

        }
        else
        {
            line_l[i] = 30;
            //l_bool[i] -= 1;
            line_bool+= (i-2)*4;
        }
        if (countNonZero(div_r) != 0)
        {
            findNonZero(div_r, indices_r);
            line_r[i] += (indices_r[0].x-29);

        }
        else
        {
            line_r[i] = 290;
            //r_bool[i] -= 1;
            line_bool += i-2;
        }
        line_l[i] = line_l[i]<30 ? 30 : line_l[i];
        line_r[i] = line_r[i]<30 ? 30 : line_r[i];
        line_r[i] = line_r[i]>290 ? 290 : line_r[i];
        line_l[i] = line_l[i]>290 ? 290 : line_l[i];
        int midpoint_y = (int) (2*i+1) * 30 / 4 + ih/2;
        Point center_l = Point(line_l[i], midpoint_y);
        circle(img_color, center_l, 5, (0, 0, 255), -1);
        Point center_r = Point(line_r[i], midpoint_y);
        circle(img_color, center_r, 5, (0, 0, 255), -1);
    }
    /////////////////////////////////////
    if(line_bool/4 > 2)
        atan_x = (line_bool%4 == 3) ? (line_l[0]-line_l[1]+line_r[0]-line_r[1])/2 : line_l[0]-line_l[1];
    else if(line_bool%4 == 3)
        atan_x = line_r[0]-line_r[1];
    else
        atan_x = (line_l[0]-line_l[1]+line_r[0]-line_r[1])/2;
    s_angle = (atan_x/(float)atan_y)*45;
    int r_angle = (int)s_angle; 

    
    //조향각, 속도 수식. 가중치 곱하기//
	//printf("%d\t",atan_x);
	//printf("%d\n",atan_y);
    //angle = (abs(angle - p_angle)<200 ? angle : p_angle);
	resize(img_color, dstRGB, Size(320,180), 0, 0, CV_INTER_LINEAR);


	return r_angle;
}
//-----------------------------------------------------------------------------------------------

int line_tracing2(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf, int* midpoint)       //OpenCV로 흰색과 노란색을 라인트레이싱
{
    int angle;
    // 이미지 불러오기, 세팅 //
    Mat dstRGB(ih, iw, CV_8UC3, outBuf);
    Mat img_color(ih, iw, CV_8UC3, srcBuf);
    Mat img_hsv; cvtColor(img_color, img_hsv, CV_BGR2HSV);

    //노란색 검출//
    Scalar lower_white = Scalar(200, 200, 200);
    Scalar upper_white = Scalar(255, 255, 255);
    Mat  img_mask1; inRange(img_color, lower_white, upper_white, img_mask1);
    Mat img_white; bitwise_and(img_color, img_color, img_white, img_mask1);

    Scalar lower_yellow = Scalar(20, 70, 70);
    Scalar upper_yellow = Scalar(40, 255, 255);
    Mat  img_mask2; inRange(img_hsv, lower_yellow, upper_yellow, img_mask2);

    Mat img_yellow;  bitwise_and(img_color, img_color, img_yellow, img_mask2);
    Mat roi_m; addWeighted(img_yellow, 1.0, img_white, 1.0, 0.0, roi_m);

    //캐니(차선 외곽선만 검출)//
    Mat img_gray;
    cvtColor(roi_m, img_gray, CV_BGR2GRAY);
    GaussianBlur(img_gray, img_gray, Size(5, 5), 0, 0);
    Mat edges;
    Canny(img_gray, edges, 50, 150);
    //roi 잘라내기//
    int div = 4;
    int atan_x = 0, atan_y = ih * 3 / 8;
    /*for(int i =0; i < div ; i++){
    atan_x+= midpoint[i];}
    atan_x = atan_x - midpoint[3]*4;
    int p_angle = (int)(atan(atan_x/atan_y)*180/M_PI);
    atan_x = 0;
    */
    //int p_angle = (angle-1500)9/(-90);
    int offset = angle > 60 ? ih / 8 : 0;
    Mat roi = edges(Rect(0, ih / 4 + offset, iw, ih / 2));
    ih /= 2;
    for (int i = div - 1; i > -1; i--)
    {
        Mat div_l = roi(Rect(0, i * ih / div, midpoint[i], ih / div));
        Mat div_r = roi(Rect(midpoint[i], i * ih / div, iw - midpoint[i], ih / div));
        vector<Point> indices_l;
        vector<Point> indices_r;
        int avgl = 0, avgr = iw;
        if (countNonZero(div_l) != 0)
        {
            findNonZero(div_l, indices_l);
            avgl = mean(indices_l)[0];
        }
        if (countNonZero(div_r) != 0)
        {
            findNonZero(div_r, indices_r);
            avgr = mean(indices_r)[0] + midpoint[i];

        }

        midpoint[i] = (avgl + avgr) / 2;
        if (midpoint[i] > 300)
            midpoint[i] = 300;
        else if (midpoint[i] < 20)
            midpoint[i] = 20;
        int midpoint_y = i * ih / 2 / div + ih / 2;
        Point center = Point(midpoint[i], midpoint_y);
        circle(img_color, center, 5, (0, 0, 255), -1);
        //atan_x += midpoint[i];
    }
    //atan_x = atan_x - midpoint[3]*4;
    atan_x = midpoint[0] - midpoint[3];
    atan_y = ih * 3 / 8;
    if ((midpoint[0] - midpoint[1]) * (midpoint[1] - midpoint[3]) < 0)
    {
        atan_x = midpoint[1] - midpoint[3];
        atan_y = ih / 4;
        midpoint[0] = midpoint[1] > 160 ? 280 : 40;
    }
    angle = (int)(atan(atan_x / atan_y) * 180 / M_PI);
    resize(img_color, dstRGB, Size(320, 180), 0, 0, CV_INTER_LINEAR);



    return angle;
}

//-----------------------------------------------------------------------------------------------

void rotate_tracing(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf)         //회전교차로 정지선 인식 후 전진 -> 뒤에 차가 다가오면 라인트레이싱 출발
{
    int angle, speed; 

    angle = 1450;
    speed = 50;
    SteeringServoControl_Write(angle);
    DesireSpeed_Write(speed);
    EncoderCounter_Write(0);
    while (abs(EncoderCounter_Read()) < 1020)
    {

    }

}

//-----------------------------------------------------------------------------------------------

int choowol(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf)             //왼쪽 추월인지 오른쪽 추월인지 노란색 검출양으로 판별
{
    Mat imgOriginal(ih, iw, CV_8UC3, srcBuf);
    Mat img_hsv; cvtColor(imgOriginal, img_hsv, CV_BGR2GRAY);
    Rect bounds(0, 0, imgOriginal.cols, imgOriginal.rows);
    Rect r(iw * 2 / 5, ih * 1 / 3, iw * 3 / 5, ih * 2 / 3);
    Mat Roi = img_hsv(r & bounds);
    Mat imgMask; inRange(Roi, Scalar(97, 0, 0), Scalar(156, 255, 255), imgMask);   
    int dArea = countNonZero(imgMask);
    return dArea;
}

//-----------------------------------------------------------------------------------------------

int detect_traffic_light(unsigned char* srcBuf, int iw, int ih, int color_green, int ranges, int saturation_th3, int value_th3, unsigned char* outBuf) //신호등 판별
    {
        //입력 : image, width, height, red hue, yellow hue, green hue, 오차값, saturation, value
     Mat dstRGB(ih, iw, CV_8UC3, outBuf);
     Mat img_color(ih, iw, CV_8UC3, srcBuf);          //capt
     Mat img_hsv;
     Mat img_color2 = img_color.clone();
     cvtColor(img_color2, img_hsv, COLOR_BGR2HSV);
              //그냥 초기값은 hue 최댓값인 180 이상인 값을 주어 아무의미 없는 숫자를 준다.

     Vec3b lower_green1 = cv::Vec3b(color_green - ranges, saturation_th3, value_th3);
     Vec3b upper_green1 = cv::Vec3b(color_green + ranges, 255, 255);


     Mat img_mask_green;

     inRange(img_hsv, lower_green1, upper_green1, img_mask_green);              //green mask

     erode(img_mask_green, img_mask_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
     dilate(img_mask_green, img_mask_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

     dilate(img_mask_green, img_mask_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
     erode(img_mask_green, img_mask_green, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));    //green 모폴로지

            //////////////////////////////////////////////////////////////////////////////////////////////;

     vector<vector<Point> > contours;
     vector<Vec4i> hierarchy;
     cv::findContours(img_mask_green, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);      

     vector<Moments> mu(contours.size());
     vector<Point2f> mc(contours.size());

     for (int i = 0; i < contours.size(); i++)
     {
         mu[i] = moments(contours[i], false);            /// Get the moments
     }

     int cx, cy, ci;
     int times = 0;
     int width, height;

     for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);
        if (area > 80) {                                                                   
            mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);              ///  Get the mass centers:
            cx = mc[i].x;
            cy = mc[i].y;
            ci = i;
            times += 1;
         }
     }

     if (times == 1) {
        cout<<"greencheck"<<endl;
        Point cir_center = Point(cx, cy);
        circle(img_color, cir_center, 2, (0, 0, 255), -1);

        Rect rect = boundingRect(contours[ci]);
        width = rect.width;
        height = rect.height;

        rectangle(img_color, Point(cx-(width/2), cy-(height/2)), Point(cx+(width/2),cy+(height/2)), Scalar(0, 255, 0), 3);

        cout << "width" << width << endl;
        cout << "height" << height << endl;
     }

     else {
         height = 1000;
     }
    resize(img_color, dstRGB, Size(320,180), 0, 0, CV_INTER_LINEAR);
    return height;
}

//-----------------------------------------------------------------------------------------------

int detect_sudden_stop(unsigned char* srcBuf, int iw, int ih, int color_red1, int ranges, int saturation_th1, int value_th1, unsigned char* outBuf)
    {
        //input : image, width, height, red hue, yellow hue, green hue, 오차값, saturation, value
		Mat dstRGB(ih, iw, CV_8UC3, outBuf);
        Mat img_color(ih, iw, CV_8UC3, srcBuf);          //capt
        Mat img_hsv;
        Mat img_color2 = img_color.clone();
        cvtColor(img_color2, img_hsv, COLOR_BGR2HSV);

        int center_hue = 300;

        Vec3b lower_red1 = cv::Vec3b(color_red1 - 6, saturation_th1, value_th1);                  // 180 근처
        Vec3b upper_red1 = cv::Vec3b(180, 255, 255);
        Vec3b lower_red2 = cv::Vec3b(0, saturation_th1, value_th1);
        Vec3b upper_red2 = cv::Vec3b(color_red1 + 20 - 180, 255, 255);       
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        Mat img_mask_r1, img_mask_r2, img_mask_red;

        inRange(img_hsv, lower_red1, upper_red1, img_mask_r1);
        inRange(img_hsv, lower_red2, upper_red2, img_mask_r2);
        img_mask_red = img_mask_r1 | img_mask_r2;         //red mask

        erode(img_mask_red, img_mask_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        dilate(img_mask_red, img_mask_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

        dilate(img_mask_red, img_mask_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        erode(img_mask_red, img_mask_red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));        //red 모폴로지

            //////////////////////////////////////////////////////////////////////////////////////////////

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        cv::findContours(img_mask_red, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE); 
        vector<Moments> mu(contours.size());
        vector<Point2f> mc(contours.size());

        for (int i = 0; i < contours.size(); i++)
        {
            mu[i] = moments(contours[i], false);            /// Get the moments
        }

        int cx, cy, ci;

        int times = 0;

	int width, height;

	int result;
        for (int i = 0; i < contours.size(); i++) {
            int area = contourArea(contours[i]);

            if (area > 500) {                                                                   //실제로 해볼때 신호등이 80퍼센트 켜졌을 때가 몇 픽셀 이상인지는 현장에서 측정해봐야될 듯 
                mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);              ///  Get the mass centers:

                cx = mc[i].x;
                cy = mc[i].y;
		ci = i;
                times += 1;

            }
        }

        if (times == 1) {

	Rect rect = boundingRect(contours[ci]);
	width = rect.width;
	height = rect.height;

	rectangle(img_color, Point(cx-(width/2), cy-(height/2)), Point(cx+(width/2),cy+(height/2)), Scalar(0, 255, 0), 3);

            Scalar contour_center = img_color.at<Scalar>(cy, cx);
            Mat contour_center_bgr(1, 1, CV_8UC3, contour_center);                          //여기 위아래줄 오류는 안떳는데 뭔가 불안함

            Mat contour_center_hsv;
            cvtColor(contour_center_bgr, contour_center_hsv, COLOR_BGR2HSV);

            center_hue = contour_center_hsv.at<Vec3b>(0, 0)[0];

            if (center_hue >= 0 && center_hue < 6) {
                result = 3000;                               // stop = 3000, go = 4000
            }
            else if (center_hue <= 180 && center_hue > 165) {
                result = 3000;
            }
            else {
                result = 4000;
            }
        }
        else {
            center_hue = 300;
	    result = 4000;
        }

	resize(img_color, dstRGB, Size(320,180), 0, 0, CV_INTER_LINEAR);
	
	return result;
    }


}



