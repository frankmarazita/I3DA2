#ifndef MOUSE_H
#define MOUSE_H

// We can't parse in class methods to GLUT so we have to make all these public

class Mouse
{
public:
	Mouse();

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

	int lastMouse1X;
	int lastMouse1Y;
	int lastMouse2Y;

private:

};

#endif