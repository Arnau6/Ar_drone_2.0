#pragma once
#include "stdafx.h"
#include "Multiple_Input_Devices.h"

class LeapMotion_Listener : public Listener {

public:
	LeapMotion_Listener(Multiple_Input_Devices*);

	virtual void onInit(const Controller&);
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onExit(const Controller&);
	virtual void onFrame(const Controller&);
	virtual void onFocusGained(const Controller&);
	virtual void onFocusLost(const Controller&);


private:
	Multiple_Input_Devices *_multiple_Input_Devices;
	int _input_type;
};