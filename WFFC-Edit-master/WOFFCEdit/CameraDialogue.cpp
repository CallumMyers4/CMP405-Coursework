#include "stdafx.h"
#include "CameraDialogue.h"

// CameraDialogue dialog

IMPLEMENT_DYNAMIC(CameraDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(CameraDialogue, CDialogEx)
	ON_COMMAND(IDOK, &CameraDialogue::End)				//OK button
	ON_COMMAND(IDCANCEL, &CameraDialogue::Cancel)		//cancel button
END_MESSAGE_MAP()

CameraDialogue::CameraDialogue(CWnd* pParent)
	: CDialogEx(IDD_DIALOG3, pParent)
{
}

CameraDialogue::CameraDialogue() : CDialogEx(IDD_DIALOG3)
{
}

CameraDialogue::~CameraDialogue()
{
}

void CameraDialogue::SetFields(ToolMain* toolMain)
{
	m_toolSystem = toolMain;		//reference to main

	//set the min/max options for each slider
	m_speedSlider.SetRangeMin(0);
	m_speedSlider.SetRangeMax(100);
	m_speedSlider.SetPos(((cameraMoveSpeed - minSpeed) / (maxSpeed - minSpeed)) * 100);

	m_standardSlider.SetRangeMin(0);
	m_standardSlider.SetRangeMax(100);
	m_standardSlider.SetPos(((standardRotSpeed - minStandard) / (maxStandard - minStandard)) * 100); // corrected here

	m_arcballSlider.SetRangeMin(0);
	m_arcballSlider.SetRangeMax(100);
	m_arcballSlider.SetPos(((arcballRotSpeed - minArcball) / (maxArcball - minArcball)) * 100); // corrected here

}

void CameraDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_speedSlider);
	DDX_Control(pDX, IDC_SLIDER2, m_standardSlider);
	DDX_Control(pDX, IDC_SLIDER3, m_arcballSlider);
}

void CameraDialogue::End()
{
	//to map 0-100, use min + (slider/100) * max - min
	cameraMoveSpeed = minSpeed + (static_cast<float>(m_speedSlider.GetPos()) / 100) * (maxSpeed - minSpeed);
	standardRotSpeed = minStandard + (static_cast<float>(m_standardSlider.GetPos()) / 100) * (maxStandard - minStandard);
	arcballRotSpeed = minArcball +  (static_cast<float>(m_arcballSlider.GetPos()) / 100) * (maxArcball - minArcball);

	m_toolSystem->SetCameraVars(cameraMoveSpeed, standardRotSpeed, arcballRotSpeed);
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void CameraDialogue::Cancel()
{
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

BOOL CameraDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CameraDialogue::PostNcDestroy()
{
}
