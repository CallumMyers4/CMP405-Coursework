#include "ObjectCreation.h"
#include "stdafx.h"


IMPLEMENT_DYNAMIC(ObjectCreation, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(ObjectCreation, CDialogEx)
	ON_COMMAND(IDOK, &ObjectCreation::End)					//ok button
	ON_BN_CLICKED(IDOK, &ObjectCreation::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &ObjectCreation::Select)	//listbox
END_MESSAGE_MAP()


ObjectCreation::ObjectCreation(CWnd* pParent, std::vector<SceneObject>* SceneGraph)		//constructor used in modal
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_sceneGraph = SceneGraph;
}

ObjectCreation::ObjectCreation(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

ObjectCreation::~ObjectCreation()
{
}

///pass through pointers to the data in the tool we want to manipulate
void ObjectCreation::SetObjectData(std::vector<SceneObject>* SceneGraph, int* selection)
{
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
}


void ObjectCreation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
}

void ObjectCreation::End()
{
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void ObjectCreation::Select()
{
	int index = m_listBox.GetCurSel();
	CString currentSelectionValue;

	m_listBox.GetText(index, currentSelectionValue);

	*m_currentSelection = _ttoi(currentSelectionValue);

}

BOOL ObjectCreation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void ObjectCreation::PostNcDestroy()
{
}


void ObjectCreation::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

