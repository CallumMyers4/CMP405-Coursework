#pragma once

#include <afxwin.h> 
#include <afxext.h>
#include <afx.h>
#include "pch.h"
#include "Game.h"
#include "ToolMain.h"
#include "resource.h"
#include "MFCFrame.h"
#include "SelectDialogue.h"
#include "CreateDialogue.h"
#include "CameraDialogue.h"


class MFCMain : public CWinApp 
{
public:
	MFCMain();
	~MFCMain();
	BOOL InitInstance();
	int  Run();

private:

	CMyFrame * m_frame;	//handle to the frame where all our UI is
	HWND m_toolHandle;	//Handle to the MFC window
	ToolMain m_ToolSystem;	//Instance of Tool System that we interface to. 
	CRect WindowRECT;	//Window area rectangle. 
	SelectDialogue m_ToolSelectDialogue;			//for modeless dialogue, declare it here
	CreateDialogue m_ToolCreateDialogue;			//for modeless dialogue, declare it here
	CameraDialogue m_ToolCameraDialogue;			//for modeless dialogue, declare it here
	int m_width;		
	int m_height;
	
	//Interface funtions for menu and toolbar etc requires
	afx_msg void MenuFileQuit();
	afx_msg void MenuFileSaveTerrain();
	afx_msg void MenuFileCameraControls();
	afx_msg void MenuEditSelect();
	afx_msg	void ToolBarButton1();
	afx_msg void PasteSelected();
	afx_msg void MenuEditCreate();

	//switch between modes
	afx_msg void NormalMode();
	afx_msg void TranslateMode();
	afx_msg void RotateMode();
	afx_msg void ScaleMode();


	DECLARE_MESSAGE_MAP()	// required macro for message map functionality  One per class
};
