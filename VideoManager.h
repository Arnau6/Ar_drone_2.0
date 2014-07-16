#pragma once

#include "stdafx.h"
#include "Socket_Manager.h"
#include "Multiple_Input_Devices.h"
#include "NavData.h"

class VideoManager
{
public:
	VideoManager(Multiple_Input_Devices *multiple_Input_Devices, boolean detectFace, boolean is_automatic_mouvement, NavData* navData, boolean useDrone_unless_PcWebcam);
	~VideoManager(void);
	

	
	/**
	* Method:		custom_and_print_frame
	*
	* Brief :		catch each image of a video stream
	*
	* Parameter:	const string videoStreamAddress : address IP of the drone
	* Parameter:	boolean detectFace : true to detect faces
	* Parameter:	boolean is_automatic_movement : true for automatic movement (detectFace must be true)
	*
	* Returns:		void 
	**/



	Mat custom_frame();
	Mat get_imgNearestHead();
	void getHSL(cv::Point p);

	Mat detectObjectByHLS(Mat frame);

	void setIsDetectedFaces( boolean detectFace );

	void setPictureBox(System::Windows::Forms::PictureBox^ PictureBox);

	void startRecording(string path);
	void stopRecording();

	bool isCorrectPath(std::string& path);

	Mat _imgNearestHead ;
	Mat lastValidFrame, lastFrameWithDetection;
	Rect roi_head;

	boolean _is_detected_Faces, _is_detected_HLS, _is_automatic_mouvement;

	int hls_hue, hls_lightness, hls_saturation, hls_ErrorMargin;
	int scale; 
	double latency_find_faces, fps;

private:

	/**
	* Method:		find_faces
	*
	* Brief :		find faces using face_cascade.
	The current image to analyze is convert in black and white 
	and is resized with scale value to enhance the  performance
	*
	* Returns:		void 
	**/
	void find_faces();
	
	/**
	* Method:		thread_find_faces
	*
	* Brief :		this thread contains find_faces() method
	it is useful to get an instant video stream. Unless,
	their is a latency between the current image (seen) and the last
	find_faces() analyse
	*
	* Parameter:	void * Param : Contains the current class
	*
	* Returns:		DWORD WINAPI 
	**/
	static DWORD WINAPI thread_find_faces (void* Param);
	
	static DWORD WINAPI thread_getFrameFromStream (void* Param);

	static DWORD WINAPI thread_custom_and_print_frame (void* Param);

	/**
	* Method:		draw_faces
	*
	* Brief :		draw a circle around each head detected 
	of the current image and show it
	*
	* Parameter:	boolean is_automatic_mouvement : if true,
	a rectangle of viewfinder is draw and the method automatic_mouvement()
	is call
	*
	* Returns:		void 
	**/
	void draw_faces(boolean is_automatic_mouvement, Mat frame);

	Rect get_roi_NearestHead( Point &center_head, int width_head, int height_head, Mat &frame );


	/**
	* Method:	automatic_mouvement
	*
	* Brief :	find the nearest head (the bigger on screen)
	if his center is outside the rectangle of viewfinder, command
	are send to the drone to adjust his position
	*
	* Returns:	void 
	**/
	void automatic_movementWithFaces(vector<Rect>::const_iterator nearest_head, Point center_nearest_head, const Point rect_point_A,const Point rect_point_B);
	
	/**
	* Method:		get_detected_faces
	*
	* Brief :		return detected_faces. As detected_faces is 
	change in a thread, method who need this variable will always
	call this method to prevent conflict (detected_faces may change between
	the start and the end of a function who need it.
	*
	* Returns:		const vector<Rect> & 
	const is useful to prevent "Vector subscript out of range"
	& is useful prevent "vector iterator incompatible"
	**/
	const vector<Rect> get_detected_faces();
	
	
	/**
	* Method:		print_Info_on_screen
	*
	* Brief :		Print fps and latency on the top right corner of the screen
	*
	* Returns:		void 
	**/
	void refresh_fps(Mat frame);

	void getFrameFromStream();

	HANDLE thread_DetectFaces;

	cv::VideoCapture vcap;
	cv::VideoWriter vWriter;

	Multiple_Input_Devices *_multiple_Input_Devices;
	NavData* _navData;

	CascadeClassifier face_cascade;
	vector<Rect> detected_faces;
	int dimension_rect_finder;
	Point nearestDetectedObject;

	int fps_start, last_automatic_movement; // time in ms
	int frame_counter;
	
	/* Important value. A low value increase the chance to find faces
	but increase the latency of drawing faces
	A good latency is under 100 ms (at least 10 refresh per second)
	*/
	int _input_type;	

	bool _is_Recording;

	
};

