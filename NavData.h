#pragma once
#include "stdafx.h"
#include "Socket_Manager.h"  
#include "Multiple_Input_Devices.h"

#define ARDRONE_NAVDATA_HEADER1      (0x55667788)
#define ARDRONE_NAVDATA_HEADER2      (0xffffff88)

//#pragma pack(push, 1)
struct NAVDATA {
	// Header
	unsigned int   header;
	unsigned int   ardrone_state;
	unsigned int   sequence;
	unsigned int   vision_defined;

	// Demo
	unsigned short tag;
	unsigned short size;
	unsigned int   ctrl_state;
	unsigned int   vbat_flying_percentage;
	float          theta;
	float          phi;
	float          psi;
	int            altitude;
	float          vx;
	float          vy;
	float          vz;

	NAVDATA():theta(0), phi(0), psi(0), altitude(0), vbat_flying_percentage(99){}
};
//#pragma pack(pop)

class NavData
{
public:
	NavData(Socket_Manager* socket_Manager, Multiple_Input_Devices* mid);
	~NavData(void);
	static DWORD WINAPI thread_update_NavData (void* Param);
	
	double getRoll();
	double getPitch();
	double getYaw();
	double getAltitude();
	int getBattery();

	Mat drawInstrumentation(cv::Mat image);

private:
	NAVDATA navdata;
	Socket_Manager* _socket_Manager;
	Multiple_Input_Devices* _multiple_Input_Devices;

	void update_NavData();
	void draw_Image(cv::Mat imageSource, cv::Mat imageToAdd, cv::Point position, double angle);
	Mat rotateImage(cv::Mat src, double angle);

	void draw_Battery(Mat image, Scalar color);
	void draw_Altimeter(Mat image, Scalar color);
	void draw_analog_stick(Mat image, Scalar color);

	Mat imageRoll, imagePitch, imageGamePad, imageStick, imageUp, imageDown, imageTurnLeft, imageTurnRight;
};

