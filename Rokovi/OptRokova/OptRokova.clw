; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COptRokDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OptRokova.h"
LastPage=0

ClassCount=14
Class1=COptRokApp
Class2=COptRokDoc
Class3=COptRokView
Class4=CMainFrame

ResourceCount=13
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_OPTIMIZACIJA
Resource4=IDD_POPIS_ISPITA
Class6=CDlgParamOptimizacije
Resource5=IDD_PREGLED_PO_SMJEROVIMA
Class7=CDlgParametriRoka
Resource6=IDD_PREGLED_SMJER_GOD_VIZ
Class8=CDlgOptim
Resource7=IDD_PREGLED_ISPITI_ISTI_DAN
Class9=CDlgPopisIspita
Resource8=IDD_VIZUALNI_PRIKAZ
Class10=CDlgVizualniPrikaz
Resource9=IDD_PARAMETRI_OPTIMIZACIJE
Class11=CDlgIspitiIstiDan
Resource10=IDD_PARAMETRI_ROKA
Class12=CDlgPregledZelja
Resource11=IDD_PREGLED_SA_ZELJAMA
Class13=CPregledSmjeroviGodinaDlg
Resource12=IDD_ABOUTBOX (English (U.S.))
Class14=CDlgPregledSmjerGodinaVizualno
Resource13=IDR_MAINFRAME (English (U.S.))

[CLS:COptRokApp]
Type=0
HeaderFile=OptRokova.h
ImplementationFile=OptRokova.cpp
Filter=N

[CLS:COptRokDoc]
Type=0
HeaderFile=OptRokDoc.h
ImplementationFile=OptRokDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=COptRokDoc

[CLS:COptRokView]
Type=0
HeaderFile=OptRokView.h
ImplementationFile=OptRokView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_PREGLED_PO_SMJEROVIMA
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=OptRokova.cpp
ImplementationFile=OptRokova.cpp
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
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

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


[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_WRITE_ASCII
Command6=ID_ASCII_DAT_SMJER_GOD
Command7=ID_FILE_EXPORT
Command8=ID_UCITAJ_NAZIVE_ISPITA
Command9=ID_UCITAJ_NAST_PLAN
Command10=ID_UCITAJ_PRESJEK_STUDENATA
Command11=ID_FILE_PRINT
Command12=ID_FILE_PRINT_PREVIEW
Command13=ID_FILE_PRINT_SETUP
Command14=ID_FILE_MRU_FILE1
Command15=ID_APP_EXIT
Command16=ID_EDIT_UNDO
Command17=ID_EDIT_CUT
Command18=ID_EDIT_COPY
Command19=ID_EDIT_PASTE
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_PREGLEDAJ_ISPITE
Command23=ID_PREGLEDAJ_PRESJEK
Command24=ID_PREGLED_ISPITI_ISTI_DAN
Command25=ID_PARAM_OPTIMIZACIJE
Command26=ID_PARAM_ROKA
Command27=ID_SIFRE_ISTIH
Command28=ID_ISPITI_ISTI_DAN
Command29=ID_OPTIMIZACIJA_POKRENI
Command30=ID_OPTIMIZACIJA_ZAUSTAVI
Command31=ID_VIZUALNI_PRIKAZ
Command32=ID_REZULTATI_PREGLED_PO_SEMESTRIMA
Command33=ID_REZULTATI_PREGLED_PO_ISPITIMA
Command34=ID_REZULTATI_PREGLED_PO_GRUPAMA_PREDMETA
Command35=ID_PREGLED_ISPUNJ_ZELJA_PROF
Command36=ID_PREGLED_PO_SMJEROVIMA
Command37=ID_PREGLED_SMJEROVI_GODINE
Command38=ID_PREGLED_SMJER_GOD_VIZUALNO
Command39=ID_APP_ABOUT
CommandCount=39

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

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_PARAM_OPTIMIZACIJE
Command2=ID_EDIT_COPY
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_PARAM_ROKA
Command7=ID_FILE_SAVE
Command8=ID_OPTIMIZACIJA_POKRENI
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
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

[DLG:IDD_PARAMETRI_OPTIMIZACIJE]
Type=1
Class=CDlgParamOptimizacije
ControlCount=32
Control1=IDC_VEL_POP,edit,1350631552
Control2=IDC_ITER_NUM,edit,1350631552
Control3=IDC_MUTACIJA,edit,1350631552
Control4=IDC_EXP_UDALJ,edit,1350631552
Control5=IDC_KAZNA_PODROKOVI,edit,1350631552
Control6=IDC_KAZNA_MIN_DIST,edit,1350631552
Control7=IDC_KAZNA_MAX_OPTEREC_GRUPA_PRED,edit,1350631552
Control8=IDC_NAGRADA_ISTI_DAN,edit,1350631552
Control9=IDC_AMP_BLIZINE,edit,1350631552
Control10=IDC_AMP_PRESJEK,edit,1350631552
Control11=IDC_MIN_DIST,edit,1350631552
Control12=IDC_MIN_PRESJEK,edit,1350631552
Control13=IDC_MAX_OPTEREC_GRUPA_PRED,edit,1350631552
Control14=IDC_MAX_ISP,edit,1350631552
Control15=IDC_KAZNA_MAX_ISP,edit,1350631552
Control16=IDOK,button,1342242817
Control17=IDCANCEL,button,1342242816
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352

[CLS:CDlgParamOptimizacije]
Type=0
HeaderFile=DlgParamOptimizacije.h
ImplementationFile=DlgParamOptimizacije.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_MAX_ISP

[DLG:IDD_PARAMETRI_ROKA]
Type=1
Class=CDlgParametriRoka
ControlCount=14
Control1=IDC_ROK_LJETNI,button,1342373891
Control2=IDC_ROK_JESENSKI,button,1342373891
Control3=IDC_ROK_JESENSKI_IZV,button,1342373891
Control4=IDC_ROK_ZIMSKI,button,1342373891
Control5=IDC_ROK_PROLJETNI,button,1342373891
Control6=IDC_DATUM_POCETKA,SysMonthCal32,1342242832
Control7=IDC_DATUM_ZAVRSETKA,SysMonthCal32,1342242832
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342177280
Control12=IDC_STATIC,static,1342177280
Control13=IDC_STATIC,static,1342308352
Control14=IDC_BROJ_ROKOVA,edit,1350631552

[CLS:CDlgParametriRoka]
Type=0
HeaderFile=DlgParametriRoka.h
ImplementationFile=DlgParametriRoka.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_OPTIMIZACIJA]
Type=1
Class=CDlgOptim
ControlCount=7
Control1=IDC_STOP,button,1342242816
Control2=IDC_RECT,static,1073741830
Control3=IDC_PROGRESS1,msctls_progress32,1350565888
Control4=IDC_VSCROLL,{DFD181E0-5E2F-11CE-A449-00AA004A803D},1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_NASTAVI,button,1342242816
Control7=IDC_OPT_PROMIJENI_PAR,button,1342242817

[CLS:CDlgOptim]
Type=0
HeaderFile=DlgOptim.h
ImplementationFile=DlgOptim.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_VSCROLL

[DLG:IDD_POPIS_ISPITA]
Type=1
Class=CDlgPopisIspita
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GRID,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_CHECK_DANI,button,1342242819
Control6=IDC_CHECK_DATUMI,button,1342242819

[CLS:CDlgPopisIspita]
Type=0
HeaderFile=DlgPopisIspita.h
ImplementationFile=DlgPopisIspita.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgPopisIspita

[DLG:IDD_VIZUALNI_PRIKAZ]
Type=1
Class=CDlgVizualniPrikaz
ControlCount=9
Control1=IDC_OK,button,1342242816
Control2=IDC_STATIC,static,1342177286
Control3=IDC_VIZPRIKAZ_VSCROLL,{DFD181E0-5E2F-11CE-A449-00AA004A803D},1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_CHECK_JESIZV,button,1342373891
Control6=IDC_CHECK_ZIM,button,1342373891
Control7=IDC_CHECK_PROLJ,button,1342373891
Control8=IDC_CHECK_LJET,button,1342373891
Control9=IDC_CHECK_JES,button,1342373891

[CLS:CDlgVizualniPrikaz]
Type=0
HeaderFile=DlgVizualniPrikaz.h
ImplementationFile=DlgVizualniPrikaz.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK_JES

[DLG:IDD_PREGLED_ISPITI_ISTI_DAN]
Type=1
Class=CDlgIspitiIstiDan
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST,listbox,1352728833

[CLS:CDlgIspitiIstiDan]
Type=0
HeaderFile=DlgIspitiIstiDan.h
ImplementationFile=DlgIspitiIstiDan.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgIspitiIstiDan

[DLG:IDD_PREGLED_SA_ZELJAMA]
Type=1
Class=CDlgPregledZelja
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GRID,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_CHECK_DANI,button,1342242819
Control6=IDC_CHECK_DATUMI,button,1342242819

[CLS:CDlgPregledZelja]
Type=0
HeaderFile=DlgPregledZelja.h
ImplementationFile=DlgPregledZelja.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgPregledZelja

[DLG:IDD_PREGLED_PO_SMJEROVIMA]
Type=1
Class=CPregledSmjeroviGodinaDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control4=IDC_ODABIR_SMJERA,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GODINA1,button,1342242816
Control7=IDC_GODINA2,button,1342242816
Control8=IDC_GODINA3,button,1342242816
Control9=IDC_GODINA4,button,1342242816
Control10=IDC_GODINA5,button,1342242816
Control11=IDC_PROMJENI_SMJER,button,1342242816

[CLS:CPregledSmjeroviGodinaDlg]
Type=0
HeaderFile=PregledSmjeroviGodinaDlg.h
ImplementationFile=PregledSmjeroviGodinaDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_GODINA1
VirtualFilter=dWC

[DLG:IDD_PREGLED_SMJER_GOD_VIZ]
Type=1
Class=CDlgPregledSmjerGodinaVizualno
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ODABIR_SMJERA,combobox,1344339971
Control4=IDC_STATIC,static,1342308352
Control5=IDC_GODINA1,button,1342242816
Control6=IDC_GODINA2,button,1342242816
Control7=IDC_GODINA3,button,1342242816
Control8=IDC_GODINA4,button,1342242816
Control9=IDC_GODINA5,button,1342242816
Control10=IDC_PROMJENI_SMJER,button,1342242816
Control11=IDC_STATIC,static,1342177286
Control12=IDC_STATIC,button,1342177287
Control13=IDC_CHECK_JESIZV,button,1342373891
Control14=IDC_CHECK_ZIM,button,1342373891
Control15=IDC_CHECK_PROLJ,button,1342373891
Control16=IDC_CHECK_LJET,button,1342373891
Control17=IDC_CHECK_JES,button,1342373891

[CLS:CDlgPregledSmjerGodinaVizualno]
Type=0
HeaderFile=DlgPregledSmjerGodinaVizualno.h
ImplementationFile=DlgPregledSmjerGodinaVizualno.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgPregledSmjerGodinaVizualno
VirtualFilter=dWC

