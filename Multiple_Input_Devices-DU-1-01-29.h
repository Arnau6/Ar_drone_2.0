#pragma once
#include "Socket_Manager.h" 

class Multiple_Input_Devices
{
public:
	Multiple_Input_Devices(Socket_Manager* dcm);
	~Multiple_Input_Devices(void);
	
	void prepare_to_send(string msg, int input_type);
	Socket_Manager* getDrone_Socket_Manager();

	/**
	* Method:		get_Float_value_IEEE754
	*
	* Brief :		un float est constitué de 4 octets de 32 bits, de même pour les int.
	Ainsi grace a (int*)&value; on precise que le pointeur pointant sur un float est à interpreté comme
	si il pointe sur un int. Le 1er caractere * permet alors de recuperer la valeur contenu dans le pointeur a l'adresse suivante

	Pour un float 2 octets sont pour les  puissance de 2 negative (a droite de la virgule), 2 octets pour les puissance de 2 positive.
	Pour un int les 4 octets sont pour les puissance de 2 positives (pas de virgule). 

	Ainsi grace a cette conversion on obtient la valeur IEEE754 d'un float. 
	Attention : le float et le int doivent être codé sur lemême nombre de bit

	Example Float to Integer conversions:
	(float)0.05 = (int)1028443341
	(float)-0.05 = (int)1119040307

	(float)1 = (int)1065353216
	((float)-1 = (int)1082130432
	*
	* Parameter:	float value : float to convert
	*
	* Returns:		cv::string : string with IEEE754 value
	**/
	string get_Float_value_IEEE754(float value);
private:
	void init_command();
	void loop_check_input();
	static DWORD WINAPI thread_GamepadController (void* Param);
	static DWORD WINAPI thread_check_input (void* Param);
	bool check_prioritary_command();

	Socket_Manager* _drone;

	string Keyboard_command;
	string GamePad_command;
	string LeapMotion_command;
	string automatic_command;
};

