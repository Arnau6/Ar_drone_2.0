#include "stdafx.h"
#include "Socket_Manager.h"
#include "NavData.h"

NavData::NavData(Socket_Manager* socket_Manager, Multiple_Input_Devices* mid)
{

	imageRoll = imread("../navigation_img/face_resized.png");
	imagePitch = imread("../navigation_img/cote_resized.png");
	imageGamePad = imread("../navigation_img/Aqua_Ball_Icon_200.png");
	imageStick = imread("../navigation_img/stick.png");
	imageTurnRight = imread("../navigation_img/turnRight.png");
	imageTurnLeft = imread("../navigation_img/turnLeft.png");
	imageUp = imread("../navigation_img/up_64.png");
	imageDown = imread("../navigation_img/down_48.png");;

	_multiple_Input_Devices = mid;
	_socket_Manager = socket_Manager;
	DWORD threadID = 2;
	CreateThread(NULL, 0, thread_update_NavData,(void*)this, 0, &threadID );
}


NavData::~NavData(void)
{
}

void NavData::update_NavData()
{
	boolean debug = false;
	while (true)
	{
		// Send a request
		_socket_Manager->sendNavData((char*) "\x01\x00\x00\x00");
		
		// Receive data
		char buf[512];
		int size = _socket_Manager->receiveNavData((void*)&buf, sizeof(buf));

		//printf("%06x\n", buf[0]);
		if (size > 0 && (buf[0] == ARDRONE_NAVDATA_HEADER1 || buf[0] == ARDRONE_NAVDATA_HEADER2))
			memcpy(&navdata, buf, sizeof(NAVDATA));
		
		if(debug)
		{
			double roll = getRoll();
			cout<<setprecision(3)<<"Roll  = "<<getRoll()<<endl;
			cout<<setprecision(3)<<"Pitch = "<<getPitch()<<endl;
			cout<<setprecision(3)<<"Yaw   = "<<getYaw()<<endl;
			cout<<setprecision(3)<<"Alt   = "<<getAltitude()<<endl;
			cout<<setprecision(3)<<"Bat   = "<<getBattery()<<"%"<<endl;

			cout<<endl;

		}
		

		Sleep(30);
	}
}

DWORD WINAPI NavData::thread_update_NavData(void* Param)
{
	NavData* This = (NavData*) Param;

	This->update_NavData();

	return 0;
}

double NavData::getRoll()
{
	return navdata.phi * 0.001 ;
}

double NavData::getPitch()
{
	return navdata.theta * 0.001 ;
}

double NavData::getYaw()
{
	return navdata.psi * 0.001 ;
}

double NavData::getAltitude()
{
	return navdata.altitude * 0.001;
}

int NavData::getBattery()
{
	return navdata.vbat_flying_percentage;
}

Mat NavData::drawInstrumentation(cv::Mat imagee )
{
	Mat image;
	imagee.copyTo(image);

	Scalar color = Scalar( 120, 100, 30 );
	draw_Battery(image, color);
	draw_Altimeter(image, color);
	
	
	int y = image.size().height  - imageRoll.size().height -10; // image roll and pitch have the same size
	
	cv::Point position_roll (10, y);
	//cv::Point position_pitch (30+imageRoll.size().width, y);
	cv::Point position_pitch (position_roll.x, position_roll.y - imageRoll.size().height);
	
	
	draw_Image(image, imageRoll, position_roll,  getRoll());
	draw_Image(image, imagePitch, position_pitch,  getPitch());

	
	draw_analog_stick(image, color);
	
	return image;
}


Mat NavData::rotateImage(cv::Mat src, double angle)
{
	Mat dst;
	float div = 2.; // to avoid warning

	int len = std::max(src.cols, src.rows);
	cv::Point2f pt(len/div, len/div);
	cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);
	cv::warpAffine(src, dst, r, cv::Size(len, len), INTER_CUBIC, BORDER_REPLICATE); //BORDER_REPLICATE to erase the border

	return dst;
}

void NavData::draw_Image(cv::Mat imageSource, cv::Mat imageToAdd, cv::Point position, double angle)
{

	if(imageSource.empty())
		return;

	if(imageToAdd.empty())
		{
			cout<<"ERROR, one image does not exist";
			exit(0);
		}

	if(imageSource.size().height < imageToAdd.size().height 
		|| imageSource.size().width < imageToAdd.size().width )

	{
		cout<<"ERROR, imageToAdd is bigger than imageSource";
		exit(0);
	}
	
	cv::Mat imageToAddRotated = (angle != 0.0f)? rotateImage(imageToAdd, angle) : imageToAdd;

	Mat mask_without_white;
		
	inRange(imageToAddRotated,
		//Scalar(1.0,1.0,1.0),
		Scalar(0.0,0.0,0.0), // Black
		Scalar(254.0,255.0,255.0), //erase color 255, 255, 255 (white)
		mask_without_white);
	
	cv::Rect rect( position, imageToAddRotated.size() );
	imageToAddRotated.copyTo( imageSource( rect ), mask_without_white );
}

void NavData::draw_Battery(Mat image, Scalar color)
{
	int battery = static_cast<int>(getBattery());

	Scalar color_background = color;
	Scalar color_red = Scalar( 0, 0, 200 );
	Scalar color_green = Scalar( 0, 150, 0 );
	Scalar color_battery = (battery < 33)? color_red : color_green;

	int rect_out_height = 30, rect_out_width = 55;
	const Point rect_out_A = Point(image.size().width - (rect_out_width + 40) , 10); // en haut a gauche
	const Point rect_out_B = Point(rect_out_A.x+rect_out_width, rect_out_A.y+rect_out_height); // en bas a droite
	rectangle( image, rect_out_A, rect_out_B, color_background,-1 );

	int mini_rect_height = (rect_out_A.y-rect_out_B.y)/3
		, mini_rect_width = 7;
	const Point mini_rect_out_A = Point(rect_out_B.x , rect_out_A.y - mini_rect_height-1); // en haut a gauche
	const Point mini_rect_out_B = Point(rect_out_B.x + mini_rect_width, rect_out_A.y - mini_rect_height*2+1); // en bas a droite
	rectangle( image, mini_rect_out_A, mini_rect_out_B, color_background,-1 );

	
	int margin = 4;
	int width_in = static_cast<int>((rect_out_B.x - rect_out_A.x - margin)*battery/100.0);
	const Point rect_in_A = Point(rect_out_A.x + margin, rect_out_A.y + margin);
	const Point rect_in_B = Point(rect_out_A.x + width_in, rect_out_B.y - margin);
	rectangle( image, rect_in_A, rect_in_B, color_battery,-1 );

	ostringstream txt;
	txt<<battery <<"%";
	const Point txt_position = Point(rect_out_A.x+10, rect_out_A.y+20);
	double font_scale = 0.5;
	int thickness = 1;
	cv::putText(image,txt.str() , txt_position, NULL, font_scale,  Scalar( 200, 200, 200 ), thickness,1);
}

void NavData::draw_Altimeter(Mat image, Scalar color)
{

	int width = 30, right_margin = 47, space_inter_line = 20, reduction_inter_line = 7, nb_line = 5*2;
	double value_inter_line, altitude = getAltitude();

	//Determine l'echelle
	if(altitude < 5) value_inter_line = 0.5;
	else if(altitude < 10) value_inter_line = 1;
	else if(altitude < 25) value_inter_line = 2.5;
	else if(altitude < 50) value_inter_line = 5;
	else if(altitude < 100) value_inter_line = 10;
	else value_inter_line = 20;

	Point start = Point(image.size().width-width-right_margin, image.size().height/2 - (nb_line/2)*space_inter_line); //start.y is adapted to center the Altimeter
	Point end = Point(start.x+width , start.y);

	Point inter_start =Point(start.x+reduction_inter_line, start.y+space_inter_line);
	Point inter_end = Point(end.x-reduction_inter_line, end.y+space_inter_line);

	int thickness = 2;
	int lineType = 8;

	for (int i = 5; i >= 0; i--)
	{
		line( image, start, end, color, thickness, lineType);
		line( image, inter_start, inter_end, color, thickness, lineType);//inter line
		
		ostringstream txt;
		txt<<i*value_inter_line*2;
		const Point txt_position = Point(end.x+10, end.y+5);
		cv::putText(image,txt.str() , txt_position, NULL, 0.6, color, 2,1);

		if(i !=0) 
		{
			
			inter_start = Point(start.x+reduction_inter_line, start.y+space_inter_line);
			inter_end = Point(end.x-reduction_inter_line, end.y+space_inter_line);

			start = Point(start.x, start.y+space_inter_line*2);
			end = Point(end.x, end.y+space_inter_line*2);
		}			
	}
	
	int y_pointer = static_cast<int> (start.y - space_inter_line * (altitude/value_inter_line));

	int height_marker = 12, width_marker = 45;
	line( image, Point(start.x-10, y_pointer), Point(start.x-20, y_pointer-height_marker), color, thickness, lineType); // triangle
	line( image, Point(start.x-10, y_pointer), Point(start.x-20, y_pointer+height_marker), color, thickness, lineType);

	line( image,Point(start.x-20, y_pointer+height_marker), Point(start.x-20-width_marker, y_pointer+height_marker), color, thickness, lineType); //rectangle
	line( image,Point(start.x-20, y_pointer-height_marker), Point(start.x-20-width_marker, y_pointer-height_marker), color, thickness, lineType);
	line( image, Point(start.x-20-width_marker, y_pointer+height_marker), Point(start.x-20-width_marker, y_pointer-height_marker), color, thickness, lineType);

	ostringstream txt;
	txt<< setprecision(3) << altitude;
	cv::putText(image,txt.str() , Point(start.x-20-width_marker+5, y_pointer-height_marker+19), NULL, 0.6, color, 2,1);

}

void NavData::draw_analog_stick(Mat image, Scalar color)
{
	boolean debug = false;
	
	int radius = imageGamePad.size().width /2;
	Point position_gamePad = Point(image.size().width/2 - radius, image.size().height-radius*2 - 10);
	
	
	Point center_gamepad = Point(position_gamePad.x+radius - imageStick.size().width/2, position_gamePad.y+radius - imageStick.size().height/2);

	draw_Image(image, imageGamePad, position_gamePad,  0);

	At_Command cmd = _multiple_Input_Devices->last_command;
	if(cmd._clock +200< clock()) //obsolet command
	{
		draw_Image(image, imageStick, center_gamepad,  0);
	}
	else
	{
		if(debug)
			cout<<"x = "<<cmd._x<<endl
			<<"z = "<<cmd._z<<endl
			<<"y = "<<cmd._y<<endl
			<<"rotate = "<<cmd._rotate<<endl<<endl;


		int margin = 10;
		int x = static_cast<int>( center_gamepad.x + cmd._x*(radius - imageStick.size().width/2));
		int z = static_cast<int>( center_gamepad.y - cmd._z*(-radius + imageStick.size().height/2));
		draw_Image(image, imageStick, Point(x, z),  0);


		if(cmd._y != 0.0f)
		{
			Mat imageUpDown = (cmd._y > 0)? imageUp: imageDown;

			int margin = 20;
			Point center_up = Point(center_gamepad.x + radius + margin, center_gamepad.y + radius - margin);
			draw_Image(image, imageUpDown,center_up,  0);
		}

		if(cmd._rotate != 0.0f)
		{
			Mat imageRotate = (cmd._rotate > 0)? imageTurnRight : imageTurnLeft;

			int margin = 20;
			Point center_up = Point(center_gamepad.x - radius, center_gamepad.y + radius - margin);
			draw_Image(image, imageRotate,center_up,  0);
		}
	}
}