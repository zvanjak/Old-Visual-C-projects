// DlgSetProblemInstances.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "DlgSetProblemInstances.h"

#include <QAP\QAP.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetProblemInstances dialog


CDlgSetProblemInstances::CDlgSetProblemInstances(CQAPCompareDoc	*inpDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetProblemInstances::IDD, pParent)
{
	pDoc = inpDoc;

	//{{AFX_DATA_INIT(CDlgSetProblemInstances)
	//}}AFX_DATA_INIT

	CString		str;

	for( int i=0; i<10; i++ ) {
		m_strFile[i] = "";

		str.Format("%d", (i+1)*10 );
		m_strLabel[i] = str;
	}
}


void CDlgSetProblemInstances::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetProblemInstances)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_FILENAME1, m_strFile[0]);
	DDX_Text(pDX, IDC_EDIT_FILENAME2, m_strFile[1]);
	DDX_Text(pDX, IDC_EDIT_FILENAME3, m_strFile[2]);
	DDX_Text(pDX, IDC_EDIT_FILENAME4, m_strFile[3]);
	DDX_Text(pDX, IDC_EDIT_FILENAME5, m_strFile[4]);
	DDX_Text(pDX, IDC_EDIT_FILENAME6, m_strFile[5]);
	DDX_Text(pDX, IDC_EDIT_FILENAME7, m_strFile[6]);
	DDX_Text(pDX, IDC_EDIT_FILENAME8, m_strFile[7]);
	DDX_Text(pDX, IDC_EDIT_FILENAME9, m_strFile[8]);
	DDX_Text(pDX, IDC_EDIT_FILENAME10, m_strFile[9]);
	
	DDX_Text(pDX, IDC_STATIC1, m_strLabel[0]);
	DDX_Text(pDX, IDC_STATIC2, m_strLabel[1]);
	DDX_Text(pDX, IDC_STATIC3, m_strLabel[2]);
	DDX_Text(pDX, IDC_STATIC4, m_strLabel[3]);
	DDX_Text(pDX, IDC_STATIC5, m_strLabel[4]);
	DDX_Text(pDX, IDC_STATIC6, m_strLabel[5]);
	DDX_Text(pDX, IDC_STATIC7, m_strLabel[6]);
	DDX_Text(pDX, IDC_STATIC8, m_strLabel[7]);
	DDX_Text(pDX, IDC_STATIC9, m_strLabel[8]);
	DDX_Text(pDX, IDC_STATIC10, m_strLabel[9]);
}


BEGIN_MESSAGE_MAP(CDlgSetProblemInstances, CDialog)
	//{{AFX_MSG_MAP(CDlgSetProblemInstances)
	ON_BN_CLICKED(IDC_BROWSE_CMD1, OnBrowseCmd1)
	ON_BN_CLICKED(IDC_BROWSE_CMD2, OnBrowseCmd2)
	ON_BN_CLICKED(IDC_BROWSE_CMD3, OnBrowseCmd3)
	ON_BN_CLICKED(IDC_BROWSE_CMD4, OnBrowseCmd4)
	ON_BN_CLICKED(IDC_BROWSE_CMD5, OnBrowseCmd5)
	ON_BN_CLICKED(IDC_BROWSE_CMD6, OnBrowseCmd6)
	ON_BN_CLICKED(IDC_BROWSE_CMD7, OnBrowseCmd7)
	ON_BN_CLICKED(IDC_BROWSE_CMD8, OnBrowseCmd8)
	ON_BN_CLICKED(IDC_BROWSE_CMD9, OnBrowseCmd9)
	ON_BN_CLICKED(IDC_BROWSE_CMD10, OnBrowseCmd10)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD, OnLoadBestsolCmd1)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD10, OnLoadBestsolCmd10)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD2, OnLoadBestsolCmd2)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD3, OnLoadBestsolCmd3)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD4, OnLoadBestsolCmd4)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD5, OnLoadBestsolCmd5)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD6, OnLoadBestsolCmd6)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD7, OnLoadBestsolCmd7)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD8, OnLoadBestsolCmd8)
	ON_BN_CLICKED(IDC_LOAD_BESTSOL_CMD9, OnLoadBestsolCmd9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetProblemInstances message handlers

void CDlgSetProblemInstances::Load( int ind ) 
{
	int						Size;
	CString				strFileName;
	CFileDialog		dlgFileOpen(TRUE);	

	if( dlgFileOpen.DoModal() == IDOK ) 
	{
		strFileName = dlgFileOpen.GetPathName();
		if( strFileName.IsEmpty() != TRUE ) 
		{
			m_strFile[ind] = strFileName;

			Math::Matrix<float>		A, B;
			if( LoadProblem(strFileName.GetBuffer(200), &Size, &A, &B) == 0 ) 
			{
				pDoc->vecProblemDefined[ind] = TRUE;

				pDoc->vecA[ind] = A;
				pDoc->vecB[ind] = B;

				CString	strSize;
				strSize.Format(_T("%d"), Size);
				m_strLabel[ind] = strSize;
			}
			else
				AfxMessageBox("Nije uspjelo uèitavanje !!!");

			UpdateData(FALSE);
		}
	}
}

void CDlgSetProblemInstances::LoadBestSolution( int ind ) 
{
	FILE					*fp;
	CString				strFileName;
	CFileDialog		dlgFileOpen(TRUE);	

	if( dlgFileOpen.DoModal() == IDOK ) 
	{
		strFileName = dlgFileOpen.GetPathName();
		if( strFileName.IsEmpty() != TRUE ) 
		{
			if( (fp=fopen(strFileName.GetBuffer(200), "r")) != NULL ) {
				int			Size;
				float		BestValue;

				fscanf(fp, "%d", &Size);
				fscanf(fp, "%f", &BestValue);
				
				int		num = 0;
				QAPSolution		SolLoad(Size);

				SolLoad.setValue(BestValue);
				for( int i=1; i<=Size; i++ )
					num += fscanf(fp, "%d", &SolLoad[i] );

				if( num == Size ) {
					pDoc->vecBestKnownSolLoaded[ind] = TRUE;
					pDoc->vecBestKnownSol[ind] = SolLoad;
				}
			}
			else
				AfxMessageBox("Nisam uspio otvoriti datoteku !!!");

			UpdateData(FALSE);
		}
	}
}

void CDlgSetProblemInstances::OnBrowseCmd1() 
{
	Load(0);
}

void CDlgSetProblemInstances::OnBrowseCmd2() 
{
	Load(1);
}

void CDlgSetProblemInstances::OnBrowseCmd3() 
{
	Load(2);
}

void CDlgSetProblemInstances::OnBrowseCmd4() 
{
	Load(3);
}

void CDlgSetProblemInstances::OnBrowseCmd5() 
{
	Load(4);
}

void CDlgSetProblemInstances::OnBrowseCmd6() 
{
	Load(5);
}

void CDlgSetProblemInstances::OnBrowseCmd7() 
{
	Load(6);
}

void CDlgSetProblemInstances::OnBrowseCmd8() 
{
	Load(7);
}

void CDlgSetProblemInstances::OnBrowseCmd9() 
{
	Load(8);
}

void CDlgSetProblemInstances::OnBrowseCmd10() 
{
	Load(9);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd1() 
{
	LoadBestSolution(0);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd2() 
{
	LoadBestSolution(1);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd3() 
{
	LoadBestSolution(2);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd4() 
{
	LoadBestSolution(3);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd5() 
{
	LoadBestSolution(4);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd6() 
{
	LoadBestSolution(5);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd7() 
{
	LoadBestSolution(6);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd8() 
{
	LoadBestSolution(7);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd9() 
{
	LoadBestSolution(8);
}

void CDlgSetProblemInstances::OnLoadBestsolCmd10() 
{
	LoadBestSolution(9);
}