; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSchEqDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SchroedingerEq.h"
LastPage=0

ClassCount=10
Class1=CSchEqApp
Class2=CSchEqDoc
Class3=CSchEqView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_SCHROETYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDR_SCHROETYPE (English (U.S.))
Resource5=IDD_OPTIONS
Resource6=IDD_ABOUTBOX (English (U.S.))
Class7=CDlgDefineParameters
Resource7=IDD_VIEW_RESULTS
Class8=CDlgPerformIntegration
Resource8=IDD_PERFORM_INTEGRATION
Class9=CDlgViewResults
Resource9=IDD_DEFINE_PAR
Class10=CDlgOptions
Resource10=IDR_MAINFRAME (English (U.S.))

[CLS:CSchEqApp]
Type=0
HeaderFile=SchroedingerEq.h
ImplementationFile=SchroedingerEq.cpp
Filter=N

[CLS:CSchEqDoc]
Type=0
HeaderFile=SchEqDoc.h
ImplementationFile=SchEqDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_OPTIONS

[CLS:CSchEqView]
Type=0
HeaderFile=SchEqView.h
ImplementationFile=SchEqView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=IDC_OPT_PERT_FUNC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=SchroedingerEq.cpp
ImplementationFile=SchroedingerEq.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
CommandCount=8
Command8=ID_APP_ABOUT

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_SCHROETYPE]
Type=1
Class=CSchEqView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
CommandCount=21
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_SCHROETYPE (English (U.S.))]
Type=1
Class=CSchEqView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_DEFINE_PARAMETERS
Command16=ID_PERFORM_INTEGRATION
Command17=ID_CALCULATE_PERTURBATION
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_VIEW_RESULTS
Command21=ID_DRAW_METAFILE
Command22=ID_OPTIONS
Command23=ID_WINDOW_NEW
Command24=ID_WINDOW_CASCADE
Command25=ID_WINDOW_TILE_HORZ
Command26=ID_WINDOW_ARRANGE
Command27=ID_APP_ABOUT
CommandCount=27

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_DEFINE_PARAMETERS
Command3=ID_PERFORM_INTEGRATION
Command4=ID_DRAW_METAFILE
Command5=ID_FILE_NEW
Command6=ID_FILE_OPEN
Command7=ID_FILE_PRINT
Command8=ID_VIEW_RESULTS
Command9=ID_FILE_SAVE
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=ID_EDIT_CUT
Command18=ID_EDIT_UNDO
CommandCount=18

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DEFINE_PAR]
Type=1
Class=CDlgDefineParameters
ControlCount=13
Control1=IDC_EDIT_FINITE_A1,edit,1350631552
Control2=IDC_EDIT_FINITE_B1,edit,1350631552
Control3=IDC_EDIT_FINITE_A2,edit,1350631552
Control4=IDC_EDIT_FINITE_B2,edit,1350631552
Control5=IDC_EDIT_FINITE_V0,edit,1350631552
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352

[CLS:CDlgDefineParameters]
Type=0
HeaderFile=DlgDefineParameters.h
ImplementationFile=DlgDefineParameters.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgDefineParameters
VirtualFilter=dWC

[DLG:IDD_PERFORM_INTEGRATION]
Type=1
Class=CDlgPerformIntegration
ControlCount=11
Control1=IDC_EDIT_NORM,edit,1350631552
Control2=IDC_EDIT_E_START,edit,1350631552
Control3=IDC_EDIT_E_END,edit,1350631552
Control4=IDC_EDIT_E_STEP,edit,1350631552
Control5=IDC_EDIT_E_VALUES,edit,1350631552
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352

[CLS:CDlgPerformIntegration]
Type=0
HeaderFile=DlgPerformIntegration.h
ImplementationFile=DlgPerformIntegration.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_VIEW_RESULTS]
Type=1
Class=CDlgViewResults
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST,SysListView32,1350633473
Control4=IDC_LIST2,SysListView32,1350631425

[CLS:CDlgViewResults]
Type=0
HeaderFile=DlgViewResults.h
ImplementationFile=DlgViewResults.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgViewResults

[DLG:IDD_OPTIONS]
Type=1
Class=CDlgOptions
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_OPT_NUM_INT,button,1342308361
Control7=IDC_OPT_PERT_FUNC,button,1342308361

[CLS:CDlgOptions]
Type=0
HeaderFile=DlgOptions.h
ImplementationFile=DlgOptions.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

