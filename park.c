#include "car_lib.h"
#include <stdio.h>
int angle, speed, mode; 


void vertical_parking(void)
{
	
	printf("1");

	angle = 1000;
	speed = -50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 1100)
	{
		printf("%d\n",EncoderCounter_Read());
	}
	angle = 1500;
	speed = -50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 600)
	{

	}

	angle = 1500;
	speed = 0;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	sleep(4);

	angle = 1500;
	speed = 50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 600)
	{

	}

	angle = 1000;
	speed = 50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 1100)
	{

	}

	angle = 1500;
	speed = 50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 500)
	{

	}

	mode = -1;
}

void horizental_parking(void)
{
	

	angle = 1000;
	speed = -50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 1100)
	{

	}

	angle = 1500;
	speed = 30;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 100)
	{

	}


	angle = 2000;
	speed = -50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 800)
	{

	}


	angle = 2000;
	speed = 0;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	sleep(3);
	

	
	angle = 2000;
	speed = 50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 750)
	{
		
	}

	angle = 1500;
	speed = -30;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 100)
	{
		
	}


	angle = 1000;
	speed = 50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 1000)
	{

	}

	angle = 1500;
	speed = 50;
	SteeringServoControl_Write(angle);
	DesireSpeed_Write(speed);

	EncoderCounter_Write(0);

	while (abs(EncoderCounter_Read()) < 600)
	{

	}

	mode = -1;

}

void left_choowol(void) {
    //채워야함
}

void right_choowol(void) {
    //채워야함
}


