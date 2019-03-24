// TestNumFrameworkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestNumFramework.h"
#include "TestNumFrameworkDlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

IMPLEMENT_DYNAMIC(CTestDlg, CDialog);

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_strEdit = _T("");
	m_lStart = 0;
	m_lEnd = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;

	pSolver = NULL;

	m_lEnd = 1000000;
}

CTestDlg::~CTestDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_CMD_STOP, m_cmdStop);
	DDX_Control(pDX, IDC_CMD_CONTINUE, m_cmdContinue);
	DDX_Control(pDX, IDC_EDIT_LAST_FOUND, m_ctrlLastFound);
	DDX_Control(pDX, IDC_CMD_START, m_cmdStart);
	DDX_Text(pDX, IDC_EDIT, m_strEdit);
	DDX_Text(pDX, IDC_EDIT_START, m_lStart);
	DDX_Text(pDX, IDC_EDIT_END, m_lEnd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CMD_START, OnCmdStart)
  ON_MESSAGE(WM_REFRESH_MESSAGE , OnRefreshMessage)
	ON_BN_CLICKED(IDC_CMD_STOP, OnCmdStop)
	ON_BN_CLICKED(IDC_CMD_CONTINUE, OnCmdContinue)
	ON_BN_CLICKED(IDC_CMD_TERMINATE, OnCmdTerminate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CTestDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CTestDlg::OnOK() 
{
	if (CanExit())
		CDialog::OnOK();
}

void CTestDlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CTestDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


LRESULT	CTestDlg::OnRefreshMessage(WPARAM wParam, LPARAM lParam)
{
	long		res;
	char		str[100];

	GetExchangePtr()->GetResult(&res);
	sprintf(str, "%ld", res);
	m_ctrlLastFound.SetWindowText(str);

	return 1;
}

void CTestDlg::AddCalcResult( long &res )
{
	vecResult.push_back(res);
}

void CTestDlg::OnCmdStart() 
{
	UpdateData(TRUE);

	long	start, end;
	
	start = m_lStart;
	end		= m_lEnd;

	if( pSolver == NULL )
	{
		CreateExchangeObject(this->m_hWnd);

		pSolver = new ThreadablePrimSolver(GetExchangePtr(), this, start, end);
		pSolver->Start();
	}
	else {
	}
}

void CTestDlg::OnCmdStop() 
{
	if( pSolver != NULL )
		pSolver->Stop();
}

void CTestDlg::OnCmdContinue() 
{
	if( pSolver != NULL )
		pSolver->Continue();
}

void CTestDlg::OnCmdTerminate() 
{
	if( pSolver	!= NULL ) {
		pSolver->Terminate();
	
		delete pSolver;
		pSolver = NULL;
	}
}