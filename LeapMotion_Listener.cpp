#include "stdafx.h"
#include "LeapMotion_Listener.h"
#include "Multiple_Input_Devices.h"
#include "At_Command.h"

LeapMotion_Listener::LeapMotion_Listener(Multiple_Input_Devices* mid)
{
	_input_type = 2;
	_multiple_Input_Devices = mid;
}

void LeapMotion_Listener::onInit(const Controller& controller) {
	std::cout << "Waiting for LeapMotion's connection " << std::endl;
}

void LeapMotion_Listener::onConnect(const Controller& controller) {
	std::cout << "LeapMotion connected" << std::endl;
	_multiple_Input_Devices->isLeapmotionConnected = true;
}

void LeapMotion_Listener::onDisconnect(const Controller& controller) {
	//Note: not dispatched when running in a debugger.
	std::cout << "LeapMotion disconnected" << std::endl;
	_multiple_Input_Devices->isLeapmotionConnected = false;
}

void LeapMotion_Listener::onExit(const Controller& controller) {
	_multiple_Input_Devices->isLeapmotionConnected = false;
	std::cout << "Exited" << std::endl;
}

void LeapMotion_Listener::onFocusGained(const Controller& controller) {
	//std::cout << "LeapMotion started" << std::endl;
}

void LeapMotion_Listener::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void LeapMotion_Listener::onFrame(const Controller& controller) {

	boolean debug = false;
	//std::cin.get();

	const float min_roll_left = 15.0f, max_roll_left = std::numeric_limits<float>::max();
	const float min_roll_right = std::numeric_limits<float>::lowest(), max_roll_right = -15.0f;
	
	const float min_pitch_up = 25.0f, max_pitch_up = std::numeric_limits<float>::max();
	const float min_pitch_down = std::numeric_limits<float>::lowest(), max_pitch_down = -5.0f;

	const float min_y_down = 0.0f, max_y_down = 70.0f;
	const float min_y_up = 190.0f, max_y_up = std::numeric_limits<float>::max();

	const float min_x_left = std::numeric_limits<float>::lowest(), max_x_left = -90.0f;
	const float min_x_right = 90.0f, max_x_right = std::numeric_limits<float>::max();

	//const float min_yaw_left_finger = std::numeric_limits<float>::lowest(), max_yaw_left_finger = -45.0f;
	//const float min_yaw_right_finger = 10.0f, max_yaw_right_finger = std::numeric_limits<float>::max();

	
	// Get the most recent frame and report some basic information
	const Frame frame = controller.frame();
	
	if (!frame.hands().isEmpty()) 
	{
		const Hand hand = frame.hands()[0];
		const Leap::Vector normal = hand.palmNormal();
		const Leap::Vector direction = hand.direction();
	
		const float pitch = direction.pitch() * RAD_TO_DEG;
		const float roll = normal.roll() * RAD_TO_DEG;
		const float yaw = direction.yaw() * RAD_TO_DEG;

		const float y_palm = hand.palmPosition().y;
		const float x_palm = hand.palmPosition().x;

		float x_drone = 0.0f, y_drone = 0.0f, z_drone = 0.0f, turn_drone = 0.0f;

		if(y_palm>min_y_down && y_palm<max_y_down)
			y_drone = -1.0f;
		else if(y_palm>min_y_up && y_palm<max_y_up)
			y_drone = 1.0f;

		if(x_palm>min_x_left && x_palm<max_x_left)
			turn_drone = -1.0f;
		else if(x_palm>min_x_right && x_palm<max_x_right)
			turn_drone = 1.0f;

		if(pitch>min_pitch_up && pitch<max_pitch_up)
			z_drone = 1.0f;
		else if(pitch>min_pitch_down && pitch<max_pitch_down)
			z_drone = -1.0f;

		if(roll>min_roll_right && roll< max_roll_right)
			x_drone = 1.0f;
		else if(roll>min_roll_left && roll< max_roll_left)
			x_drone = -1.0f;

		/*if(roll>min_yaw_left_finger && roll<max_yaw_left_finger)
			std::cout<<"turn_left";
		else if(roll>min_yaw_right_finger && roll<max_yaw_right_finger)
			std::cout<<"turn_right";
			*/

		if(x_drone != 0.0f || y_drone != 0.0f || z_drone != 0.0f || turn_drone != 0.0f)
		{
			int _speed_drone = 10;
			At_Command _command; 


			if(x_drone !=0.0f &&  z_drone != 0.0f)
			{
				float margin = 0.25f;
				(x_drone < 0)? x_drone += margin : x_drone -= margin;
				(z_drone < 0)? z_drone += margin : z_drone -= margin;
			}

			if(y_drone != 0.0f)
				_command = At_Command(0, y_drone, 0, 0, Point(_speed_drone, 100), _input_type);
			
			else if(turn_drone != 0.0f)
				_command = At_Command(0, 0, 0, turn_drone, Point(_speed_drone, 100),  _input_type);

			else
				_command = At_Command(x_drone, y_drone, z_drone, turn_drone, Point(_speed_drone, 100),  _input_type);

			_multiple_Input_Devices->prepare_to_send(_command);

			if(debug)
			{
				if(x_drone < 0.0f)
					cout<<"Go_Left ";
				else if(x_drone > 0.0f)
					cout<<"Go_Right ";

				if(y_drone > 0.0f)
					cout<<"UP ";
				else if(y_drone < 0.0f)
					cout<<"DOWN ";

				if(z_drone > 0.0f)
					cout<<"FW ";
				else if(z_drone < 0.0f)
					cout<<"BW ";

				if(turn_drone > 0.0f)
					cout<<"turn_Right ";
				else if(turn_drone < 0.0f)
					cout<<"Turn_Left ";
				std::cout<<std::endl;
			}
		}
	}	
}
