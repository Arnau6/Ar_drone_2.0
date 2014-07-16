#pragma once
class At_Command
{
public:
	At_Command(void);
	At_Command(float x, float y, float z, float rotate,Point speed, int input_type);
	At_Command(string prioritary_command, int input_type);

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
	int At_Command::get_Float_value_IEEE754(float value);
	~At_Command(void);

	string getConstructed_PCMD_command(int sequence_number);

	float _x, _y, _z, _rotate;
	int _input_type, _clock;
	Point _speed;
	string _prioritary_command;

	boolean isAviable;

	static const int keyboardType = 0;// GamePadType =1, leapMotionType =2, automaticType =3;
};
