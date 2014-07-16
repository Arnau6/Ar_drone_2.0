#include "stdafx.h"
#include "Multiple_Input_Devices.h"
#include "GamepadController.h"
#include "At_Command.h"

GamepadController::GamepadController(Multiple_Input_Devices* mid)
{
	_input_type = 1;
	_multiple_Input_Devices = mid;
	checkInput();
}

GamepadController::~GamepadController()
{
}

void GamepadController::checkInput()
{
	bool msg_wait_for_gamepad = true, msg_first_parseinput = true;
	_sequence_number = 0;
	_speed_drone = 10;
	memset(&_state, 0, sizeof(XINPUT_STATE)); //initialise la variable

	while(true)
	{
		//Sleep(40);
		if (!XInputGetState(0, &_state) == ERROR_SUCCESS) // Test si une manette est branché, 0 correspond au joueur 1
		{
			if(msg_wait_for_gamepad) // to print the message one time
			{
				cout << "Veuillez brancher une manette"<<endl;
				_multiple_Input_Devices->isGamePadConnected = false;

				msg_wait_for_gamepad = false;
				msg_first_parseinput = true;
			}		
		}
		else{
			if(msg_first_parseinput) // to print the message one time
			{
				cout << "Manette activee"<<endl;
				_multiple_Input_Devices->isGamePadConnected = true;

				msg_first_parseinput = false;
				msg_wait_for_gamepad = true;
			}
			parseInput();
		}
			
	}
}


void GamepadController::parseInput()
{

	bool debug = false;

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_START){
		
		_command = At_Command("AT*REF=1,290718208\r\n", _input_type);// Decollage
		_multiple_Input_Devices->prepare_to_send(_command);
		_sequence_number = 2;

		if(debug)
		{
			cout<< "START ";
			cout<<_command._prioritary_command<<endl;
		}
		
		return;
	}

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK){
		_command = At_Command("AT*REF=1,290717952\r\n", _input_type);// Reset
		_multiple_Input_Devices->prepare_to_send(_command);
		_sequence_number = 2;

		if(debug)
		{
			cout<< "Back ";
			cout<<_command._prioritary_command<<endl;
		}
		
		return;
	}

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_X){
		_command = At_Command("AT*REF=1,290717696\r\n", _input_type);// Atterissage
		_multiple_Input_Devices->prepare_to_send(_command);
		_sequence_number = 2;

		if(debug)
		{
			cout<< "X ";
			cout<<_command._prioritary_command<<endl;
		}
		
		return;
	}


	float y = 0.0f;
	float x;
	float z;


	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_A){ 
		/*_command = string("AT*PCMD=") + to_string(_sequence_number) + string(",1,0,0,") + get_Float_value_IEEE754(-1) + string(",0\r\n");
		_drone->prepare_to_send(_command, 1);
		_sequence_number++;*/
		y =  -1.0f;

		if(debug)
			cout<< "A ";
		//cout<<_command<<endl;
	}

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_B){
		if(debug)
			cout<< "B ";
	}

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y){

		/*_command = string("AT*PCMD=") + to_string(_sequence_number) + string(",1,0,0,") + get_Float_value_IEEE754(1) + string(",0\r\n");
		_drone->prepare_to_send(_command, 1);
		_sequence_number++;*/
		 y =  1.0f;
		 if(debug)
			cout<< "Y ";
		//cout<<_command<<endl;
	}

	/*
	 *Left thumbstick x-axis value. Each of the thumbstick axis members is a signed value between -32768 and 32767 
	 *describing the position of the thumbstick. A value of 0 is centered. 
	 *Negative values signify down or to the left. Positive values signify up or to the right.
	 */
	x = _state.Gamepad.sThumbLX;
	z = -_state.Gamepad.sThumbLY;
	(x<0)?x /= 32768 : x /= 32767;
	(z<0)?z /= 32768 : z /= 32767;

	if (x<0.2 && x >-0.2) // DeadZone du stick
	{
		x = 0.0f;
	}
	if (z<0.2 && z >-0.2) // DeadZone du stick
	{
		z = 0.0f;
	}

	if (!(x<0.2 && x >-0.2) || !(z<0.2 && z >-0.2)) // DeadZone du stick
	{
		if(debug)
			cout<<"stick left ";
	}

	float rotate = _state.Gamepad.sThumbRX;
	(rotate<0)?rotate /= 32768 : rotate /= 32767;

	if (!(rotate<0.2 && rotate >-0.2)) // DeadZone du stick
	{
		if(debug)
			cout<<"rotate ";
	}
	else
		rotate = 0.0f;



	if (x != 0 || z != 0 || y != 0 || rotate != 0)
	{
		_command = At_Command(x, y, z, rotate,  Point(_speed_drone, 100),_input_type);
		_multiple_Input_Devices->prepare_to_send(_command);
		//_sequence_number++;

		if(debug)
			cout<<_command.getConstructed_PCMD_command(1)<<endl;
	}
}
