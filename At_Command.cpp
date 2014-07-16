#include "StdAfx.h"
#include "At_Command.h"

At_Command::At_Command(void)
{
	_clock = clock();
	isAviable = false;
	_x =0, _y=0, _z=0, _rotate = 0, _input_type = -1;
}
At_Command::At_Command( float x, float y, float z, float rotate, Point speed, int input_type )
{
	_clock = clock();
	isAviable = true;
	_input_type = input_type;
	_x = x;
	_y = y;
	_z = z;
	_rotate = rotate;
	_speed = speed;
}

At_Command::At_Command( string prioritary_command, int input_type )
{
	_clock = clock();
	isAviable = true;
	_x =0, _y=0, _z=0, _rotate = 0, _input_type = -1;
	_input_type =  input_type;
	_prioritary_command = prioritary_command;
}

At_Command::~At_Command(void)
{
}

string At_Command::getConstructed_PCMD_command( int sequence_number )
{
	bool debug = false;
	ostringstream command;
	command << "AT*PCMD=" << sequence_number<<",1,"<< get_Float_value_IEEE754(_x*_speed.x/100.0f) <<","<< get_Float_value_IEEE754(_z*_speed.x/100.0f) <<","<< get_Float_value_IEEE754(_y*_speed.y/100.0f) << "," << get_Float_value_IEEE754(_rotate)<< "\r\n";

	string res = command.str();

	if(debug)
		cout<<"x = "<<_x<<endl
			<<"z = "<<_z<<endl
			<<"y = "<<_y<<endl
			<<"rotate = "<<_rotate<<endl<<endl;

	//cout<<"---->"<< res;
	return res;
}

int At_Command::get_Float_value_IEEE754(float value)
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
	(float)-1 = (int)-1082130432;
	*/
	return convert;
}