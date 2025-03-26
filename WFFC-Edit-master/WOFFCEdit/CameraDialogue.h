#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include "ToolMain.h"
#include <vector>

class CameraDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(CameraDialogue);

public:
	CameraDialogue(CWnd* pParent);   // modal // takes in out scenegraph in the constructor
	CameraDialogue();
	virtual ~CameraDialogue();
	void SetFields(ToolMain* toolMain); //passing in pointers to the data the class will operate on.

	float cameraMoveSpeed, standardRotSpeed, arcballRotSpeed;	//store the user-defined values for movement/rotation speeds


	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End();		//kill the dialogue
	afx_msg void Cancel();		//kill the dialogue

	ToolMain* m_toolSystem;

	//get ranges for each value since CSlider only allows int values, doesnt return floats
	float minSpeed = 1.0f, maxSpeed = 3.0f, minStandard =0.1f, maxStandard = 1.0f, minArcball = 0.001f, maxArcball = 0.01f;

	DECLARE_MESSAGE_MAP()

public:
	//references to sliders
	//https://learn.microsoft.com/en-us/cpp/mfc/reference/csliderctrl-class?view=msvc-170
	CSliderCtrl m_speedSlider, m_standardSlider, m_arcballSlider;
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
};

INT_PTR CALLBACK SelectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);