; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COptScheduleView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OptSchedule.h"
ODLFile=OptSchedule.odl
LastPage=0

ClassCount=8
Class1=COptScheduleApp
Class2=COptScheduleDoc
Class3=COptScheduleView
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_OPTSCHTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDR_MAINFRAME (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDD_SET_MODEL_DATA
Class7=CDlgViewData
Resource7=IDD_VIEW_DATA
Class8=CDlgSetModelDescr
Resource8=IDR_OPTSCHTYPE (English (U.S.))

[CLS:COptScheduleApp]
Type=0
HeaderFile=OptSchedule.h
ImplementationFile=OptSchedule.cpp
Filter=N

[CLS:COptScheduleDoc]
Type=0
HeaderFile=OptScheduleDoc.h
ImplementationFile=OptScheduleDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_OPTIMIZATION_SET_MODEL_DATA

[CLS:COptScheduleView]
Type=0
HeaderFile=OptScheduleView.h
ImplementationFile=OptScheduleView.cpp
Filter=C
LastObject=ID_OPTIMIZATION_START


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
HeaderFile=OptSchedule.cpp
ImplementationFile=OptSchedule.cpp
Filter=D
LastObject=CAboutDlg

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

[MNU:IDR_OPTSCHTYPE]
Type=1
Class=COptScheduleView
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


[MNU:IDR_OPTSCHTYPE (English (U.S.))]
Type=1
Class=COptScheduleView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_LOAD_EXTERNAL
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_DATA_VIEW
Command17=ID_DATA_VIEW_MODEL
Command18=ID_OPTIMIZATION_SET_MODEL_DATA
Command19=ID_OPT_SET_MODEL_PAR
Command20=ID_OPT_START_GENETIC
Command21=ID_OPT_START_SIM_ANN
Command22=ID_OPT_START_TABU_SEARCH
Command23=ID_VIEW_TOOLBAR
Command24=ID_VIEW_STATUS_BAR
Command25=ID_WINDOW_NEW
Command26=ID_WINDOW_CASCADE
Command27=ID_WINDOW_TILE_HORZ
Command28=ID_WINDOW_ARRANGE
Command29=ID_APP_ABOUT
CommandCount=29

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

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_DATA_VIEW
Command3=ID_FILE_LOAD_EXTERNAL
Command4=ID_DATA_VIEW_MODEL
Command5=ID_FILE_NEW
Command6=ID_FILE_OPEN
Command7=ID_FILE_PRINT
Command8=ID_FILE_SAVE
Command9=ID_OPTIMIZATION_START
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

[DLG:IDD_VIEW_DATA]
Type=1
Class=CDlgViewData
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DATA_TREE,SysTreeView32,1350631424
Control4=IDC_TREE_PRESJECI,SysTreeView32,1350631424
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgViewData]
Type=0
HeaderFile=DlgViewData.h
ImplementationFile=DlgViewData.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgViewData

[DLG:IDD_SET_MODEL_DATA]
Type=1
Class=CDlgSetModelDescr
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SEM_LOW,edit,1350631552
Control5=IDC_SEM_UPP,edit,1350631552
Control6=IDC_BROJ_LOW,edit,1350631552
Control7=IDC_BROJ_UPP,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,button,1342177287
Control10=IDC_CHECK_OBAVEZNI,button,1342373891
Control11=IDC_CHECK_IZBORNI,button,1342373891
Control12=IDC_CHECK_HUMAN,button,1342373891
Control13=IDC_CHECK_SEMINAR,button,1342373891
Control14=IDC_CHECK_DIPLOMSKI,button,1342373891

[CLS:CDlgSetModelDescr]
Type=0
HeaderFile=DlgSetModelDescr.h
ImplementationFile=DlgSetModelDescr.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgSetModelDescr
VirtualFilter=dWC

