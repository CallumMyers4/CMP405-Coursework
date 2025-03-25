// CreateDialogue.cpp : implementation file
//

#include "stdafx.h"
#include "CreateDialogue.h"

// CreateDialogue dialog

IMPLEMENT_DYNAMIC(CreateDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(CreateDialogue, CDialogEx)
	ON_COMMAND(IDC_BUTTON2, &CreateDialogue::End)					//ok button
	ON_BN_CLICKED(IDOK, &CreateDialogue::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &CreateDialogue::Select)	//listbox
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
void CreateDialogue::SetObjectData(std::vector<SceneObject>* SceneGraph, int* selection)
{
	/*
	m_sceneGraph = SceneGraph;
	m_currentSelection = selection;

	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = m_sceneGraph->size();
	for (int i = 0; i < numSceneObjects; i++)
	{
		//easily possible to make the data string presented more complex. showing other columns.
		std::wstring listBoxEntry = std::to_wstring(m_sceneGraph->at(i).ID);
		m_listBox.AddString(listBoxEntry.c_str());
	}
	*/

	//https://stackoverflow.com/questions/21865034/how-to-set-a-default-value-for-edit-control-box-in-a-dialog-that-is-added-to-m
	GetDlgItem(IDC_EDIT1)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT2)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT3)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT4)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT5)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT6)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT7)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT8)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT9)->SetWindowText(L"0");
}


void CreateDialogue::DoDataExchange(CDataExchange* pDX)
{
	//CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST1, m_listBox);
}

void CreateDialogue::End()
{
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void CreateDialogue::Select()
{
	int index = m_listBox.GetCurSel();
	CString currentSelectionValue;

	m_listBox.GetText(index, currentSelectionValue);

	*m_currentSelection = _ttoi(currentSelectionValue);

}

BOOL CreateDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//uncomment for modal only
/*	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = m_sceneGraph->size();
	for (size_t i = 0; i < numSceneObjects; i++)
	{
		//easily possible to make the data string presented more complex. showing other columns.
		std::wstring listBoxEntry = std::to_wstring(m_sceneGraph->at(i).ID);
		m_listBox.AddString(listBoxEntry.c_str());
	}*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CreateDialogue::PostNcDestroy()
{
}




// CreateDialogue message handlers callback   - We only need this if the dailogue is being setup-with createDialogue().  We are doing
//it manually so its better to use the messagemap
/*INT_PTR CALLBACK SelectProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		//	EndDialog(hwndDlg, wParam);
			DestroyWindow(hwndDlg);
			return TRUE;


		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return TRUE;
			break;
		}
	}

	return INT_PTR();
}*/


void CreateDialogue::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}