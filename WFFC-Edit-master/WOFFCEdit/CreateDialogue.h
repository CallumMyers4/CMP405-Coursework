#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include "ToolMain.h"
#include <vector>

class CreateDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(CreateDialogue);

	public:
		CreateDialogue(CWnd* pParent);   // modal // takes in out scenegraph in the constructor
		CreateDialogue();
		virtual ~CreateDialogue();
		void SetFields(ToolMain* toolMain); //passing in pointers to the data the class will operate on.

		std::string selectedTex, selectedModel;		//the paths to selected texture/model
		DirectX::SimpleMath::Vector3 position, rotation, scale;		//the paths to selected texture/model


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

		ToolMain* m_toolSystem;

		DECLARE_MESSAGE_MAP()

	public:
		//references to dropdowns
		//https://learn.microsoft.com/en-us/cpp/mfc/reference/ccombobox-class?view=msvc-170
		CComboBox m_modelComboBox, m_textureComboBox;
		virtual BOOL OnInitDialog() override;
		virtual void PostNcDestroy();
};

INT_PTR CALLBACK SelectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);