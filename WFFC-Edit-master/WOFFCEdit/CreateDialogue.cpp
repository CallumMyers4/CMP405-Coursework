// CreateDialogue.cpp : implementation file
//

#include "stdafx.h"
#include "CreateDialogue.h"

// CreateDialogue dialog

IMPLEMENT_DYNAMIC(CreateDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(CreateDialogue, CDialogEx)
	ON_COMMAND(IDC_BUTTON1, &CreateDialogue::CreateObject)	//create button
	ON_COMMAND(IDC_BUTTON2, &CreateDialogue::End)					//cancel/exit button
END_MESSAGE_MAP()


CreateDialogue::CreateDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph)		//constructor used in modal
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_sceneGraph = SceneGraph;
}

CreateDialogue::CreateDialogue(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG2, pParent)
{
}

CreateDialogue::~CreateDialogue()
{
}

///pass through pointers to the data in the tool we want to manipulate
void CreateDialogue::SetFields(std::vector<SceneObject>* SceneGraph, int* selection)
{
	m_sceneGraph = SceneGraph;
	m_currentSelection = selection;

	//dropdowns


	//position, rotation and scale fields
	//https://stackoverflow.com/questions/21865034/how-to-set-a-default-value-for-edit-control-box-in-a-dialog-that-is-added-to-m
	GetDlgItem(IDC_EDIT1)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT2)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT3)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT4)->SetWindowText(L"1");
	GetDlgItem(IDC_EDIT5)->SetWindowText(L"1");
	GetDlgItem(IDC_EDIT6)->SetWindowText(L"1");
	GetDlgItem(IDC_EDIT7)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT8)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT9)->SetWindowText(L"0");

	//dropdown fields
	m_modelComboBox.AddString(_T("Box"));
	m_modelComboBox.AddString(_T("Not Box"));
	m_textureComboBox.AddString(_T("Placeholder"));
	m_textureComboBox.AddString(_T("The other one"));
}


void CreateDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_modelComboBox);
	DDX_Control(pDX, IDC_COMBO2, m_textureComboBox);
}

void CreateDialogue::End()
{
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void CreateDialogue::CreateObject()
{
	/*
	int index = m_listBox.GetCurSel();
	CString currentSelectionValue;

	m_listBox.GetText(index, currentSelectionValue);

	*m_currentSelection = _ttoi(currentSelectionValue);
	*/
}

BOOL CreateDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CreateDialogue::PostNcDestroy()
{
}