#include "Camera.h"
#include <algorithm>
#include "Game.h"

void Camera::Initialise()
{
	//default vectors
	//cam position
	position.x = 0.0f;
	position.y = 3.7f;
	position.z = -3.5f;

	//camera rotation
	orientation.x = 0;
	orientation.y = 0;
	orientation.z = 0;

	//point to focus on
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 0.0f;

	//direction to point
	lookDirection.x = 0.0f;
	lookDirection.y = 0.0f;
	lookDirection.z = 1.0f;

	//the camera's Y axis
	camUp.x = 0;
	camUp.y = 0;
	camUp.z = 0;

	//the camera's right direction
	camRight.x = 1.0f;
	camRight.y = 0.0f;
	camRight.z = 0.0f;
}

void Camera::Update(InputCommands& Input)
{
	//if this is the camera in use
	if (cameraActive)
	{
		inputs = Input;	//get reference to inputs (for WASD and mouse)

		//if in the mode to move the camera, allow inputs (prevents focus camera being moved)
		if (Input.currentMode == InputCommands::Modes::normal)
			MoveCamera();

		//rotate if pushing right mouse button, otherwise tell program to reset camera center to mouse pos next time its pressed (prevent snapping if user moves the mouse
		//when not rotating the camera
		if (inputs.rightMouseDown)
			RotateCamera();
		else
			cameraStart = true;

		//update lookat point
		lookAt = position + lookDirection;

		//apply camera vectors
		view = DirectX::SimpleMath::Matrix::CreateLookAt(position, lookAt, DirectX::SimpleMath::Vector3::UnitY);
	}
}

void Camera::MoveCamera()
{
	position += (inputs.right - inputs.left) * moveSpeed * camRight;
	position.y += (inputs.up - inputs.down) * moveSpeed;
	position += (inputs.forward - inputs.back) * moveSpeed * lookDirection;
}

void Camera::RotateCamera()
{
	//recenter camera around mouse if it has been moved without the camera being rotated 
	//(i.e. if moved to the right since last rotation, the camera would snap right without this)
	if (cameraStart)
	{
		prevMouseX = inputs.mouseX;
		prevMouseY = inputs.mouseY;
		cameraStart = false;
		return;
	}

	//work out movement based on where mouse was last frame compared to now
	float deltaX = (inputs.mouseX - prevMouseX) * sensitivity;
	float deltaY = (inputs.mouseY - prevMouseY) * sensitivity;

	//make this mouse pos the prev for next frame
	prevMouseX = inputs.mouseX;
	prevMouseY = inputs.mouseY;

	//change yaw and pitch
	orientation.y += deltaX; //yaw (side)
	orientation.x -= deltaY; //pitch (up)

	//clamp to stop from flipping (>90 would flip camera)
	orientation.x = (std::max)(-89.0f, (std::min)(orientation.x, 89.0f));

	//use formula from wiki
	lookDirection = DirectX::SimpleMath::Vector3(cos(orientation.y * 3.1415f / 180) * cos(orientation.x * 3.1415 / 180), sin(orientation.x * 3.1415 / 180),
		sin(orientation.y * 3.1415 / 180) * cos(orientation.x * 3.1415 / 180));
	lookDirection.Normalize();

	//change right vec
	lookDirection.Cross(DirectX::SimpleMath::Vector3::UnitY, camRight);
}

void Camera::FocusOnObject(DirectX::SimpleMath::Vector3 focus)
{
	//move camera position to the objects position + the offset
	position = focus + objectOffset;

	//set lookat to point towards the object
	lookAt = focus;

	//get the look direction by subtracting camera's position from the target
	lookDirection = lookAt - position;
	lookDirection.Normalize();

	//get the right vector
	lookDirection.Cross(DirectX::SimpleMath::Vector3::UnitY, camRight);
	camRight.Normalize();

	//update view to pass back to main camera in game.cpp
	view = DirectX::SimpleMath::Matrix::CreateLookAt(position, lookAt, DirectX::SimpleMath::Vector3::UnitY);
}