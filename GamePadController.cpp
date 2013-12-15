#include "stdafx.h"

#include "Drone_Socket_Manager.h"
#include "GamepadController.h"

GamepadController::GamepadController(Drone_Socket_Manager* dsm)
{
	_drone = dsm;
	checkInput();
}

GamepadController::~GamepadController()
{
}

void GamepadController::checkInput()
{
	_sequence_number = 0;
	_speed_drone = 0.1f;
	memset(&_state, 0, sizeof(XINPUT_STATE)); //initialise la variable

	while(true)
	{
		Sleep(40);
		if (!XInputGetState(0, &_state) == ERROR_SUCCESS) // Test si une manette est branché, 0 correspond au joueur 1
		{
			string a;
			cout << "Veuillez brancher une manette"<<endl;
			cin >> a;
		}
		else
			parseInput();
	}
}


void GamepadController::parseInput()
{

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_START){
		_command = "AT*REF=1,290718208\r\n";// Decollage
		_drone->send((char*) _command.c_str());
		_sequence_number = 2;

		cout<< "START ";
		cout<<_command<<endl;
		return;
	}

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK){
		_command = "AT*REF=1,290717952\r\n";// Reset
		_drone->send((char*) _command.c_str());
		_sequence_number = 2;

		cout<< "Back ";
		cout<<_command<<endl;
		return;
	}

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_X){
		_command = "AT*REF=1,290717696\r\n";// Atterissage
		_drone->send((char*) _command.c_str());
		_sequence_number = 2;

		cout<< "X ";
		cout<<_command<<endl;
		return;
	}


	string gaz = "0";
	string left_stick_x = "0";
	string left_stick_y = "0";
	string right_stick_x = "0";
	string right_stick_y = "0";

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_A){ 
		/*_command = string("AT*PCMD=") + to_string(_sequence_number) + string(",1,0,0,") + get_Float_value_IEEE754(-1) + string(",0\r\n");
		_drone->send((char*) _command.c_str());
		_sequence_number++;*/
		gaz =  get_Float_value_IEEE754(-1);


		cout<< "A ";
		//cout<<_command<<endl;
	}

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_B){
		cout<< "B ";
	}

	if(_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y){

		/*_command = string("AT*PCMD=") + to_string(_sequence_number) + string(",1,0,0,") + get_Float_value_IEEE754(1) + string(",0\r\n");
		_drone->send((char*) _command.c_str());
		_sequence_number++;*/
		 gaz =  get_Float_value_IEEE754(1);

		cout<< "Y ";
		//cout<<_command<<endl;
	}

	/*
	 *Left thumbstick x-axis value. Each of the thumbstick axis members is a signed value between -32768 and 32767 
	 *describing the position of the thumbstick. A value of 0 is centered. 
	 *Negative values signify down or to the left. Positive values signify up or to the right.
	 */
	float x = _state.Gamepad.sThumbLX;
	float y = _state.Gamepad.sThumbLY;
	(x<0)?x /= 32768 : x /= 32767;
	(y<0)?y /= 32768 : y /= 32767;

	if (!(x<0.2 && x >-0.2) || !(y<0.2 && y >-0.2)) // DeadZone du stick
	{

		left_stick_x = get_Float_value_IEEE754(x*_speed_drone);
		left_stick_y = get_Float_value_IEEE754(-y*_speed_drone);

		cout<<"stick left ";
	}

	x = _state.Gamepad.sThumbRX;
	(x<0)?x /= 32768 : x /= 32767;
	(y<0)?y /= 32768 : y /= 32767;

	if (!(x<0.2 && x >-0.2) || !(y<0.2 && y >-0.2)) // DeadZone du stick
	{
		right_stick_x = get_Float_value_IEEE754(x);
		right_stick_y = get_Float_value_IEEE754(-y);

		cout<<"right ";
	}



	if (left_stick_x != "0" || left_stick_y != "0" || gaz != "0" || right_stick_x != "0")
	{
		_command = string("AT*PCMD=")+to_string(_sequence_number) + string(",1,")+left_stick_x + string(",") + left_stick_y + string(",")+ gaz + string(",")+right_stick_x+string("\r\n");
		_drone->send((char*) _command.c_str());
		_sequence_number++;
		cout<<_command<<endl;
	}
}

string GamepadController:: get_Float_value_IEEE754(float value)
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
	(float)-0.05 = (int)1119040307
	*/

	return to_string(convert);
}