; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgOptimizacija
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OptimiranjeRokova.h"
ODLFile=OptimiranjeRokova.odl
LastPage=0

ClassCount=6
Class1=COptRokovaApp
Class2=COptRokovaDoc
Class3=COptRokovaView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDR_MAINFRAME (English (U.S.))
Resource4=IDD_ABOUTBOX (English (U.S.))
Class6=CDlgOptimizacija
Resource5=IDD_OPTIMIZACIJA

[CLS:COptRokovaApp]
Type=0
HeaderFile=OptimiranjeRokova.h
ImplementationFile=OptimiranjeRokova.cpp
Filter=N

[CLS:COptRokovaDoc]
Type=0
HeaderFile=OptRokovaDoc.h
ImplementationFile=OptRokovaDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=COptRokovaDoc

[CLS:COptRokovaView]
Type=0
HeaderFile=OptRokovaView.h
ImplementationFile=OptRokovaView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_OPTIMIZACIJA_POKRENI




[CLS:CAboutDlg]
Type=0
HeaderFile=OptimiranjeRokova.cpp
ImplementationFile=OptimiranjeRokova.cpp
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
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=17
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_HELP_FINDER
Command17=ID_APP_ABOUT

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
CommandCount=16
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP


[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_OPTIMIZACIJA_POKRENI
Command17=ID_OPTIMIZACIJA_ZAUSTAVI
Command18=ID_HELP_FINDER
Command19=ID_APP_ABOUT
CommandCount=19

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
Command9=ID_CONTEXT_HELP
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_OPTIMIZACIJA_POKRENI
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_HELP
Command11=ID_CONTEXT_HELP
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_OPTIMIZACIJA]
Type=1
Class=CDlgOptimizacija
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PRIKAZRASPOREDAISPITACTRL1,{58E19248-A94F-4762-B543-0F1CD6C3B71D},1342242816
Control4=IDC_SCROLLBAR,{DFD181E0-5E2F-11CE-A449-00AA004A803D},1342242816

[CLS:CDlgOptimizacija]
Type=0
HeaderFile=DlgOptimizacija.h
ImplementationFile=DlgOptimizacija.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SCROLLBAR

