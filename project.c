#include <signal.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <termios.h>
#include <sys/time.h>
#include <errno.h>
#include <syslog.h>

#include "util.h"

#include "display-kms.h"
#include "v4l2.h"
#include "vpe-common.h"
#include "drawing.h"
#include "car_lib.h"

#define VPE_OUTPUT_W        320
#define VPE_OUTPUT_H        180

#define TIME_TEXT_X             385 //320
#define TIME_TEXT_Y             260 //240
#define TIME_TEXT_COLOR         0xffffffff //while

extern int line_l[];
extern int line_r[];
extern float s_angle;
extern short curve;
extern unsigned short cnt, after_turnel, p_cnt;
extern short p_mode;
extern short park_cnt;
extern int direct1, direct2, dir_cnt, song_cnt;

//작업 속도 표시
static void draw_operatingtime(struct display *disp, uint32_t time)
{
	FrameBuffer tmpFrame;
	unsigned char* pbuf[4];
	char strtime[128];

	memset(strtime, 0, sizeof(strtime));

	sprintf(strtime, "%03d(ms)", time);
	
	if(get_framebuf(disp->overlay_p_bo, pbuf) == 0) {
		tmpFrame.buf = pbuf[0];
		tmpFrame.format = draw_get_pixel_foramt(disp->overlay_p_bo->fourcc);
		//FORMAT_RGB888; 
		//alloc_overlay_plane() -- FOURCC('R','G','2','4');
		tmpFrame.stride = disp->overlay_p_bo->pitches[0];
		drawString(&tmpFrame, strtime, TIME_TEXT_X, TIME_TEXT_Y, 0, TIME_TEXT_COLOR);
	}
}

//카메라에서 받아온 데이터 가공 후 원하는 함수 선택하여 실행
static int fun_select(struct display *disp, struct buffer *cambuf, int n) 
{   
	unsigned char srcbuf[VPE_OUTPUT_W*VPE_OUTPUT_H*3];
	uint32_t optime;
	struct timeval st, et;

	unsigned char* cam_pbuf[4];
	if(get_framebuf(cambuf, cam_pbuf) == 0) {
	memcpy(srcbuf, cam_pbuf[0], VPE_OUTPUT_W*VPE_OUTPUT_H*3);
	gettimeofday(&st, NULL);

	switch (n)
	{
		case 0:
		//0 출발 신호
		return start_signal(srcbuf, VPE_OUTPUT_W, VPE_OUTPUT_H, cam_pbuf[0], VPE_OUTPUT_W, VPE_OUTPUT_H);

		case 1:
		//1 차선인식(노란색 + 흰색)
		return line_tracing2(srcbuf, VPE_OUTPUT_W, VPE_OUTPUT_H, cam_pbuf[0]);

		case 2:
		//2 차선인식(노란색)
		return line_tracing(srcbuf, VPE_OUTPUT_W, VPE_OUTPUT_H, cam_pbuf[0]);

		case 3:
		{
		//3 신호등
		int traffic_result = detect_traffic_light(srcbuf, VPE_OUTPUT_W, VPE_OUTPUT_H, 60, 20, 80, 50, cam_pbuf[0]);
		return traffic_result;
		}

		case 4:
		{
        //4 sudden_stop
        int sudden_result = detect_sudden_stop(srcbuf, VPE_OUTPUT_W, VPE_OUTPUT_H, 175, 20, 160, 90);
        return sudden_result;
        }

		case 5:
		//5 회전교차교
		rotate_tracing(srcbuf, VPE_OUTPUT_W, VPE_OUTPUT_H, cam_pbuf[0]);
		break;

		case 6:
		//6 추월
		return choowol(srcbuf, VPE_OUTPUT_W, VPE_OUTPUT_H, cam_pbuf[0]);
		break;
	}
	gettimeofday(&et, NULL);
	optime = ((et.tv_sec - st.tv_sec)*1000)+ ((int)et.tv_usec/1000 - (int)st.tv_usec/1000);
	draw_operatingtime(disp, optime);
	}
}

// 영상과 센서값들을 통해 조건을 판별하여 각각의 모드 실행
int project(struct display *disp, struct buffer *cambuf, int mode, int green_num)
{
	int speed;
	int popcorn;
	int pdata, tdata1, tdata2;
	char sensor;
	unsigned char gain;
	speed = 50;

	pdata = DistanceSensor(3);
	tdata1 = DistanceSensor(2);
	tdata2 = DistanceSensor(6);
	
	/*printf("mode = %d   ", mode);
	printf("cnt = %d   ", cnt);
	printf("p_mode = %d   ", p_mode);
	printf("sensor1 = %d   ", DistanceSensor(1));
	printf("endocer = %d\n",EncoderCounter_Read());*/
	
	//-4 주차 벽 
	else if (mode == -4)
	{
		tdata1 = DistanceSensor(2);
		tdata2 = DistanceSensor(6);
		tunnel_right(tdata1, tdata2);
		if(tdata1<100 || tdata2<100) mode=-1;
	}
	//-3 출발 신호 기다리는 모드
	if(mode == -3)
	{
		
		short judge = fun_select(disp, cambuf, 0);
		if(judge == 1)
		{
			Desirespeed_Write(200);
			mode = -4;     //고가도로
			CameraYServoControl_Write(1760);
		}
		
	}
	//-2 차선인식(노란색 + 흰색) 모드
	else if (mode == -2)
    	{
        	int angle = (int)(1500 - fun_select(disp, cambuf, 1) * 70 / 9);
		if (angle > 1550){
			EncoderCounter_Write(0);
			angle = (angle > 2000) ? 2000 : angle + 300;
		}
		else if (angle < 1000){
			EncoderCounter_Write(0);
			angle = 1000;
		}
		int speed = (abs(angle - 1500) > 1) ? 100 : 100;
		SteeringServoControl_Write(angle);
		DesireSpeed_Write(speed);

		if (DistanceSensor(1) >= 1300)
		{
			mode = 13;
			DesireSpeed_Write(0);
			CameraYServoControl_Write(1600);
			CameraXServoControl_Write(2000);
			sleep(1);
			return mode;
		}
    	}
	//-1 차선인식(노란색) 모드
	else if(mode == -1)
	{	
		int angle = (int)(1500 - fun_select(disp, cambuf, 2)*70/9); 
		if (after_turnel == 0 && tdata1 > 1000 && tdata2 > 1000)
		{	
			DesiredSpeedWrite(200);
			mode = 10;
			CarLight_Write(FRONT_ON);
			after_turnel ++;
			return mode;
		}

		if(angle>1550)
		{
			EncoderCounter_Write(0);
			angle = (angle>2000)? 2000 : angle + 300;
		}		
		else if(angle<1000)
		{
			EncoderCounter_Write(0);
			angle = 1000;
		}
	
		int speed = (abs(angle-1500)>1)? 100 : 100;  

		SteeringServoControl_Write(angle);
		DesireSpeed_Write(speed);
		
		sensor = LineSensor_Read();
		printf("sensor : %d", sensor);
		if (sensor == 0 && cnt == 0)
		{
			mode = 7;
			cnt++;
			return mode;
		}
		else if (sensor == 0 && cnt == 1)
		{
			CameraYServoControl_Write(1600);
			DesireSpeed_Write(0);
			mode = 20;
		}
		if (p_mode == 1) // 주차공간 인식시 encoder를 초기화시킨다
		{
			if(pdata < 350)
			{
				popcorn = EncoderCounter_Read();
				if(popcorn < 80)
				{
					p_mode=0;
				}
				EncoderCounter_Write(0);
				p_mode = 2;
			
			}
			return mode;
		}
		
		else if (p_mode == 2) // 두번째 벽 감지
		{
			if(pdata > 800 && pdata < 2000)
			{
				mode = 4;
				return mode; 
			}
			return mode;
		}

        int sudden_red = fun_select(disp, cambuf, 4);
        if (sudden_red == 3000)
        {
            mode = 21;
            return mode;
        }
		mode = 0;
	}
	//0 주차 용 벽 감지
	else if(mode == 0 && p_cnt < 2) //주차 2번만 실행
	{
		if( pdata > 1300 && pdata < 1800)
		{
			EncoderCounter_Write(0);
			p_mode = 1;
			
		}
		mode = -1;
		
	}
	//4 평행 및 수직 주차 판단
	else if(mode == 4)  // 기록한 encoder값을 기준으로 수직/수평 주차를 판단하고 오류값은 배제시킨다
	{
		p_mode = 0;
		int park = EncoderCounter_Read();

		if(park > 700 && park < 1100) //수평주차
		{
			
			speed = (860 - EncoderCounter_Read()); // encoder값에 따라 전진,후진 구분
			if (speed > 0)
			{
				speed = 80;
			}
			else
			{
				speed = -80;
			}
           		DesireSpeed_Write(speed);
			while(EncoderCounter_Read() < 840 || EncoderCounter_Read() > 880 ) // 840~860 사이의 엔코더값까지 도달
			{
				//printf("speed = %d\n",speed);
			}
			mode = 5; 
		}	
		else if(park <= 600) //수직주차
		{
			speed = (650 - EncoderCounter_Read()); // encoder값에 따라 전진,후진 구분
			if (speed > 0)
			{
				speed = 80;
			}
			else
			{
				speed = -80;
			}
			DesireSpeed_Write(speed);
			while(EncoderCounter_Read() < 630 || EncoderCounter_Read() > 670 ) // 630~670 사이의 엔코더값까지 도달
			{

			}	
			mode = 6;
		}

		else if (park >= 1100) //일정값 이상이면 주차구역이 아니라고 판단
		{
			mode = -1;
			p_mode = 1;
		}

		else
		{
			mode = -1;
		}
	}
	//5 수평 주차 모드 p_cnt는 주행중 주차2번으로 제한, park_cnt는 수직주차 횟수 제한
	else if(mode == 5)
	{
		if(park_cnt == 0)
		{
			//EncoderCounter_Write(0);
			horizental_parking();
			park_cnt = 1;
			p_cnt += 1;
			mode = -1;
		}
		else
		{
			mode = -1;
			
		}
		
	}
	//6 수직 주차 모드
	else if(mode == 6)
	{
		
		//EncoderCounter_Write(0);
		vertical_parking();
		p_cnt += 1;		
		mode = -1;	
		
	}
	//7 회전 교차로 돌입 전 준비
	else if(mode == 7)
	{	
		DesireSpeed_Write(0);
		while (DistanceSensor(1) < 1500)
		{

		}
		fun_select(disp, cambuf, 5);
		DesireSpeed_Write(0);
		while (DistanceSensor(4) < 1400 || DistanceSensor(5) <1400)
		{

		}
		mode = -1;
	}
	//10 터널 주행 
	else if (mode == 10)
	{
		
		tunnel_right(tdata1, tdata2);
		if(tdata1<100 || tdata2<100) //터널을 통과하면 라이트 off
		{

			CarLight_Write(ALL_OFF);
			mode=-2;
		}
	}
	//13 추월 전 카메라 전환
	else if (mode == 13)
	{
		if(dir_cnt % 2 == 0)
			CameraXServoControl_Write(2000);
		else
			CameraXServoControl_Write(1000);
		sleep(1);
		mode = 15;
	}
	//14 추월 방향 판단 후 동작
	else if (mode == 14)
	{
		if(dir_cnt % 2 == 0){
			dir_cnt++;
			printf("direct1 = ");
			direct1 = fun_select(disp, cambuf, 6);
			mode = 13;
		}
		else{
			dir_cnt++;
			printf("direct2 = ");
			direct2 = fun_select(disp, cambuf, 6);
			mode = 13;
			if(direct2 > direct1){
				CameraXServoControl_Write(1500);
				printf("===========\n=         =\n=  right  =\n=         =\n===========\n");
				right_choowol();
				CameraYServoControl_Write(1760);
				mode = -1;
				return mode;
			}
			else{
				CameraXServoControl_Write(1500);
				printf("==========\n=        =\n=  left  =\n=        =\n==========\n");
				left_choowol();
				CameraYServoControl_Write(1760);
				mode = -1;
				return mode;
			}
		}
	}
	//15 카메라 프레임 조정
	else if (mode == 15)
	{
		if(song_cnt > 35){
			mode = 14; song_cnt = 0;}
		else
			song_cnt++;			
	}
	//20 신호등 판별
	else if (mode == 20)
	{
		int green_hue;
		int total_return;

		int result_color = fun_select(disp, cambuf, 3);

		if (result_color == 1000) {
			green_num = 0;
			green_hue = 200;
		}
		else if (result_color >= 0 && result_color < 100) {
			green_num = green_num + 1;
			green_hue = result_color;
		}
		total_return = green_num + (green_hue*10);
		if (green_num == 1){
			printf("2sec wait to make delay checking green");
			sleep(2);
		}

		return total_return;
	}
	//21 돌발정지
	else if (mode == 21)
	{
		int angle = 1500;
		int speed = 0;
		SteeringServoControl_Write(angle);
		DesireSpeed_Write(speed);

		int sudden_red = fun_select(disp, cambuf, 4);

		if (sudden_red == 3000)
		{
			mode = 21;
		}

		else if (sudden_red == 4000)
		{
			mode = -1;
		}
	}
    return mode;
}
