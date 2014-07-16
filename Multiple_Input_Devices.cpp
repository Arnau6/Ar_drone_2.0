#include "stdafx.h"
#include "Multiple_Input_Devices.h"
#include "GamepadController.h"
#include "LeapMotion_Listener.h"
#include "At_Command.h"

Multiple_Input_Devices::Multiple_Input_Devices(Socket_Manager* dcm)
{
	isGamePadConnected = isLeapmotionConnected = false;

	last_global_command_ms = 0;
	last_Keyboard_command_ms = 0;
	last_GamePad_command_ms = 0;
	last_LeapMotion_command_ms = 0;
	last_automatic_command_ms = 0;

	init_command();
	_drone = dcm;
	
	DWORD threadID_GP = 3, threadID_input = 4; // 0 is for faceDetector, 1 getFrameFromStream, 2 custom_and_print_frame
	CreateThread(NULL, 0, thread_GamepadController,(void*)this, 0, &threadID_GP );

	CreateThread(NULL, 0, thread_check_input,(void*)this, 0, &threadID_input );
	//loop_check_input();

}


Multiple_Input_Devices::~Multiple_Input_Devices(void)
{
}

DWORD WINAPI Multiple_Input_Devices::thread_GamepadController(void* Param)
{
	Multiple_Input_Devices* This = (Multiple_Input_Devices*) Param;
	GamepadController *gc = new GamepadController(This);

	return 0;
}

DWORD WINAPI Multiple_Input_Devices::thread_check_input(void* Param)
{
	Multiple_Input_Devices* This = (Multiple_Input_Devices*) Param;
	This->loop_check_input();

	return 0;
}

bool Multiple_Input_Devices::check_prioritary_command()
{

	if(Keyboard_command.isAviable && Keyboard_command._prioritary_command.find("AT")==0)
	{
		_drone->sendCmd((char*) Keyboard_command._prioritary_command.c_str());
		return true;
	}
	else if(GamePad_command.isAviable && GamePad_command._prioritary_command.find("AT")==0)
	{
		_drone->sendCmd((char*) GamePad_command._prioritary_command.c_str());
		return true;
	}

	else if(LeapMotion_command.isAviable && LeapMotion_command._prioritary_command.find("AT")==0)
	{
		_drone->sendCmd((char*) LeapMotion_command._prioritary_command.c_str());
		return true;
	}

	else if(automatic_command.isAviable && automatic_command._prioritary_command.find("AT")==0)
	{
		_drone->sendCmd((char*) automatic_command._prioritary_command.c_str());
		return true;
	}

	return false;
}

void Multiple_Input_Devices::loop_check_input()
{
	// Priority command : keyboard > GamePad > LeapMotion > automatic
	// an inferiors command must wait (difftime + last superior command) to be valid
	bool debug = false;

	LeapMotion_Listener listener = LeapMotion_Listener(this);
	Controller controller;
	controller.setPolicyFlags(Controller::POLICY_BACKGROUND_FRAMES);
	// Have the sample listener receive events from the controller
	controller.addListener(listener);

	int difftime = 1500;
	int no_command = 0;
	int sequence_number = 2;

	while (true)
	{
		if(clock() - last_global_command_ms < 100) // max command send per second = 10 (1000/100)
			continue;

		if (/*Keyboard_command.find("AT")==0 || GamePad_command.find("AT")==0 || LeapMotion_command.find("AT")==0 || automatic_command.find("AT")==0 || */check_prioritary_command())
		{
			sequence_number = 2;
			last_global_command_ms = clock();
			init_command();
			continue;
		}
		//else  cout <<endl<<"-----"<<GamePad_command.c_str()<<endl;

		if(Keyboard_command.isAviable)
		{

			_drone->sendCmd(Keyboard_command.getConstructed_PCMD_command(sequence_number));

			if(debug) cout <<"KB  : "<<Keyboard_command.getConstructed_PCMD_command(sequence_number)<<endl;

			last_command = Keyboard_command;
			last_Keyboard_command_ms = last_global_command_ms = clock();
			init_command();
			sequence_number++;
		}

		else if(GamePad_command.isAviable && (clock() - last_Keyboard_command_ms > difftime))
		{

			_drone->sendCmd(GamePad_command.getConstructed_PCMD_command(sequence_number));

			if(debug) cout <<"PAD : "<<GamePad_command.getConstructed_PCMD_command(sequence_number)<<endl;

			last_command = GamePad_command;
			last_GamePad_command_ms = last_global_command_ms = clock();
			init_command();
			sequence_number++;
		}

		else if(LeapMotion_command.isAviable && (clock() - last_Keyboard_command_ms > difftime) && (clock() - last_GamePad_command_ms > difftime))
		{
			_drone->sendCmd(LeapMotion_command.getConstructed_PCMD_command(sequence_number));

			if(debug) cout <<"LM  : " <<LeapMotion_command.getConstructed_PCMD_command(sequence_number)<<endl;

			last_command = LeapMotion_command;
			last_LeapMotion_command_ms = last_global_command_ms = clock();
			init_command();
			sequence_number++;
		}

		else if(automatic_command.isAviable && (clock() - last_Keyboard_command_ms > difftime) && (clock() - last_GamePad_command_ms > difftime)
			&& (clock() - last_LeapMotion_command_ms > difftime))
		{
			_drone->sendCmd(automatic_command.getConstructed_PCMD_command(sequence_number));

			if(debug) cout <<"AC  : "<<automatic_command.getConstructed_PCMD_command(sequence_number)<<endl;

			last_command = automatic_command;
			last_automatic_command_ms = last_global_command_ms = clock();
			init_command();
			sequence_number++;
		}
		else
		{
			//The drone must received at least 1 command every 2 sec to not reset the video stream
			if(clock() - last_global_command_ms > 1500)
			{
				
				ostringstream oss;
				oss<<"AT*PCMD="<<sequence_number<<",1,0,0,0,0\r\n";
				_drone->sendCmd((char*) oss.str().c_str());

				if(debug) cout <<"Void : "<<oss.str()<<endl;

				last_global_command_ms = clock();
				sequence_number++;
			}
				
		}
	}
}

void Multiple_Input_Devices::init_command()
{
	Keyboard_command.isAviable = false;
	GamePad_command.isAviable = false;
	LeapMotion_command.isAviable = false;
	automatic_command.isAviable = false;
}
void Multiple_Input_Devices::prepare_to_send(At_Command command)
{
	/*
	 *	input_type info
	 *	0 = Keyboard
	 *	1 = GamePad
	 *	2 = LeapMotion
	 *	3 = automatic
	 */

	//the latest command of each type must be saved (cf loop_check_input)
	switch (command._input_type)
	{
	case 0 : 
		Keyboard_command = command;
		
		break;

	case 1 : 
		GamePad_command = command;
		
		break;

	case 2 : 
		LeapMotion_command = command;
		
		break;

	case 3 : 
		automatic_command = command;
		
		break;

	default:
		cout<<"Wrong input_type in Multiple_Input_Devices::prepare_to_send method"<<endl;
		system("pause");
		break;
	}
}

Socket_Manager* Multiple_Input_Devices::getDrone_Socket_Manager()
{
	return _drone;
}



