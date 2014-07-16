// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Socket_Manager.h"
#include "Multiple_Input_Devices.h"
#include "VideoManager.h"
#include "GamepadController.h"
#include "LeapMotion_Listener.h"
#include "NavData.h"
#include "MyMainWindowsForm.h"

using namespace Ar_drone_20;

[STAThread]
int main()
{
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE); //hide console application
	//or
	//FreeConsole();//remove console application
	


	boolean is_automatic_mouvement = false, detectFace = true, 
		useDrone_unless_PcWebcam = false;

	const string videoStreamAddress = "tcp://192.168.1.1:5555";
	const string controlling_IP = "192.168.1.1";
	u_short controlling_Port = 5556;
	u_short navData_Port = 5554;
	
	Socket_Manager* dsm = new Socket_Manager(videoStreamAddress, controlling_IP, controlling_Port, navData_Port);
	
	Multiple_Input_Devices* mid = new Multiple_Input_Devices(dsm);

	NavData* navData = new NavData(dsm, mid);
	
	VideoManager* vm = new VideoManager(mid, detectFace, is_automatic_mouvement, navData, useDrone_unless_PcWebcam);


	//vm->custom_and_print_frame();
	
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew MyMainWindowsForm(vm, mid));

	return 0;
}



