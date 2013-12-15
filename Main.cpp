// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Drone_Socket_Manager.h"
#include "GamepadController.h"

//#pragma comment(lib, "Xinput9_1_0.lib") // manette Xbox
int main()
{
	Drone_Socket_Manager *dcm = new Drone_Socket_Manager();
	GamepadController *gc = new GamepadController(dcm);
}