#pragma once

class Drone_Socket_Manager
{
public:
	Drone_Socket_Manager();
	~Drone_Socket_Manager();
	void send(char*);

private:
	SOCKADDR_IN goal_address;
	SOCKET goal_type_socket;

	void allowSocket();
	void prepare_UDP_connextion();
};

