/**
**Class to handle gesture capture
**This handles the callbacks supported in Leap Motion SDK
References : Leap Motion developer website
Author - Nikhil Chaturvedi*/

#include "Leap.h"

using namespace Leap;

class GestureListener : public Listener
{
public:
	virtual void onInit(const Controller&);
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onExit(const Controller&);
	virtual void onFrame(const Controller&);
	virtual void onFocusGained(const Controller&);
	virtual void onFocusLost(const Controller&);
	virtual void onDeviceChange(const Controller&);
	virtual void onServiceConnect(const Controller&);
	virtual void onServiceDisconnect(const Controller&);

};
