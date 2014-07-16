#pragma once


class Socket_Manager
{
public:
	Socket_Manager(const string videoStreamAddress, const string controlling_IP, u_short controlling_Port, u_short navData_Port);
	~Socket_Manager();
	void sendCmd(string);
	void sendNavData(char*);
	int receiveNavData(void* data, int size);
	const string getVideoStreamAddress();
	void init_navData_socket(const string navData_IP, u_short navData_Port);

private:
	SOCKADDR_IN command_address;
	SOCKET command_socket;

	SOCKADDR_IN navData_address;
	SOCKET navData_socket;
	
	string _videoStreamAddress;

	void choose_wifi();
	void allowSocket();
	void init_command_socket(const string controlling_IP, u_short controlling_Port);
	string toString(int value);
	void initConfig();
	
};

