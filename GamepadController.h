#pragma once

class GamepadController
{

public:
	GamepadController(Drone_Socket_Manager*);
	~GamepadController();
	string get_Float_value_IEEE754(float);

private:
	Drone_Socket_Manager *_drone;

	string _command; //message a envoyer
	XINPUT_STATE _state;
	int _sequence_number; // correspond au numero de la commande envoyé au drone, le protocol UDP pouvant subir des pertes il ne faut pa
	float _speed_drone;

	void checkInput();
	void parseInput();
};

