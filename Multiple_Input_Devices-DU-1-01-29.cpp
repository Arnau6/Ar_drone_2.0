#include "stdafx.h"
#include "Multiple_Input_Devices.h"
#include "GamepadController.h"
#include "LeapMotion_Listener.h"

Multiple_Input_Devices::Multiple_Input_Devices(Socket_Manager* dcm)
{
	init_command();
	_drone = dcm;
	
	DWORD threadID_GP = 3, threadID_input = 4; // 0 is for faceDetector, 1 for the video, 2 for NavData
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

	if(Keyboard_command.find("AT")==0)
	{
		_drone->sendCmd((char*) Keyboard_command.c_str());
		return true;
	}
	else if(GamePad_command.find("AT")==0)
	{
		cout<<"in";
		_drone->sendCmd((char*) GamePad_command.c_str());
		return true;
	}

	else if(LeapMotion_command.find("AT")==0)
	{
		_drone->sendCmd((char*) LeapMotion_command.c_str());
		return true;
	}

	else if(automatic_command.find("AT")==0)
	{
		_drone->sendCmd((char*) automatic_command.c_str());
		return true;
	}

	return false;
}

void Multiple_Input_Devices::loop_check_input()
{
	// Priority command : keyboard > GamePad > LeapMotion > automatic
	// an inferiors command must wait (difftime + last superior command) to be valid
	bool debug = false;

	int last_global_command_ms = 0;
	int last_Keyboard_command_ms = 0;
	int last_GamePad_command_ms = 0;
	int last_LeapMotion_command_ms = 0;
	int last_automatic_command_ms = 0;

	int difftime = 1500;
	int no_command = 0;
	int sequence_number = 2;

	while (true)
	{
		if(clock() - last_global_command_ms < 100) // max command send per second = 20 (1000/50)
			continue;

		if (/*Keyboard_command.find("AT")==0 || GamePad_command.find("AT")==0 || LeapMotion_command.find("AT")==0 || automatic_command.find("AT")==0 || */check_prioritary_command())
		{
			sequence_number = 2;
			last_global_command_ms = clock();
			init_command();
			continue;
		}
		//else  cout <<endl<<"-----"<<GamePad_command.c_str()<<endl;

		if(Keyboard_command.length() > 0)
		{
			ostringstream oss;
			oss<<"AT*PCMD="<<sequence_number<<Keyboard_command;
			_drone->sendCmd((char*) oss.str().c_str());

			if(debug) cout <<"KB  : "<<oss.str()<<endl;

			last_Keyboard_command_ms = last_global_command_ms = clock();
			init_command();
			sequence_number++;
		}

		else if(GamePad_command.length() > 0 && (clock() - last_Keyboard_command_ms > difftime))
		{
			ostringstream oss;
			oss<<"AT*PCMD="<<sequence_number<<GamePad_command;
			_drone->sendCmd((char*) oss.str().c_str());

			if(debug) cout <<"PAD : "<<oss.str()<<endl;

			last_GamePad_command_ms = last_global_command_ms = clock();
			init_command();
			sequence_number++;
		}

		else if(LeapMotion_command.length() > 0 && (clock() - last_Keyboard_command_ms > difftime) && (clock() - last_GamePad_command_ms > difftime))
		{
			ostringstream oss;
			oss<<"AT*PCMD="<<sequence_number<<LeapMotion_command;
			_drone->sendCmd((char*) oss.str().c_str());

			if(debug) cout <<"LM  : " <<oss.str()<<endl;

			last_LeapMotion_command_ms = last_global_command_ms = clock();
			init_command();
			sequence_number++;
		}

		else if(automatic_command.length() > 0 && (clock() - last_Keyboard_command_ms > difftime) && (clock() - last_GamePad_command_ms > difftime)
			&& (clock() - last_LeapMotion_command_ms > difftime))
		{
			ostringstream oss;
			oss<<"AT*PCMD="<<sequence_number<<automatic_command;
			_drone->sendCmd((char*) oss.str().c_str());

			if(debug) cout <<"AC  : "<<oss.str()<<endl;

			last_automatic_command_ms = last_global_command_ms = clock();
			init_command();
			sequence_number++;
		}
		else
		{
			/*
			//Connection is lost if the drone received any command in 2000 ms
			//if the NavData is use, the code below is usless

			if(clock() - last_global_command_ms > 1500)
			{
				
				ostringstream oss;
				oss<<"AT*PCMD="<<sequence_number<<",1,0,0,0,0\r\n";
				_drone->sendCmd((char*) oss.str().c_str());

				if(debug) cout <<"Void : "<<oss.str()<<endl;

				last_global_command_ms = clock();
				sequence_number++;
			}
			*/	
		}
	}
}

void Multiple_Input_Devices::init_command()
{
	Keyboard_command = "";
	GamePad_command = "";
	LeapMotion_command = "";
	automatic_command = "";
}
void Multiple_Input_Devices::prepare_to_send(string msg, int input_type)
{
	/*
	 *	input_type info
	 *	0 = Keyboard
	 *	1 = GamePad
	 *	2 = LeapMotion
	 *	3 = automatic
	 */

	switch (input_type)
	{
	case 0 : 
		Keyboard_command = msg;
		
		break;

	case 1 : 
		GamePad_command = msg;
		
		break;

	case 2 : 
		LeapMotion_command = msg;
		
		break;

	case 3 : 
		automatic_command = msg;
		
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

string Multiple_Input_Devices::get_Float_value_IEEE754(float value)
{
	int convert = *(int*)&value; 
	/*
	un float est constitué de 4 octets de 32 bits, de même pour les int.
	Ainsi grace a (int*)&value; on precise que le pointeur pointant sur un float est à interpreté comme
	si il pointe sur un int. Le 1er caractere * permet alors de recuperer la valeur contenu dans le pointeur a l'adresse suivante

	Pour un float 2 octets sont pour les  puissance de 2 negative (a droite de la virgule), 2 octets pour les puissance de 2 positive.
	Pour un int les 4 octets sont pour les puissance de 2 positives (pas de virgule). 

	Ainsi grace a cette conversion on obtient la valeur IEEE754 d'un float. 
	Attention : le float et le int doivent être codé sur lemême nombre de bit

	Example Float to Integer conversions:
	(float)0.05 = (int)1028443341
	(float)-0.05 = (int)-1119040307

	(float)1 = (int)1065353216;
	(float)1 = (int)-1082130432;
	*/
	ostringstream oss;
	oss<<convert;
	return oss.str();
}