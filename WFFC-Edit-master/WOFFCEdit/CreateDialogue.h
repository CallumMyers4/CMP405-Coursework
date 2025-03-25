#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include <vector>

class CreateDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(CreateDialogue);

	public:
		CreateDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph);   // modal // takes in out scenegraph in the constructor
		CreateDialogue(CWnd* pParent = NULL);
		virtual ~CreateDialogue();
		void SetFields(std::vector<SceneObject>* SceneGraph, int* Selection); //passing in pointers to the data the class will operate on.


	// Dialog Data
	#ifdef AFX_DESIGN_TIME
			enum { IDD = IDD_DIALOG1 };
	#endif

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		afx_msg void End();		//kill the dialogue
		afx_msg void SelectModel();		//when user chooses a model from dropdown
		afx_msg void SelectTexture();		//when user chooses a texture from dropdown
		afx_msg void CreateObject();	//Item has been selected

		std::vector<SceneObject>* m_sceneGraph;
		std::string selectedTex, selectedModel;
		int* m_currentSelection;

		std::vector<std::string> texturePaths
		{
			"database/data/placeholder.dds",		//placeholder
			"database/data/Error.dds",				//error
			"database/data/rock.dds",				//rock
			"database/data/Tiny_skin.dds"			//tiny skin
			"database/data/ceramic.dds"				//ceramic
		};

		std::vector<std::string> modelPaths
		{
			"database/data/placeholder.cmo",		//placeholder
			"database/data/objFence.cmo",		//fence
		};

		DECLARE_MESSAGE_MAP()
	public:
		//references to dropdowns
		//https://learn.microsoft.com/en-us/cpp/mfc/reference/ccombobox-class?view=msvc-170
		CComboBox m_modelComboBox, m_textureComboBox;
		virtual BOOL OnInitDialog() override;
		virtual void PostNcDestroy();
};

INT_PTR CALLBACK SelectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);