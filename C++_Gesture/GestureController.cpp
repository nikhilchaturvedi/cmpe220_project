/*Implements the Listener functions for the Leap Motion
**Author - Nikhil Chaturvedi*/

#include <iostream>
#include <cstring>
#include "GestureController.h"

using namespace Leap;

const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

void GestureListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void GestureListener::onConnect(const Controller& controller) 
{
  std::cout << "Connected" << std::endl;

  //Enable all the gestures supported
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void GestureListener::onDisconnect(const Controller& controller) 
{
  std::cout << "Disconnected" << std::endl;
}

void GestureListener::onExit(const Controller& controller) 
{
  std::cout << "Exited" << std::endl;
}

void GestureListener::onFrame(const Controller& controller) 
{
  
  const Frame frame = controller.frame();

  //Get the gestures and iterate through them
  const GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];

    switch (gesture.type()) 
	{
      case Gesture::TYPE_CIRCLE:
      {
        CircleGesture circle = gesture;
        
		if(gesture.state() == gesture.STATE_START | gesture.state() == gesture.STATE_STOP)
        std::cout << std::string(2, ' ')
                  << " Gesture type: Swipe and id: " << gesture.id()
                  << ", state: " << stateNames[gesture.state()]
                  << ", progress: " << circle.progress()
                  << ", radius: " << circle.radius()
                  << std::endl;
        break;
		//TODO: Wrap gesture in JSON message and send it to audio kit
      }
      case Gesture::TYPE_SWIPE:
      {
        SwipeGesture swipe = gesture;
		if (gesture.state() == gesture.STATE_START | gesture.state() == gesture.STATE_STOP)
        std::cout << std::string(2, ' ')
          << "Gesture type: Swipe and id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", direction: " << swipe.direction()
          << ", speed: " << swipe.speed() << std::endl;
        break;
		//TODO: Wrap gesture in JSON message and send it to audio kit
      }

      case Gesture::TYPE_KEY_TAP:
      {
        KeyTapGesture tap = gesture;

		if (gesture.state() == gesture.STATE_START | gesture.state() == gesture.STATE_STOP)
        std::cout << std::string(2, ' ')
          << "Gesture type: Key tap and id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", position: " << tap.position()
          << ", direction: " << tap.direction()<< std::endl;
        break;
		//TODO: Wrap gesture in JSON message and send it to audio kit
      }

      case Gesture::TYPE_SCREEN_TAP:
      {
        ScreenTapGesture screentap = gesture;

		if (gesture.state() == gesture.STATE_START | gesture.state() == gesture.STATE_STOP)
        std::cout << std::string(2, ' ')
          << "Gesture type: Screen tap and id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", position: " << screentap.position()
          << ", direction: " << screentap.direction()<< std::endl;
        break;
		//TODO: Wrap gesture in JSON message and send it to audio kit
      }

      default:
        std::cout << std::string(2, ' ')  << " Gesture not recognized" << std::endl;
        break;
		//TODO: Handle unknown gestures. Currently for testing, a sleep of some 1s can be inserted
		//to ease the load on Leap Motion
    }
  }

}

void GestureListener::onFocusGained(const Controller& controller) 
{
  std::cout << "Focus Gained" << std::endl;
}

void GestureListener::onFocusLost(const Controller& controller) 
{
  std::cout << "Focus Lost" << std::endl;
}

void GestureListener::onDeviceChange(const Controller& controller) 
{
	//listen for device disconnect and reconnect
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}


void GestureListener::onServiceConnect(const Controller& controller) 
{
  std::cout << "Service Connected" << std::endl;
}

void GestureListener::onServiceDisconnect(const Controller& controller) 
{
  std::cout << "Service Disconnected" << std::endl;
}

int main(int argc, char** argv) 
{
  
  GestureListener listener;
  Controller controller;

  controller.addListener(listener);

  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
