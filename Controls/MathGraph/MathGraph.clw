; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMathGraphCtrl
LastTemplate=COlePropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mathgraph.h"
LastPage=0
CDK=Y

ClassCount=4
Class1=CMathGraphCtrl
Class2=CMathGraphPropPage

ResourceCount=4
Resource1=IDD_PROPPAGE_MATHGRAPH
Resource2=IDD_SEC_PROPPAGE_MATHGRAPH
Class3=CMathGraphSecPage
Resource3=IDD_STAT_PROPPAGE_MATHGRAPH
Class4=CMathGraphStatPage
Resource4=IDD_ABOUTBOX_MATHGRAPH

[CLS:CMathGraphCtrl]
Type=0
BaseClass=COleControl
HeaderFile=MathGraphCtl.h
ImplementationFile=MathGraphCtl.cpp
LastObject=CMathGraphCtrl
Filter=W
VirtualFilter=wWC

[CLS:CMathGraphPropPage]
Type=0
BaseClass=COlePropertyPage
HeaderFile=MathGraphPpg.h
ImplementationFile=MathGraphPpg.cpp
LastObject=IDC_CARTESIAN
Filter=D
VirtualFilter=idWC

[DLG:IDD_PROPPAGE_MATHGRAPH]
Type=1
Class=CMathGraphPropPage
ControlCount=21
Control1=IDC_COLORS,button,1342242819
Control2=IDC_DIFF_LINE_STYLES,button,1342242819
Control3=IDC_NORM_NORM,button,1342308361
Control4=IDC_NORM_LOG,button,1342308361
Control5=IDC_LOG_NORM,button,1342308361
Control6=IDC_LOG_LOG,button,1342308361
Control7=IDC_CARTESIAN,button,1342308361
Control8=IDC_SPHERICAL,button,1342308361
Control9=IDC_CYLINDRICAL,button,1342308361
Control10=IDC_TITLE,edit,1350631552
Control11=IDC_X_AXIS,edit,1350631552
Control12=IDC_Y_AXIS,edit,1350631552
Control13=IDC_Z_AXIS,edit,1350631552
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_SHOW_LEGEND,button,1342242819

[DLG:IDD_ABOUTBOX_MATHGRAPH]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SEC_PROPPAGE_MATHGRAPH]
Type=1
Class=CMathGraphSecPage
ControlCount=21
Control1=IDC_TYPE_GRAPH,static,1350637582
Control2=IDC_TYPE_PHASE,static,1484853262
Control3=IDC_TYPE_FITT_LINEAR,static,1350637582
Control4=IDC_TYPE_FITT_POLYNOM,static,1350637582
Control5=IDC_TYPE_SURFACE,static,1350637582
Control6=IDC_TYPE_PHASE3D,static,1350633486
Control7=IDC_SELECTED,combobox,1344339971
Control8=IDC_X_AXIS,edit,1350631552
Control9=IDC_Z_AXIS,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342177280
Control12=IDC_STATIC,static,1342177280
Control13=IDC_STATIC,static,1342177280
Control14=IDC_STATIC,static,1342177280
Control15=IDC_STATIC,static,1342177280
Control16=IDC_STATIC,static,1342177280
Control17=IDC_STATIC,static,1342177280
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_Y_AXIS,edit,1350631552

[CLS:CMathGraphSecPage]
Type=0
HeaderFile=MathGraphSecPage.h
ImplementationFile=MathGraphSecPage.cpp
BaseClass=COlePropertyPage
Filter=D
LastObject=CMathGraphSecPage
VirtualFilter=idWC

[DLG:IDD_STAT_PROPPAGE_MATHGRAPH]
Type=1
Class=CMathGraphStatPage
ControlCount=32
Control1=IDC_STATIC,static,1342308352
Control2=IDC_SELECT_GRAPH,combobox,1344340226
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_LIN_REG_A,edit,1484849280
Control16=IDC_LINE_REG_DA,edit,1484849280
Control17=IDC_LIN_REG_B,edit,1484849280
Control18=IDC_LIN_REG_DB,edit,1484849280
Control19=IDC_MEAN,edit,1484849280
Control20=IDC_VAR,edit,1484849280
Control21=IDC_STAND_DEV,edit,1484849280
Control22=IDC_AVERG_DEV,edit,1484849280
Control23=IDC_SKEW,edit,1484849280
Control24=IDC_KURTOSIS,edit,1484849280
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_X_NORM,button,1342308361
Control30=IDC_X_LOG,button,1342308361
Control31=IDC_Y_NORM,button,1342308361
Control32=IDC_Y_LOG,button,1342308361

[CLS:CMathGraphStatPage]
Type=0
HeaderFile=MathGraphStatPage.h
ImplementationFile=MathGraphStatPage.cpp
BaseClass=COlePropertyPage
Filter=D
LastObject=CMathGraphStatPage

