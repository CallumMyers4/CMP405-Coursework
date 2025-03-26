//
// Game.h
//

/* code for outputting to debug, remove in final build
		// Prepare the formatted debug message
		wchar_t buffer[512];  // Buffer for formatted string

		// Debug message for "false"
		swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"Debug: The value of Y is %f\n");
		OutputDebugString(buffer);  // Output to the Debug window

*/

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "SceneObject.h"
#include "DisplayObject.h"
#include "DisplayChunk.h"
#include "ChunkObject.h"
#include "InputCommands.h"
#include "Camera.h"
#include <vector>

//struct to store details of object currently being selected
struct SelectedObjectStruct 
{
	int selectedId;
	std::string modelPath;	//the path to the model
	std::string texturePath;	//the path to the texture
	DirectX::SimpleMath::Vector3 position;	//objects position
	DirectX::SimpleMath::Vector3 rotation;	//objects rotation
	DirectX::SimpleMath::Vector3 scale;		//objects scale
};

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

	Game();
	~Game();

	// Initialization and management
	void Initialize(HWND window, int width, int height);
	void SetGridState(bool state);

	// Basic game loop
	void Tick(InputCommands * Input);
	void Render();

	// Rendering helpers
	void Clear();

	// IDeviceNotify
	virtual void OnDeviceLost() override;
	virtual void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);

	//tool specific
	void BuildDisplayList(std::vector<SceneObject> * SceneGraph); //note vector passed by reference 
	void BuildDisplayChunk(ChunkObject *SceneChunk);
	void SaveDisplayChunk(ChunkObject *SceneChunk);	//saves geometry et al
	void UpdateDisplayList(int objectID, std::vector<SceneObject>* sceneGraph);		//display new objects as they are moved

	//object selection
	int	 MousePicking();
	SelectedObjectStruct selectedObject;		//store the variables of the object currently being selected

	//move objects
	DirectX::SimpleMath::Vector2 DragByMouse();		//return the mouse movement since the last frame
	POINT prevMousePos{ 0, 0};		//get the point of the mouse during the last frame

	RECT		m_ScreenDimensions;

	//empty camera which will store the variables of the camera currently active
	Camera mainCamera;
	void SetCameras(float speed, float standardRot, float arcballRot);		//pass over the new variables from window

	//store all objects currently selected
	std::vector<int> multiSelectObjIDs;

#ifdef DXTK_AUDIO
	void NewAudioDevice();
#endif

private:

	void Update(DX::StepTimer const& timer);

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	void XM_CALLCONV DrawGrid(DirectX::FXMVECTOR xAxis, DirectX::FXMVECTOR yAxis, DirectX::FXMVECTOR origin, size_t xdivs, size_t ydivs, DirectX::GXMVECTOR color);

	//tool specific
	std::vector<DisplayObject>			m_displayList;
	DisplayChunk						m_displayChunk;
	InputCommands						m_InputCommands;

	//cameras (the camera for focusing on objects and the normal one which allows user to move around the scene)
	Camera focusCamera, standardCamera;

	//control variables
	bool m_grid;							//grid rendering on / off
	HWND wind;		//a reference to the window (couldn't find any GetWindow() functions)
	int selectedID = 0;						//the ID of the object currently selected

	// Device resources.
    std::shared_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    // Input devices.
    std::unique_ptr<DirectX::GamePad>       m_gamePad;
    std::unique_ptr<DirectX::Keyboard>      m_keyboard;
	std::unique_ptr<DirectX::Mouse>			m_mouse;

    // DirectXTK objects.
    std::unique_ptr<DirectX::CommonStates>                                  m_states;
    std::unique_ptr<DirectX::BasicEffect>                                   m_batchEffect;
    std::unique_ptr<DirectX::EffectFactory>                                 m_fxFactory;
    std::unique_ptr<DirectX::GeometricPrimitive>                            m_shape;
    std::unique_ptr<DirectX::Model>                                         m_model;
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>  m_batch;
    std::unique_ptr<DirectX::SpriteBatch>                                   m_sprites;
    std::unique_ptr<DirectX::SpriteFont>                                    m_font;

#ifdef DXTK_AUDIO
    std::unique_ptr<DirectX::AudioEngine>                                   m_audEngine;
    std::unique_ptr<DirectX::WaveBank>                                      m_waveBank;
    std::unique_ptr<DirectX::SoundEffect>                                   m_soundEffect;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect1;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect2;
#endif

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture1;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture2;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>                               m_batchInputLayout;

#ifdef DXTK_AUDIO
    uint32_t                                                                m_audioEvent;
    float                                                                   m_audioTimerAcc;

    bool                                                                    m_retryDefault;
#endif

    DirectX::SimpleMath::Matrix                                             m_world;
    DirectX::SimpleMath::Matrix                                             m_projection;
};

std::wstring StringToWCHART(std::string s);