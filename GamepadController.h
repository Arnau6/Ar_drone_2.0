#pragma once

class GamepadController
{

public:
	GamepadController(Multiple_Input_Devices*);
	~GamepadController();

private:
	Multiple_Input_Devices *_multiple_Input_Devices;

	int _input_type;

	At_Command _command; //message a envoyer
	XINPUT_STATE _state;
	int _sequence_number; // correspond au numero de la commande envoyé au drone, le protocol UDP pouvant subir des pertes il ne faut pa
	int _speed_drone;

	void checkInput();
	void parseInput();
};

