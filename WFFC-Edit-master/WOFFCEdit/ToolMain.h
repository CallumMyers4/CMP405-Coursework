#pragma once

#include <afxext.h>
#include "pch.h"
#include "Game.h"
#include "sqlite3.h"
#include "SceneObject.h"
#include "InputCommands.h"
#include <vector>


class ToolMain
{
public: //methods
	ToolMain();
	~ToolMain();

	//onAction - These are the interface to MFC
	int		getCurrentSelectionID();										//returns the selection number of currently selected object so that It can be displayed.
	void	onActionInitialise(HWND handle, int width, int height);			//Passes through handle and hieght and width and initialises DirectX renderer and SQL LITE
	void	onActionLoad();													//load the current chunk
	void	PasteObject();													//create new instance of current selection to scene graph
	void	CreateNewObject(std::string model, std::string tex,				//add a new object to the scene graph
			DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rotation);
	void	DeleteObject();													//delete object from scene graph
	afx_msg	void	onActionSave();											//save the current chunk
	afx_msg void	onActionSaveTerrain();									//save chunk geometry

	void	Tick(MSG *msg);
	void	UpdateInput(MSG *msg);

	void ChangeMode(InputCommands::Modes newMode);	//switch between the mode types

	//translate object functions
	void Translate(DirectX::SimpleMath::Vector3 direction);		//move object
	DirectX::SimpleMath::Vector3 objectTranslationDir	{ 0, 0, 0 };	//where to move to

	//rotate object functions
	void Rotate(DirectX::SimpleMath::Vector3 direction);		//rotate object
	DirectX::SimpleMath::Vector3 objectRotationDir{ 0, 0, 0 };	//axis to rotate in

	//scale object functions
	void Scale(DirectX::SimpleMath::Vector3 direction);		//scale object
	DirectX::SimpleMath::Vector3 objectScaleDir{ 0, 0, 0 };	//axis to scale in

	//set new camera vars (for the dialogue window)
	void SetCameraVars(float speed, float standardRot, float arcballRot);

public:	//variables
	std::vector<SceneObject>    m_sceneGraph;	//our scenegraph storing all the objects in the current chunk
	ChunkObject					m_chunk;		//our landscape chunk
	int m_selectedObject;						//ID of current Selection

private:	//methods
	void	onContentAdded();


		
private:	//variables
	HWND	m_toolHandle;		//Handle to the  window
	Game	m_d3dRenderer;		//Instance of D3D rendering system for our tool
	InputCommands m_toolInputCommands;		//input commands that we want to use and possibly pass over to the renderer
	CRect	WindowRECT;		//Window area rectangle. 
	char	m_keyArray[256];
	sqlite3 *m_databaseConnection;	//sqldatabase handle

	int m_width;		//dimensions passed to directX
	int m_height;
	int m_currentChunk;			//the current chunk of thedatabase that we are operating on.  Dictates loading and saving. 
};
