#include "stdafx.h"
#include "Drone_Socket_Manager.h"

//#pragma comment(lib, "WS2_32.lib") // socket





Drone_Socket_Manager::Drone_Socket_Manager()
{
	this->allowSocket();
	this->prepare_UDP_connextion();
}

Drone_Socket_Manager::~Drone_Socket_Manager()
{
	
}

void Drone_Socket_Manager::allowSocket()
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

void Drone_Socket_Manager::prepare_UDP_connextion()
{
	/*
	 *Prepare une socket pour l'envoie de données au format UDP
	 */

	goal_type_socket= socket(AF_INET, SOCK_DGRAM, 0); // AF_INET = IPV4, SOCK_DGRAM = UPD, SOCK_STRAM = TCP

	if(goal_type_socket == INVALID_SOCKET)
		cout <<"Erreur sur l'initialisation de la socket";

	goal_address.sin_family=AF_INET; //IPV4
	goal_address.sin_addr.s_addr=inet_addr("192.168.1.1");
	goal_address.sin_port=htons(5556); // Port(UDP) du Drone dedié au controlle et à la configuration (Controlling and configuring) 
}

void Drone_Socket_Manager::send(char* msg)
{
	sendto(goal_type_socket,msg,strlen(msg),0,(struct sockaddr*)&goal_address,sizeof(goal_address));
}
