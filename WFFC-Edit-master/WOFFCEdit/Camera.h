#pragma once
#include "d3d12.h"
#include <SimpleMath.h>
#include "StepTimer.h"
#include "SceneObject.h"
#include "DisplayObject.h"
#include "DisplayChunk.h"
#include "ChunkObject.h"
#include "InputCommands.h"
#include <vector>

class Camera
{
public:
	//functions
	void Initialise();
	void Update(InputCommands& Input);
	void FocusOnObject(DirectX::SimpleMath::Vector3 objectPosition);

	//position and rotation vectors
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 orientation;
	DirectX::SimpleMath::Vector3 lookAt;
	DirectX::SimpleMath::Vector3 lookDirection;
	DirectX::SimpleMath::Vector3 camRight;
	DirectX::SimpleMath::Vector3 camUp;

	DirectX::SimpleMath::Matrix view;	//view calculation
	bool cameraActive = false, focused = false;		//decide if this camera is in use, adn whether it is the focus camera

	float sensitivity = 0.5f, arcballSensitivy = 0.005f, moveSpeed = 1.5f;		//rotation and movement speeds


private:
	//internal functions
	void RotateCamera();
	void MoveCamera();
	void ArcballCamera();

	//internal vars
	float prevMouseX, prevMouseY;	//where to compare the mouse's current pos to when moving, usually the position last frame
	bool cameraStart = true;	//whether or not the camera has just started moving (i.e. when the mouse button is first clicked)
	DirectX::SimpleMath::Vector3 objectOffset{ 2, 1, -3 };		//how far from the focus object to move the camera
	DirectX::SimpleMath::Vector3 focusPosition{ 0, 0, 0 };		//the position of the object bing focused on
	InputCommands inputs;	//reference to input commands (when mouse/kb is pressed)
};