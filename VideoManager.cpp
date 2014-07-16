#include "stdafx.h"
#include "VideoManager.h"
#include "At_Command.h"

const String face_cascade_name = "haarcascade_frontalface_alt.xml", window_name = "Ar Drone streaming", window_FaceName = "Face Detected";

VideoManager::VideoManager(Multiple_Input_Devices* multiple_Input_Devices, boolean IsDetectedFace, boolean is_automatic_mouvement, NavData* navData, boolean useDrone_unless_PcWebcam)
{
	_input_type = 3;
	//lastValidFrame.initEmpty() ;
	hls_hue = hls_saturation = hls_lightness = 0;
	hls_ErrorMargin = 10;
	

	_is_Recording = false;
	_is_detected_HLS = false;

	_multiple_Input_Devices = multiple_Input_Devices;
	_navData = navData,
	fps_start = clock();
	latency_find_faces = 0, frame_counter=0;
	scale = 3; 
	
	dimension_rect_finder = (useDrone_unless_PcWebcam)?500: 300;

	detected_faces.reserve(100);

	_is_automatic_mouvement = is_automatic_mouvement;
	
	//open the video stream and make sure it's opened
	if(useDrone_unless_PcWebcam)
	{
		if(!vcap.open(_multiple_Input_Devices->getDrone_Socket_Manager()->getVideoStreamAddress())) //drone camera
		{
			cout << "impossible to connect to the video stream" << endl;
			return;
		}
	}
	else
	{
		if(!vcap.open(CV_CAP_ANY)) //use webcam to debug
		{
			cout << "impossible to connect to the video stream" << endl;
			return;
		}
	}
	
	//Load the cascades to detect faces
	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); exit(0); };

	_is_detected_Faces = true;
	DWORD threadID = 0;
	thread_DetectFaces = CreateThread(NULL, 0, thread_find_faces,(void*)this, 0, &threadID );
	setIsDetectedFaces(IsDetectedFace);
	

	DWORD threadID_2 = 1;
	CreateThread(NULL, 0, thread_getFrameFromStream,(void*)this, 0, &threadID_2 );

	//threadID = 2;
	//CreateThread(NULL, 0, thread_custom_and_print_frame,(void*)this, 0, &threadID );

	//voir image.zeros pour garder le ratio
	//cvNamedWindow(window_name.c_str(), CV_WINDOW_KEEPRATIO);
	//cvNamedWindow(window_name.c_str(), CV_WINDOW_NORMAL);
	//cvSetWindowProperty(window_name.c_str(), CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
}


VideoManager::~VideoManager(void)
{

}

void VideoManager::getHSL(cv::Point point)
{
	if(lastValidFrame.size().width < point.x || lastValidFrame.size().height < point.y)
		return;

	Mat  imgHLS;
	cvtColor(lastValidFrame, imgHLS, CV_BGR2HLS);
	Vec3b intensity = imgHLS.at<Vec3b>(point);

	hls_hue = intensity.val[0];
	hls_lightness = intensity.val[1];
	hls_saturation = intensity.val[2];
	//cout<<"h="<<hls_hue<<" l="<<hls_lightness<<" s="<<hls_saturation<<endl;
}

Mat VideoManager::detectObjectByHLS(Mat frame)
{
	
	Mat imgHLS,imgResult;

	cvtColor(lastValidFrame, imgHLS, CV_BGR2HLS);

	cv::inRange(imgHLS, Scalar(hls_hue - hls_ErrorMargin, 0, hls_saturation - hls_ErrorMargin), Scalar(hls_hue + hls_ErrorMargin, 255, hls_saturation + hls_ErrorMargin), imgResult);
	//cv::GaussianBlur(imgResult, imgResult, cv::Size(9,9), 1.5);

	if(imgResult.empty())
	{
		Mat imgNULL;
		lastFrameWithDetection = imgNULL;
	}
	else
	{
		int x_gravity = 0;
		int y_gravity = 0;
		int countGoodPixel = 0;
		
		lastFrameWithDetection = imgResult;

		for(int i=0; i<lastFrameWithDetection.rows;i++)
		{
			uchar* rowi = lastFrameWithDetection.ptr/*<uchar>*/(i);
			for(int j=0; j<lastFrameWithDetection.cols; j++)
			{
				if(rowi[j] == 255)// a white pixel indicate a detection.
				{
					//check neighbor
					int countPixel_Neighbors_In_A_Square = 0;
					int square_research = 8;
					int x_start = (i-square_research < 0)? 0: i-square_research;
					int y_start = (j-square_research < 0)? 0: j-square_research;

					int x_end = (i+square_research > (lastFrameWithDetection.rows-1))? lastFrameWithDetection.rows: i+square_research;
					int y_end = (j+square_research > (lastFrameWithDetection.cols-1))? lastFrameWithDetection.cols: j+square_research;
					 
					for (int k = x_start; k < x_end; k++)
					{
						for (int l = y_start; l < y_end; l++)
						{
							if(lastFrameWithDetection.ptr/*<uchar>*/(k)[l] == 255)
								countPixel_Neighbors_In_A_Square++;
						}
					}
					//cout<<countGoodPixel<<endl;
					if(countPixel_Neighbors_In_A_Square>4)
					{
						rowi[j] = 180;//Green
						y_gravity += i;
						x_gravity += j;
						countGoodPixel ++;
					}
						
					else
						rowi[j] = 220;//red
				}				
			}
		}

		if(countGoodPixel > 10)
		{
			//cout << countGoodPixel <<endl<< x_gravity/countGoodPixel <<endl<< y_gravity/countGoodPixel <<endl<<endl;
			Point centerGravity(x_gravity/countGoodPixel, y_gravity/countGoodPixel);
			circle(frame, centerGravity, 20, Scalar( 255, 0, 0 ), -1, 8);// centre 
		}
		
		//imshow("HSL", lastFrameWithDetection);
	}
	return lastFrameWithDetection;
}

bool VideoManager::isCorrectPath(std::string& path)
{
	if (FILE *file = fopen(path.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	else
		return false;
}

void VideoManager::startRecording(string path)
{
	int i = 1;
	string pathChecked;
	while (true)
	{
		ostringstream pathToCheck;
		pathToCheck<<path<<"\\Video_"<<i<<".mpeg";

		//To not erase data
		if(isCorrectPath(pathToCheck.str()) == false)
		{
			pathChecked = pathToCheck.str();
			break;
		}
		i++;
	}


	int height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);

	int codec = CV_FOURCC('P','I','M','1');
	int fps = 20;
	Size frameSize (width, height);
	bool withColor = true;
	
	vWriter = VideoWriter(pathChecked, codec, fps, frameSize, withColor);
	_is_Recording = true;
}

void VideoManager::stopRecording()
{
	_is_Recording = false;
	vWriter.release();
}

void VideoManager::setIsDetectedFaces( boolean updateIsDetectedFaces )
{
	//_is_detected_Faces must be init to true a first time in the constructor

	if(!_is_detected_Faces && updateIsDetectedFaces)
	{
		ResumeThread(thread_DetectFaces);
	}

	else if(_is_detected_Faces && !updateIsDetectedFaces)
	{
		SuspendThread(thread_DetectFaces);
		detected_faces.clear();
	}
	_is_detected_Faces = updateIsDetectedFaces;
}

void VideoManager::getFrameFromStream()
{
	Mat frame;
	
	while (true)
	{
		vcap.read(frame);
		while(frame.empty())
		{
			cout<<"reload stream"<<endl;
			vcap.open(_multiple_Input_Devices->getDrone_Socket_Manager()->getVideoStreamAddress());
			vcap.read(frame);
		}
		lastValidFrame = frame;
	}	
}


Mat VideoManager::custom_frame()
{

	Mat frame ;
	lastValidFrame.copyTo(frame);

	if(frame.empty())
		return frame;

	++frame_counter;

	refresh_fps(frame);
	
	frame = _navData->drawInstrumentation(frame);

	if(_is_detected_Faces){
		draw_faces(_is_automatic_mouvement, frame);
	}
	else if(_is_detected_HLS)
	{
		detectObjectByHLS(frame);
	}

	

	if(cv::waitKey(10) == 'q') 
	{
		string _command = "AT*REF=1,290717696\r\n";// Atterissage
		_multiple_Input_Devices->getDrone_Socket_Manager()->sendCmd((char*) _command.c_str());
		exit(0);
	}

	if(_is_Recording)
		vWriter.write(frame);

	return frame;
}

Mat VideoManager::get_imgNearestHead()
{

	Mat frame ;
	_imgNearestHead.copyTo(frame);
	return frame;
}

DWORD WINAPI VideoManager::thread_find_faces (void* Param)
{
	VideoManager* This = (VideoManager*) Param;
	time_t latency_start = NULL;
	//cout<<"-----------------------------"<<endl<<"+++++++++++++++++++++++++++++++++"<<endl;
	while (true)
	{
		int start = clock();
		This->find_faces();		
		This->latency_find_faces = clock()-start;
	}

	return 0;
}

DWORD WINAPI VideoManager::thread_getFrameFromStream (void* Param)
{
	VideoManager* This = (VideoManager*) Param;
	This->getFrameFromStream();

	return 0;
}

DWORD WINAPI VideoManager::thread_custom_and_print_frame (void* Param)
{
	VideoManager* This = (VideoManager*) Param;
	while (true)
	{
		Mat current_frame = This->custom_frame();
		
		//-- Show what you got
		if(!current_frame.empty())
			imshow( window_name, current_frame );
	}
	

	return 0;
}

void VideoManager::find_faces()
{

	Mat frame ;
	lastValidFrame.copyTo(frame);

	if(frame.empty())
		return;

	Mat frame_gray_small = frame;

	//Useful to enhance latency but decreses the chances to detect a distant face
	resize(frame_gray_small, frame_gray_small, Size(frame_gray_small.size().width/scale, frame_gray_small.size().height/scale), 0, 0, CV_INTER_LINEAR);

	cvtColor( frame_gray_small, frame_gray_small, CV_BGR2GRAY );
	equalizeHist( frame_gray_small, frame_gray_small ); // ameliore le rendu

	//prevent "vector iterator incompatible"
	vector<Rect> new_facees(100);

	//cout<<"detect 1";
	face_cascade.detectMultiScale( frame_gray_small, new_facees, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
	//cout<<" 2"<<endl;
	detected_faces = new_facees;
}

const vector<Rect> VideoManager::get_detected_faces(){
	// const is useful to prevent "Vector subscript out of range"
	// & is useful prevent "vector iterator incompatible"
	vector<Rect> current_detected_faces(100);
	//current_detected_faces.reserve(100);

	//cout << "A0.2 ";
	//try
	//{
		
		current_detected_faces = detected_faces;
		
	/*}
	catch (...)
	{
		cout<<"++++++++++++++++++"<<endl<<"++++++++++++++++++"<<endl<<"++++++++++++++++++"<<endl<<"++++++++++++++++++"<<endl<<"++++++++++++++++++"<<endl<<"++++++++++++++++++"<<endl<<"++++++++++++++++++"<<endl<<"++++++++++++++++++"<<endl<<"++++++++++++++++++"<<endl<<"++++++++++++++++++"<<endl;
		system("pause");
		return static_cast<vector<Rect>>(NULL);
	}
	*/
	//cout << "A0.3 ";
	return current_detected_faces;
}


void VideoManager::draw_faces(boolean is_automatic_mouvement, Mat frame)
{	

	//cout << "A0.1 ";
	const vector<Rect> current_detected_faces = get_detected_faces();
	//cout << "A0.4 ";
	Point center_head = Point(); // init to null
	Point center_nearest_head = Point();

	if(current_detected_faces.empty())
	{
		Mat imgNULL;
		lastFrameWithDetection = imgNULL;
	}

	else
	{	
		//prevent "vector iterator incompatible"
		//cout<<"A1 ";
		int head_size = 0;
		vector<Rect>::const_iterator matchIter, nearest_head;

		for (matchIter = current_detected_faces.cbegin(); matchIter != current_detected_faces.cend(); ++matchIter)
		{
			//the nearest head is take (the bigger)
			int current_head_size = static_cast<int>(matchIter->height*0.6*(scale*4));
			if(head_size < current_head_size){
				nearest_head = matchIter;
				head_size = current_head_size;

				center_head = Point( static_cast<int>(nearest_head->x*scale + nearest_head->width*0.5*scale), static_cast<int>(nearest_head->y*scale + nearest_head->height*0.5*scale) );
				center_nearest_head = center_head;
				center_nearest_head = center_head;
				cout<<"OK = "<<center_nearest_head<<endl;
			}
		}

		int width_head = static_cast<int>(nearest_head->width*0.4*scale);
		int height_head = static_cast<int>(nearest_head->height*0.6*scale);
		center_head = Point( static_cast<int>(nearest_head->x*scale + nearest_head->width*0.5*scale), static_cast<int>(nearest_head->y*scale + nearest_head->height*0.5*scale) );


		Rect roi = get_roi_NearestHead(center_head, width_head, height_head, frame);
		if(roi.width > 0)
			lastFrameWithDetection = lastValidFrame(roi);

		//getImg_NearestHead(center_head, width_head, height_head, frame).copyTo(_imgNearestHead);
		//imshow( window_FaceName, _imgNearestHead );

		for (matchIter = current_detected_faces.cbegin(); matchIter != current_detected_faces.cend(); ++matchIter)
		{
			center_head = Point( static_cast<int>(matchIter->x*scale + matchIter->width*0.5*scale), static_cast<int>(matchIter->y*scale + matchIter->height*0.5*scale) );
			ellipse( frame, center_head, Size( static_cast<int>(matchIter->width*0.4*scale), static_cast<int>(matchIter->height*0.6*scale)), 0, 0, 360, Scalar( 255, 0, 0 ), 4, 8, 0 );// contour d'une tete
			circle(frame, center_head, 3, Scalar( 255, 0, 0 ), -1, 8);// centre d'une tete
			//cout<<head_size<<endl;
		}
		//cout<<"A2 ";

		//Draw the nearest head in an other color
		ellipse( frame, center_nearest_head, Size( width_head, height_head ), 0, 0, 360, Scalar( 255, 255, 0 ), 4, 8, 0 );// contour d'une tete
		circle(frame, center_nearest_head, 3, Scalar( 255, 255, 0 ), -1, 8);// centre d'une tete

		if (is_automatic_mouvement)
		{
			// rectangle of viewfinder use to determine automatic movement
			const Point rect_point_A = Point( (frame.size().width - dimension_rect_finder/2) / 2, (frame.size().height - dimension_rect_finder/2) / 2); // en haut a gauche
			const Point rect_point_B = Point( (frame.size().width + dimension_rect_finder/2) / 2, (frame.size().height + dimension_rect_finder/2) / 2); // en bas a droite
			rectangle( frame, rect_point_A, rect_point_B, Scalar( 0, 0, 255 ),1 );

			//cout << "rect_point_A"<<rect_point_A<< " - rect_point_B"<<rect_point_B<< " - center_nearest_head"<<center_nearest_head;
			automatic_movementWithFaces(nearest_head, center_nearest_head, rect_point_A, rect_point_B);
		}
	}
		
}

Rect VideoManager::get_roi_NearestHead( Point &center_head, int width_head, int height_head, Mat &frame )
	{
		/*
		p0 ---- P1
		|		|
		|		|
		p3 ---- p2
		*/

		int margin = 20;

		Point p0 (center_head.x - width_head - margin, center_head.y - height_head - margin - 20); // -20 for the hair
		Point p1 (center_head.x + width_head + margin, center_head.y - height_head + margin);
		//Point p2 (center_head.x + width_head, center_head.y + height_head);
		Point p3 (center_head.x - width_head - margin, center_head.y + height_head );

		if(p0.x<0) 
			p0.x = 0;

		if(p0.y<0) 
			p0.y = 0;

		if(p1.x > frame.size().width)
			p1.x = frame.size().width;

		if(p1.y<0) 
			p1.y = 0;

		if(p3.x <0)
			p3.x = 0;

		if(p3.y > frame.size().height)
			p3.y = frame.size().height;


		Rect roi(	p0.x, p0.y,
					p1.x - p0.x,
					p3.y - p0.y);

		//Mat imgNearestHead = frame(roi);

		return roi;
	}

void VideoManager::refresh_fps(Mat frame)
{
	//Stop the clock and show FPS
	double sec = (clock() - fps_start) / 1000.0;
	fps = frame_counter/sec;

	if(clock() > fps_start + 1000.0) // reset fps every sec
	{
		fps_start = clock(); //Start the clock
		frame_counter= 0;
	}

	/*
	//print info on video stream
	stringstream text;
	text << "FPS = " << setprecision(2)<< fps;
	Point position = Point(10, 30);
	int size =1;
	int thickness = 1;
	double font_scale = 0.5;
	cv::putText(frame,text.str() , position, NULL, font_scale,  Scalar( 0, 255, 0 ), thickness,1);

	if(_is_detected_Faces)
	{
		ostringstream oss;
		oss << "Latency = "<<latency_find_faces;
		cv::putText(frame,oss.str() , Point(position.x, position.y+15), NULL, font_scale,  Scalar( 0, 255, 0 ), thickness,1);
	}
	*/
}

void VideoManager::automatic_movementWithFaces(vector<Rect>::const_iterator nearest_head, Point center_nearest_head, const Point rect_point_A, const Point rect_point_B)
{	
	//cout<<"B1 ";
	boolean debug = false;
	
	//string one_iee754_value		= "1065353216";  //1
	//string neg_one_iee754_value = "-1082130432"; //-1

	float x = 0.0f, y =0.0f, forward_backword = 0.0f;

	double head_size = nearest_head->height*0.6*(scale*4);

	//int max_head_size= 650, min_head_size=500; //for webcam
	int max_head_size= 450, min_head_size=300; //for Drone

	if(head_size > max_head_size)
	{
		forward_backword = 1;
		if(debug)cout<<"recule "<< head_size<< endl;
	}
		
	else if(head_size < min_head_size)
	{
		forward_backword = -1;
		if(debug)cout<<"avance"<< head_size<< endl;
	}

	// A : en haut a gauche
	// B : en bas a droite

	// la gauche et la droite sont inversé sur les images d'une camera
	if(center_nearest_head.x < rect_point_A.x)
	{
		x = -1; 
		if(debug)cout<<"G ";
	}

	else if(center_nearest_head.x > rect_point_B.x)
	{
		x = 1;
		if(debug)cout<<"D ";
	}
		

	if(center_nearest_head.y < rect_point_A.y)
	{
		y = 1;
		if(debug)cout<<"H ";
	}
		
	else if(center_nearest_head.y > rect_point_B.y)
	{
		y = -1;
		if(debug)cout<<"B";
	}
		
	cout<<endl;

	int _speed_drone_x = 3;
	int _speed_drone_y = 25;

	if(x != 0 || y != 0  || forward_backword != 0 )
	{
		At_Command _command; 
		_command = At_Command( x, y, forward_backword, 0, Point(_speed_drone_x, _speed_drone_y), _input_type);

		_multiple_Input_Devices->prepare_to_send(_command);
		if(debug)
		{
			cout<<"x="<<x<<" y="<<y <<" fb="<<forward_backword<<endl;
		}
	}
	last_automatic_movement = clock();
	//cout<<"B2"<<endl<<endl;
}

