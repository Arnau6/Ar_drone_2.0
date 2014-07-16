#pragma once
#include "Socket_Manager.h" 
#include "At_Command.h"

class Multiple_Input_Devices
{
public:
	Multiple_Input_Devices(Socket_Manager* dcm);
	~Multiple_Input_Devices(void);
	
	void prepare_to_send(At_Command command);
	Socket_Manager* getDrone_Socket_Manager();
	At_Command last_command;

	int last_global_command_ms, last_Keyboard_command_ms, last_GamePad_command_ms, 
		last_LeapMotion_command_ms, last_automatic_command_ms;

	bool isGamePadConnected, isLeapmotionConnected;

private:
	void init_command();
	void loop_check_input();
	static DWORD WINAPI thread_GamepadController (void* Param);
	static DWORD WINAPI thread_check_input (void* Param);
	bool check_prioritary_command();

	Socket_Manager* _drone;

	At_Command Keyboard_command;
	At_Command GamePad_command;
	At_Command LeapMotion_command;
	At_Command automatic_command;
};

