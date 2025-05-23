#include "ToolMain.h"
#include "resource.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm> 
#include <functional>

//
//ToolMain Class
ToolMain::ToolMain()
{

	m_currentChunk = 0;		//default value
	m_selectedObject = 0;	//initial selection ID
	m_sceneGraph.clear();	//clear the vector for the scenegraph
	m_databaseConnection = NULL;

	//zero input commands
	m_toolInputCommands.forward			= false;
	m_toolInputCommands.back			= false;
	m_toolInputCommands.left			= false;
	m_toolInputCommands.right			= false;
	m_toolInputCommands.up				= false;
	m_toolInputCommands.down			= false;
	m_toolInputCommands.focus			= false;
	m_toolInputCommands.ctrl			= false;
	m_toolInputCommands.shift			= false;
	m_toolInputCommands.paste			= false;
	m_toolInputCommands.pasteHeld		= false;
	m_toolInputCommands.deleteKey		= false;
	m_toolInputCommands.deleteKeyHeld	= false;
	m_toolInputCommands.leftMouseDown	= false;
	m_toolInputCommands.rightMouseDown	= false;
	m_toolInputCommands.mouseX			= 0;
	m_toolInputCommands.mouseY			= 0;
}

ToolMain::~ToolMain()
{
	sqlite3_close(m_databaseConnection);		//close the database connection
}


int ToolMain::getCurrentSelectionID()
{

	return m_selectedObject;
}

void ToolMain::onActionInitialise(HWND handle, int width, int height)
{
	//window size, handle etc for directX
	m_width		= width;
	m_height	= height;
	
	m_d3dRenderer.Initialize(handle, m_width, m_height);

	//database connection establish
	int rc;
	rc = sqlite3_open_v2("database/test.db",&m_databaseConnection, SQLITE_OPEN_READWRITE, NULL);

	if (rc) 
	{
		TRACE("Can't open database");
		//if the database cant open. Perhaps a more catastrophic error would be better here
	}
	else 
	{
		TRACE("Opened database successfully");
	}

	onActionLoad();
}

void ToolMain::onActionLoad()
{
	//load current chunk and objects into lists
	if (!m_sceneGraph.empty())		//is the vector empty
	{
		m_sceneGraph.clear();		//if not, empty it
	}

	//SQL
	int rc;
	char *sqlCommand;
	char *ErrMSG = 0;
	sqlite3_stmt *pResults;								//results of the query
	sqlite3_stmt *pResultsChunk;

	//OBJECTS IN THE WORLD
	//prepare SQL Text
	sqlCommand = "SELECT * from Objects";				//sql command which will return all records from the objects table.
	//Send Command and fill result object
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResults, 0 );
	
	//loop for each row in results until there are no more rows.  ie for every row in the results. We create and object
	while (sqlite3_step(pResults) == SQLITE_ROW)
	{	
		SceneObject newSceneObject;
		newSceneObject.ID = sqlite3_column_int(pResults, 0);
		newSceneObject.chunk_ID = sqlite3_column_int(pResults, 1);
		newSceneObject.model_path		= reinterpret_cast<const char*>(sqlite3_column_text(pResults, 2));
		newSceneObject.tex_diffuse_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 3));
		newSceneObject.posX = sqlite3_column_double(pResults, 4);
		newSceneObject.posY = sqlite3_column_double(pResults, 5);
		newSceneObject.posZ = sqlite3_column_double(pResults, 6);
		newSceneObject.rotX = sqlite3_column_double(pResults, 7);
		newSceneObject.rotY = sqlite3_column_double(pResults, 8);
		newSceneObject.rotZ = sqlite3_column_double(pResults, 9);
		newSceneObject.scaX = sqlite3_column_double(pResults, 10);
		newSceneObject.scaY = sqlite3_column_double(pResults, 11);
		newSceneObject.scaZ = sqlite3_column_double(pResults, 12);
		newSceneObject.render = sqlite3_column_int(pResults, 13);
		newSceneObject.collision = sqlite3_column_int(pResults, 14);
		newSceneObject.collision_mesh = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 15));
		newSceneObject.collectable = sqlite3_column_int(pResults, 16);
		newSceneObject.destructable = sqlite3_column_int(pResults, 17);
		newSceneObject.health_amount = sqlite3_column_int(pResults, 18);
		newSceneObject.editor_render = sqlite3_column_int(pResults, 19);
		newSceneObject.editor_texture_vis = sqlite3_column_int(pResults, 20);
		newSceneObject.editor_normals_vis = sqlite3_column_int(pResults, 21);
		newSceneObject.editor_collision_vis = sqlite3_column_int(pResults, 22);
		newSceneObject.editor_pivot_vis = sqlite3_column_int(pResults, 23);
		newSceneObject.pivotX = sqlite3_column_double(pResults, 24);
		newSceneObject.pivotY = sqlite3_column_double(pResults, 25);
		newSceneObject.pivotZ = sqlite3_column_double(pResults, 26);
		newSceneObject.snapToGround = sqlite3_column_int(pResults, 27);
		newSceneObject.AINode = sqlite3_column_int(pResults, 28);
		newSceneObject.audio_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 29));
		newSceneObject.volume = sqlite3_column_double(pResults, 30);
		newSceneObject.pitch = sqlite3_column_double(pResults, 31);
		newSceneObject.pan = sqlite3_column_int(pResults, 32);
		newSceneObject.one_shot = sqlite3_column_int(pResults, 33);
		newSceneObject.play_on_init = sqlite3_column_int(pResults, 34);
		newSceneObject.play_in_editor = sqlite3_column_int(pResults, 35);
		newSceneObject.min_dist = sqlite3_column_double(pResults, 36);
		newSceneObject.max_dist = sqlite3_column_double(pResults, 37);
		newSceneObject.camera = sqlite3_column_int(pResults, 38);
		newSceneObject.path_node = sqlite3_column_int(pResults, 39);
		newSceneObject.path_node_start = sqlite3_column_int(pResults, 40);
		newSceneObject.path_node_end = sqlite3_column_int(pResults, 41);
		newSceneObject.parent_id = sqlite3_column_int(pResults, 42);
		newSceneObject.editor_wireframe = sqlite3_column_int(pResults, 43);
		newSceneObject.name = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 44));

		newSceneObject.light_type = sqlite3_column_int(pResults, 45);
		newSceneObject.light_diffuse_r = sqlite3_column_double(pResults, 46);
		newSceneObject.light_diffuse_g = sqlite3_column_double(pResults, 47);
		newSceneObject.light_diffuse_b = sqlite3_column_double(pResults, 48);
		newSceneObject.light_specular_r = sqlite3_column_double(pResults, 49);
		newSceneObject.light_specular_g = sqlite3_column_double(pResults, 50);
		newSceneObject.light_specular_b = sqlite3_column_double(pResults, 51);
		newSceneObject.light_spot_cutoff = sqlite3_column_double(pResults, 52);
		newSceneObject.light_constant = sqlite3_column_double(pResults, 53);
		newSceneObject.light_linear = sqlite3_column_double(pResults, 54);
		newSceneObject.light_quadratic = sqlite3_column_double(pResults, 55);
	

		//send completed object to scenegraph
		m_sceneGraph.push_back(newSceneObject);
	}

	//THE WORLD CHUNK
	//prepare SQL Text
	sqlCommand = "SELECT * from Chunks";				//sql command which will return all records from  chunks table. There is only one tho.
														//Send Command and fill result object
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResultsChunk, 0);


	sqlite3_step(pResultsChunk);
	m_chunk.ID = sqlite3_column_int(pResultsChunk, 0);
	m_chunk.name = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 1));
	m_chunk.chunk_x_size_metres = sqlite3_column_int(pResultsChunk, 2);
	m_chunk.chunk_y_size_metres = sqlite3_column_int(pResultsChunk, 3);
	m_chunk.chunk_base_resolution = sqlite3_column_int(pResultsChunk, 4);
	m_chunk.heightmap_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 5));
	m_chunk.tex_diffuse_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 6));
	m_chunk.tex_splat_alpha_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 7));
	m_chunk.tex_splat_1_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 8));
	m_chunk.tex_splat_2_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 9));
	m_chunk.tex_splat_3_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 10));
	m_chunk.tex_splat_4_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 11));
	m_chunk.render_wireframe = sqlite3_column_int(pResultsChunk, 12);
	m_chunk.render_normals = sqlite3_column_int(pResultsChunk, 13);
	m_chunk.tex_diffuse_tiling = sqlite3_column_int(pResultsChunk, 14);
	m_chunk.tex_splat_1_tiling = sqlite3_column_int(pResultsChunk, 15);
	m_chunk.tex_splat_2_tiling = sqlite3_column_int(pResultsChunk, 16);
	m_chunk.tex_splat_3_tiling = sqlite3_column_int(pResultsChunk, 17);
	m_chunk.tex_splat_4_tiling = sqlite3_column_int(pResultsChunk, 18);


	//Process REsults into renderable
	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);
	//build the renderable chunk 
	m_d3dRenderer.BuildDisplayChunk(&m_chunk);

}

//allows user to add new objects as needed
void ToolMain::PasteObject()
{
	int curID = 0;

	//pastes all objets currently in the selection array
	for (int i = 0; i < m_d3dRenderer.multiSelectObjIDs.size(); i++)
	{
		curID = m_d3dRenderer.multiSelectObjIDs[i];

		//creates a new object with all the same variables as the one selected
		SceneObject pastedObject = m_sceneGraph[curID];

		//add to the end of the scene graph to get a unique ID
		pastedObject.ID = m_sceneGraph.size() + 1;

		//give a slight offset to pos
		pastedObject.posX += 5;
		pastedObject.posZ += 3;
		m_sceneGraph.push_back(pastedObject);		//add new object to scene graph
	}

	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);		//add to display
}

//add a new object from the window
void ToolMain::CreateNewObject(std::string model, std::string tex, 
								DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rotation)
{
	//creates a new object with some base variables (i.e. all of the ones at the end of the DB which are the same for all objects; lights, audio, etc.)
	SceneObject newObject = m_sceneGraph[0];

	//add to the end of the scene graph to get a unique ID
	newObject.ID = m_sceneGraph.size() + 1;

	//set variables to ones passed as parameter
	newObject.posX = position.x;
	newObject.posY = position.y;
	newObject.posZ = position.z;

	newObject.scaX = scale.x;
	newObject.scaY = scale.y;
	newObject.scaZ = scale.z;

	newObject.rotX = rotation.x;
	newObject.rotY = rotation.y;
	newObject.rotZ = rotation.z;

	newObject.model_path = model;
	newObject.tex_diffuse_path = tex;

	m_sceneGraph.push_back(newObject);		//add new object to scene graph
	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);		//add to display
}

//remove an object from the scene
void ToolMain::DeleteObject()
{
	int curID = 0;

	//start from largest ID to prevent issues with scenegraph IDs changing whilst looping
	std::sort(m_d3dRenderer.multiSelectObjIDs.begin(), m_d3dRenderer.multiSelectObjIDs.end(), std::greater<int>());

	//delete all objects currently in the selection array
	for (int i = 0; i < m_d3dRenderer.multiSelectObjIDs.size(); i++)
	{
		curID = m_d3dRenderer.multiSelectObjIDs[i];

		//check to make sure it still exists (sometimes double clicking delete can cause problems)
		if (curID < m_sceneGraph.size())
		{
			m_sceneGraph.erase(m_sceneGraph.begin() + curID);		//remove the object at the selected position
		}

	}

	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);		//update display

}

void ToolMain::onActionSave()
{
	//SQL
	int rc;
	char *sqlCommand;
	char *ErrMSG = 0;
	sqlite3_stmt *pResults;								//results of the query
	

	//OBJECTS IN THE WORLD Delete them all
	//prepare SQL Text
	sqlCommand = "DELETE FROM Objects";	 //will delete the whole object table.   Slightly risky but hey.
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResults, 0);
	sqlite3_step(pResults);

	//Populate with our new objects
	std::wstring sqlCommand2;
	int numObjects = m_sceneGraph.size();	//Loop thru the scengraph.

	for (int i = 0; i < numObjects; i++)
	{
		std::stringstream command;
		command << "INSERT INTO Objects " 
			<<"VALUES(" << m_sceneGraph.at(i).ID << ","
			<< m_sceneGraph.at(i).chunk_ID  << ","
			<< "'" << m_sceneGraph.at(i).model_path <<"'" << ","
			<< "'" << m_sceneGraph.at(i).tex_diffuse_path << "'" << ","
			<< m_sceneGraph.at(i).posX << ","
			<< m_sceneGraph.at(i).posY << ","
			<< m_sceneGraph.at(i).posZ << ","
			<< m_sceneGraph.at(i).rotX << ","
			<< m_sceneGraph.at(i).rotY << ","
			<< m_sceneGraph.at(i).rotZ << ","
			<< m_sceneGraph.at(i).scaX << ","
			<< m_sceneGraph.at(i).scaY << ","
			<< m_sceneGraph.at(i).scaZ << ","
			<< m_sceneGraph.at(i).render << ","
			<< m_sceneGraph.at(i).collision << ","
			<< "'" << m_sceneGraph.at(i).collision_mesh << "'" << ","
			<< m_sceneGraph.at(i).collectable << ","
			<< m_sceneGraph.at(i).destructable << ","
			<< m_sceneGraph.at(i).health_amount << ","
			<< m_sceneGraph.at(i).editor_render << ","
			<< m_sceneGraph.at(i).editor_texture_vis << ","
			<< m_sceneGraph.at(i).editor_normals_vis << ","
			<< m_sceneGraph.at(i).editor_collision_vis << ","
			<< m_sceneGraph.at(i).editor_pivot_vis << ","
			<< m_sceneGraph.at(i).pivotX << ","
			<< m_sceneGraph.at(i).pivotY << ","
			<< m_sceneGraph.at(i).pivotZ << ","
			<< m_sceneGraph.at(i).snapToGround << ","
			<< m_sceneGraph.at(i).AINode << ","
			<< "'" << m_sceneGraph.at(i).audio_path << "'" << ","
			<< m_sceneGraph.at(i).volume << ","
			<< m_sceneGraph.at(i).pitch << ","
			<< m_sceneGraph.at(i).pan << ","
			<< m_sceneGraph.at(i).one_shot << ","
			<< m_sceneGraph.at(i).play_on_init << ","
			<< m_sceneGraph.at(i).play_in_editor << ","
			<< m_sceneGraph.at(i).min_dist << ","
			<< m_sceneGraph.at(i).max_dist << ","
			<< m_sceneGraph.at(i).camera << ","
			<< m_sceneGraph.at(i).path_node << ","
			<< m_sceneGraph.at(i).path_node_start << ","
			<< m_sceneGraph.at(i).path_node_end << ","
			<< m_sceneGraph.at(i).parent_id << ","
			<< m_sceneGraph.at(i).editor_wireframe << ","
			<< "'" << m_sceneGraph.at(i).name << "'" << ","

			<< m_sceneGraph.at(i).light_type << ","
			<< m_sceneGraph.at(i).light_diffuse_r << ","
			<< m_sceneGraph.at(i).light_diffuse_g << ","
			<< m_sceneGraph.at(i).light_diffuse_b << ","
			<< m_sceneGraph.at(i).light_specular_r << ","
			<< m_sceneGraph.at(i).light_specular_g << ","
			<< m_sceneGraph.at(i).light_specular_b << ","
			<< m_sceneGraph.at(i).light_spot_cutoff << ","
			<< m_sceneGraph.at(i).light_constant << ","
			<< m_sceneGraph.at(i).light_linear << ","
			<< m_sceneGraph.at(i).light_quadratic

			<< ")";
		std::string sqlCommand2 = command.str();
		rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand2.c_str(), -1, &pResults, 0);
		sqlite3_step(pResults);	
	}
	MessageBox(NULL, L"Objects Saved", L"Notification", MB_OK);
}

void ToolMain::onActionSaveTerrain()
{
	m_d3dRenderer.SaveDisplayChunk(&m_chunk);
}

void ToolMain::Tick(MSG *msg)
{
	//do we have a selection
	if (m_toolInputCommands.leftMouseDown)
	{
		m_selectedObject = m_d3dRenderer.MousePicking();
		m_toolInputCommands.leftMouseDown = false;
	}

	//if holding the control key
	if (m_toolInputCommands.ctrl)
	{
		//store the change in mouse pos since last frame
		//note: use -.y because moving down returns a positive, up returns negative, whereas world is the opposite
		DirectX::SimpleMath::Vector2 mouseChange = m_d3dRenderer.DragByMouse();

		//a switch state which decides whether to move, rotate or scale the object
		switch (m_toolInputCommands.currentMode)
		{
			case InputCommands::Modes::translate:
				//move object according to mouse movement
				objectTranslationDir.x = mouseChange.x * 0.05f;
				objectTranslationDir.y = -mouseChange.y * 0.05f;
				objectTranslationDir.z = m_toolInputCommands.forward - m_toolInputCommands.back;
				Translate(objectTranslationDir);	//translate the object
				break;

			case InputCommands::Modes::rotate:
				//rotate object according to mouse movement
				objectRotationDir.x = mouseChange.x * 0.05f;
				objectRotationDir.y = -mouseChange.y * 0.05f;
				objectRotationDir.z = m_toolInputCommands.forward - m_toolInputCommands.back;
				Rotate(objectRotationDir);		//rotate the object
				break;

			case InputCommands::Modes::scale:
				//scale object according to mouse movement
				objectScaleDir.x = mouseChange.x * 0.05f;
				objectScaleDir.y = -mouseChange.y * 0.05f;
				objectScaleDir.z = m_toolInputCommands.forward - m_toolInputCommands.back;
				Scale(objectScaleDir);		//scale the object
				break;

			case InputCommands::Modes::normal:
				break;
		}

		//if pressing V whilst holding ctrl, paste (pasteHeld prevents pasting multiple at once)
		if (m_toolInputCommands.paste && !m_toolInputCommands.pasteHeld)
		{
			m_toolInputCommands.pasteHeld = true;
			PasteObject();
		}
	}
	
	//reset pasteHeld when user releases
	if (!m_toolInputCommands.paste)
	{
		m_toolInputCommands.pasteHeld = false;
	}

	//delete the selected item if pressing delete
	if (m_toolInputCommands.deleteKey)
	{
		DeleteObject();
	}

	//Renderer Update Call
	m_d3dRenderer.Tick(&m_toolInputCommands);
}

void ToolMain::UpdateInput(MSG * msg)
{
	switch (msg->message)
	{
		//Global inputs,  mouse position and keys etc
	case WM_KEYDOWN:
		m_keyArray[msg->wParam] = true;
		break;

	case WM_KEYUP:
		m_keyArray[msg->wParam] = false;
		break;

	case WM_MOUSEMOVE:
		m_toolInputCommands.mouseX = GET_X_LPARAM(msg->lParam);
		m_toolInputCommands.mouseY = GET_Y_LPARAM(msg->lParam);
		break;

	case WM_LBUTTONDOWN:	//mouse button down,  you will probably need to check when its up too
		m_toolInputCommands.leftMouseDown = true;
		break;

	case WM_RBUTTONDOWN:	//right mouse button down
		m_toolInputCommands.rightMouseDown = true;
		break;

	case WM_RBUTTONUP:	//right mouse button down
		m_toolInputCommands.rightMouseDown = false;
		break;

	case WM_LBUTTONUP:	//mouse button up
		m_toolInputCommands.leftMouseDown = false;
		break;

	}
	//here we update all the actual app functionality that we want.  This information will either be used int toolmain, or sent down to the renderer (Camera movement etc
	//WASD movement
	if (m_keyArray['W'])
	{
		m_toolInputCommands.forward = true;
	}
	else m_toolInputCommands.forward = false;
	
	if (m_keyArray['S'])
	{
		m_toolInputCommands.back = true;
	}
	else m_toolInputCommands.back = false;
	if (m_keyArray['A'])
	{
		m_toolInputCommands.left = true;
	}
	else m_toolInputCommands.left = false;

	if (m_keyArray['D'])
	{
		m_toolInputCommands.right = true;
	}
	else m_toolInputCommands.right = false;

	//move cam up/down
	if (m_keyArray['E'])
	{
		m_toolInputCommands.up = true;
	}
	else m_toolInputCommands.up = false;

	if (m_keyArray['Q'])
	{
		m_toolInputCommands.down = true;
	}
	else m_toolInputCommands.down = false;

	//focus/unfocus
	if (m_keyArray['F'])
	{
		m_toolInputCommands.focus = true;
	}
	else m_toolInputCommands.focus = false;

	if (m_keyArray['R'])
	{
		m_toolInputCommands.unfocus = true;
	}
	else m_toolInputCommands.unfocus = false;

	//paste
	if (m_keyArray['V'])
	{
		m_toolInputCommands.paste = true;
	}
	else
		m_toolInputCommands.paste = false;

	//checks for control key being entered
	if (m_keyArray[17])
	{
		m_toolInputCommands.ctrl = true;
	}
	else m_toolInputCommands.ctrl = false;

	//checks for shift key being entered
	if (m_keyArray[16])
	{
		m_toolInputCommands.shift = true;
	}
	else m_toolInputCommands.shift = false;

	//checks if delete key is pressed
	if (m_keyArray[46] && !m_toolInputCommands.deleteKeyHeld)
	{
		m_toolInputCommands.deleteKey = true;
	}
	else
		m_toolInputCommands.deleteKey = false;

	m_toolInputCommands.deleteKeyHeld = m_keyArray[46];		//delete key should only fire once, this is a flag to check if held or pressed
}

//switch between modes
void ToolMain::ChangeMode(InputCommands::Modes newMode)
{
	m_toolInputCommands.currentMode = newMode;
}

//move selected object(s) around the scene
void ToolMain::Translate(DirectX::SimpleMath::Vector3 direction)
{
	int curID = 0;

	//run through all objects currently in the selection array
	for (int i = 0; i < m_d3dRenderer.multiSelectObjIDs.size(); i++)
	{
		curID = m_d3dRenderer.multiSelectObjIDs[i];		//stores the position of the object in the sceneGraph (stored in the vector)

		//checks it is within the database (below 0 = terrain)
		if (curID > 0)
		{
			SceneObject* object = &m_sceneGraph[curID]; //get a pointer to the active object in the scene graph
			object->posX += direction.x;	//move left/right based on direction (1 = right, -1 = left)
			object->posY += direction.y;	//move up/down based on direction (1 = up, -1 = down)
			object->posZ += direction.z;	//move forward/back based on direction (1 = forward, -1 = backward)

			//update the object on the display to match where it now is in the scene world
			m_d3dRenderer.UpdateDisplayList(curID, &m_sceneGraph);
		}
	}

}

//rotate selected object(s
void ToolMain::Rotate(DirectX::SimpleMath::Vector3 direction)
{
	int curID = 0;

	//run through all objects currently in the selection array
	for (int i = 0; i < m_d3dRenderer.multiSelectObjIDs.size(); i++)
	{
		curID = m_d3dRenderer.multiSelectObjIDs[i];

		//checks it is within the database (below 0 = terrain)
		if (curID > 0)
		{
			SceneObject* object = &m_sceneGraph[curID]; //get a pointer to the active object in the scene graph

			object->rotX += direction.x;	//rot in x
			object->rotY += direction.y;	//rot in y
			object->rotZ += direction.z;	//rot in z

			m_d3dRenderer.UpdateDisplayList(curID, &m_sceneGraph);
		}
	}

}

//scale selected object(s)
void ToolMain::Scale(DirectX::SimpleMath::Vector3 direction)
{
	int curID = 0;

	//run through all objects currently in the selection array
	for (int i = 0; i < m_d3dRenderer.multiSelectObjIDs.size(); i++)
	{
		curID = m_d3dRenderer.multiSelectObjIDs[i];

		//checks it is within the database (below 0 = terrain)
		if (curID > 0)
		{
			SceneObject* object = &m_sceneGraph[curID]; //get a pointer to the active object in the scene graph

			//the ifs prevent the object from flipping if scaled too small
			if (object->scaX + direction.x > 0.1)
				object->scaX += direction.x;	//scale in x based on direction (1 = wider, -1 = thinner)
			if (object->scaY + direction.y > 0.1)
				object->scaY += direction.y;	//scale in y based on direction (1 = taller, -1 = shorter)
			if (object->scaZ + direction.z > 0.1)
				object->scaZ += direction.z;	//scale in z based on direction (1 = bigger, -1 = smaller)

			m_d3dRenderer.UpdateDisplayList(curID, &m_sceneGraph);
		}
	}
}

//update variables in the camera class
void ToolMain::SetCameraVars(float speed, float standardRot, float arcballRot)
{
	m_d3dRenderer.SetCameras(speed, standardRot, arcballRot);
}