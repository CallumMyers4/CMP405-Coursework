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
	void Initialise(InputCommands* Input);
	void Update();
	void FocusOnObject(DirectX::SimpleMath::Vector3 objectPosition);

	//position and rotation vectors
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 orientation;
	DirectX::SimpleMath::Vector3 lookAt;
	DirectX::SimpleMath::Vector3 lookDirection;
	DirectX::SimpleMath::Vector3 camRight;
	DirectX::SimpleMath::Vector3 camUp;

	DirectX::SimpleMath::Matrix view;	//view calculation
	float sensitivity = 5.0f, moveSpeed = 3.0f;	//mouse sensitivity and movement speed

private:
	//internal functions
	void RotateCamera();
	void MoveCamera();

	//internal vars
	float prevMouseX, prevMouseY;	//where to compare the mouse's current pos to when moving, usually the position last frame
	bool cameraStart = true;	//whether or not the camera has just started moving (i.e. when the mouse button is first clicked)
	InputCommands inputs;	//reference to input commands (when mouse/kb is pressed)
};