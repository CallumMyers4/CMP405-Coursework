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
	ON_CBN_SELCHANGE(IDC_COMBO1, &CreateDialogue::SelectModel)	//model dropdown selected
	ON_CBN_SELCHANGE(IDC_COMBO2, &CreateDialogue::SelectTexture)	//model dropdown selected
END_MESSAGE_MAP()


CreateDialogue::CreateDialogue(CWnd* pParent)		//constructor used in modal
	: CDialogEx(IDD_DIALOG2, pParent)
{
}

CreateDialogue::CreateDialogue() : CDialogEx(IDD_DIALOG2)
{
}

CreateDialogue::~CreateDialogue()
{
}

///pass through pointers to the data in the tool we want to manipulate
void CreateDialogue::SetFields(ToolMain* toolMain)
{
	m_toolSystem = toolMain;		//refernce to the toolMain class (for making new objects)

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
	//models
	m_modelComboBox.AddString(_T("Box"));
	m_modelComboBox.AddString(_T("Fence"));
	m_modelComboBox.SetCurSel(0);	//default value

	//textures
	m_textureComboBox.AddString(_T("Placeholder"));
	m_textureComboBox.AddString(_T("Error"));
	m_textureComboBox.AddString(_T("Rock"));
	m_textureComboBox.AddString(_T("Tiny Skin"));
	m_textureComboBox.AddString(_T("Ceramic"));
	m_textureComboBox.SetCurSel(0);

	//give default values to prevent errors
	selectedModel = modelPaths[0];
	selectedTex = modelPaths[0];
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

//get the selected model from dropdown
void CreateDialogue::SelectModel()
{
	int selection = m_modelComboBox.GetCurSel();

	selectedModel = modelPaths[selection];
}

//get the selected tex from dropdown
void CreateDialogue::SelectTexture()
{
	int selection = m_textureComboBox.GetCurSel();

	selectedTex = texturePaths[selection];
}

//make object from fields in the window
void CreateDialogue::CreateObject()
{
	CString input;

	//get values from input boxes
	GetDlgItem(IDC_EDIT1)->GetWindowText(input);
	position.x = _ttoi(input);
	GetDlgItem(IDC_EDIT2)->GetWindowText(input);
	position.y = _ttoi(input);
	GetDlgItem(IDC_EDIT3)->GetWindowText(input);
	position.z = _ttoi(input);

	GetDlgItem(IDC_EDIT4)->GetWindowText(input);
	scale.x = _ttoi(input);
	GetDlgItem(IDC_EDIT5)->GetWindowText(input);
	scale.y = _ttoi(input);
	GetDlgItem(IDC_EDIT6)->GetWindowText(input);
	scale.z = _ttoi(input);

	GetDlgItem(IDC_EDIT7)->GetWindowText(input);
	rotation.x = _ttoi(input);
	GetDlgItem(IDC_EDIT8)->GetWindowText(input);
	rotation.y = _ttoi(input);
	GetDlgItem(IDC_EDIT9)->GetWindowText(input);
	rotation.z = _ttoi(input);

	//create a new object with parameters from the fields
	m_toolSystem->CreateNewObject(selectedModel, selectedTex, position, scale, rotation);

	End();
}

BOOL CreateDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CreateDialogue::PostNcDestroy()
{
}