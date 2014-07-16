#include "stdafx.h"
#include "Socket_Manager.h"
#include "NavData.h"


Socket_Manager::Socket_Manager(const string videoStreamAddress, const string controlling_IP, u_short controlling_port, u_short navData_Port)
{
	_videoStreamAddress = videoStreamAddress;
	choose_wifi();

	//TODO: a Verifier
	//HINTERNET hInet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0 );
	//InternetCloseHandle(hInet);

	this->allowSocket();
	this->init_command_socket(controlling_IP, controlling_port);
	this->init_navData_socket(controlling_IP, navData_Port);
	this->initConfig();
}

Socket_Manager::~Socket_Manager()
{
	
}

void Socket_Manager::choose_wifi()
{
	ShellExecute(
		NULL, 
		L"open", 
		L"shell:::{21EC2020-3AEA-1069-A2DD-08002B30309D}\\::{38a98528-6cbf-4ca9-8dc0-b1e1d10f7b1b}",
		NULL,
		NULL,
		SW_SHOWNORMAL);
}

void Socket_Manager::allowSocket()
{
	/*
	 * Autorise windows à creer des socket
	 */

	WSADATA socket_info;
	int erreur; 

	erreur=WSAStartup(MAKEWORD(2,2),&socket_info);
	if (erreur!=0)
		printf("\nErreur sur l'authorisation de creation de socket : %d %d",erreur,WSAGetLastError());
}

void Socket_Manager::init_command_socket(const string controlling_IP, u_short controlling_port)
{
	/*
	 *Prepare une socket pour l'envoie de données au format UDP
	 */

	command_socket= socket(AF_INET, SOCK_DGRAM, 0); // AF_INET = IPV4, SOCK_DGRAM = UPD, SOCK_STRAM = TCP

	if(command_socket == INVALID_SOCKET)
		cout <<"Erreur sur l'initialisation de la socket";

	command_address.sin_family=AF_INET; //IPV4
	command_address.sin_addr.s_addr=inet_addr(controlling_IP.c_str());
	command_address.sin_port=htons(controlling_port);

}

void Socket_Manager::init_navData_socket(const string navData_IP, u_short navData_Port)
{
	/*
	 *Prepare une socket pour l'envoie de données au format UDP
	 */

	navData_socket= socket(AF_INET, SOCK_DGRAM, 0); // AF_INET = IPV4, SOCK_DGRAM = UPD, SOCK_STRAM = TCP

	if(navData_socket == INVALID_SOCKET)
		cout <<"Erreur sur l'initialisation de la socket";

	navData_address.sin_family=AF_INET; //IPV4
	navData_address.sin_addr.s_addr=inet_addr(navData_IP.c_str());
	navData_address.sin_port=htons(navData_Port);
	
}

void Socket_Manager::sendCmd(string msg)
{
	//cout << "-->"<<(char *) msg.c_str();
	sendto(command_socket,(char *) msg.c_str(),msg.size(),0,(struct sockaddr*)&command_address,sizeof(command_address));
}

void Socket_Manager::sendNavData(char* msg)
{
	sendto(navData_socket,msg,strlen(msg),0,(struct sockaddr*)&navData_address,sizeof(navData_address));
}

int Socket_Manager::receiveNavData(void* data, int size)
{	
	// Receive data
	sockaddr_in addr;
	int len = sizeof(navData_address);
	int n = recvfrom(navData_socket, (char*)data, size, 0, (sockaddr*)&addr, &len);
	if (n < 1) return 0;

	return n;
}




string Socket_Manager::toString(int value)
{
	ostringstream oss;
	oss<<value;
	string result = oss.str();
	return result;
}

const string Socket_Manager::getVideoStreamAddress()
{
	return (static_cast<const string>(_videoStreamAddress));
}

void Socket_Manager::initConfig()
{
	// TODO: the first argument of the first command (sequence number) must begin with 0 and not 1 as for AT*PCMD
	int nb = 0;

		/*
	//first command use in the sdk. Seems have no effect
	string unknow_cmd1 = "AT*PMODE="+toString(nb++)+",2";
	string unknow_cmd2= "AT*MISC="+toString(nb++)+",2,20,2000,3000";
	sendCmd((char*)unknow_cmd1.c_str());
	sendCmd((char*)unknow_cmd2.c_str());
	*/

	//-----------------> INIT THE SESSION
	string cmd1 = "AT*CONFIG_IDS="+toString(nb++)+",\""ARDRONE_SESSION_ID"\",\""ARDRONE_PROFILE_ID"\",\""ARDRONE_APPLOCATION_ID"\"\r";
	string cmd2 = "AT*CONFIG="+toString(nb++)+",\"custom:session_id\",\""ARDRONE_SESSION_ID"\"\r";
	sendCmd((char*)cmd1.c_str());
	sendCmd((char*)cmd2.c_str());
	Sleep(100);

	string cmd3 = "AT*CONFIG_IDS="+toString(nb++)+",\""ARDRONE_SESSION_ID"\",\""ARDRONE_PROFILE_ID"\",\""ARDRONE_APPLOCATION_ID"\"\r";
	string cmd4 = "AT*CONFIG="+toString(nb++)+",\"custom:profile_id\",\""ARDRONE_PROFILE_ID"\"\r";
	sendCmd((char*)cmd3.c_str());
	sendCmd((char*)cmd4.c_str());
	Sleep(100);

	string cmd5 = "AT*CONFIG_IDS="+toString(nb++)+",\""ARDRONE_SESSION_ID"\",\""ARDRONE_PROFILE_ID"\",\""ARDRONE_APPLOCATION_ID"\"\r";
	string cmd6 = "AT*CONFIG="+toString(nb++)+",\"custom:application_id\",\""ARDRONE_APPLOCATION_ID"\"\r";
	sendCmd((char*)cmd5.c_str());
	sendCmd((char*)cmd6.c_str());
	Sleep(100);

	//-----------------> START Navdata
	sendNavData((char *) "\x01\x00\x00\x00");
	string cmd7 = "AT*CONFIG_IDS="+toString(nb++)+",\""ARDRONE_SESSION_ID"\",\""ARDRONE_PROFILE_ID"\",\""ARDRONE_APPLOCATION_ID"\"\r";
	string cmd8 = "AT*CONFIG="+toString(nb++)+",\"general:navdata_demo\",\"TRUE\"\r";
	string cmd9 = "AT*CTRL="+toString(nb++)+",0\r";

	sendCmd((char*)cmd7.c_str());
	sendCmd((char*)cmd8.c_str());
	Sleep(100);

	sendCmd((char*)cmd9.c_str());// Seed ACK
	Sleep(100);

	//-----------------> SET THE WEBCAM TO USE, 0 for horizontal or 1 for vertical
	string cmd10 = "AT*CONFIG_IDS="+toString(nb++)+",\""ARDRONE_SESSION_ID"\",\""ARDRONE_PROFILE_ID"\",\""ARDRONE_APPLOCATION_ID"\"\r";
	string cmd11 = "AT*CONFIG="+toString(nb++)+",\"video:video_channel\",\"0\"\r";
	sendCmd((char*)cmd10.c_str());
	sendCmd((char*)cmd11.c_str());
	Sleep(100);

	//-----------------> SET THE QUALITY, 129 for 360p or 131 for 720p
	string cmd12 = "AT*CONFIG_IDS="+toString(nb++)+",\""ARDRONE_SESSION_ID"\",\""ARDRONE_PROFILE_ID"\",\""ARDRONE_APPLOCATION_ID"\"\r";
	string cmd13 = "AT*CONFIG="+toString(nb++)+",\"video:video_codec\",\"131\"\r";
	sendCmd((char*)cmd12.c_str());
	sendCmd((char*)cmd13.c_str());
	Sleep(100);

	//string cmd14 = "AT*CONFIG_IDS="+toString(nb++)+",\""ARDRONE_SESSION_ID"\",\""ARDRONE_PROFILE_ID"\",\""ARDRONE_APPLOCATION_ID"\"\r";
	//string cmd15 = "AT*CONFIG="+toString(nb++)+",\"video:bitrate\",\"4000\"\r";
	//sendCmd((char*)cmd14.c_str());
	//sendCmd((char*)cmd15.c_str());
	//Sleep(100);

	//-----------------> INIT THE ENSOR CAPTOR, must only use when the drone in on the ground
	string cmd16 = "AT*FTRIM="+toString(nb++)+",\r";
	sendCmd((char*)cmd16.c_str());
	Sleep(100);
}

