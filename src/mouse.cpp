#include "mouse.h"

bool moveCamera;
int cameraRotationX;
int cameraRotationY;
int mouse1XDown;
int mouse1YDown;
int mouse1XUp;
int mouse1YUp;
bool zoom;
float zoomValue;
int mouse2YDown;
int mouse2YUp;

int lastMouse1X = 0;
int lastMouse1Y = 0;
int lastMouse2Y = 0;

Mouse::Mouse()
{
	this->cameraRotationX = 0;
	this->cameraRotationY = 0;
	this->mouse1XDown = 0;
	this->mouse1YDown = 0;
	this->mouse1XUp = 0;
	this->mouse1YUp = 0;
	this->zoomValue = 1.0;
	this->mouse2YDown = 0;
	this->mouse2YUp = 0;

	this->lastMouse1X = 0;
	this->lastMouse1Y = 0;
	this->lastMouse2Y = 0;
	this->moveCamera = false;
	this->zoom = false;
}