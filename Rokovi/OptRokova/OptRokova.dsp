# Microsoft Developer Studio Project File - Name="OptRokova" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=OptRokova - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OptRokova.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OptRokova.mak" CFG="OptRokova - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OptRokova - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OptRokova - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "OptRokova - Win32 Release2" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OptRokova - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_DIST" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41a /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /profile /machine:I386

!ELSEIF  "$(CFG)" == "OptRokova - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41a /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41a /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /profile /debug /machine:I386

!ELSEIF  "$(CFG)" == "OptRokova - Win32 Release2"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "OptRokova___Win32_Release2"
# PROP BASE Intermediate_Dir "OptRokova___Win32_Release2"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "OptRokova___Win32_Release2"
# PROP Intermediate_Dir "OptRokova___Win32_Release2"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /profile /machine:I386
# ADD LINK32 /nologo /subsystem:windows /profile /machine:I386 /out:"C:\Rokovi\OptRokova.exe"

!ENDIF 

# Begin Target

# Name "OptRokova - Win32 Release"
# Name "OptRokova - Win32 Debug"
# Name "OptRokova - Win32 Release2"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\OptFunc\Data.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIspitiIstiDan.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptim.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgParametriRoka.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgParamOptimizacije.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPopisIspita.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPregledSmjerGodinaVizualno.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPregledZelja.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVizualniPrikaz.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\OptFunc\ModelPar.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=..\OptFunc\Optimization.cpp
# End Source File
# Begin Source File

SOURCE=.\OptRokDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\OptRokova.cpp
# End Source File
# Begin Source File

SOURCE=.\OptRokova.rc
# End Source File
# Begin Source File

SOURCE=.\OptRokView.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PregledSmjeroviGodinaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\scrollbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\testcontrolempty.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgOptim.h
# End Source File
# Begin Source File

SOURCE=.\DlgParametriRoka.h
# End Source File
# Begin Source File

SOURCE=.\DlgParamOptimizacije.h
# End Source File
# Begin Source File

SOURCE=.\DlgPopisIspita.h
# End Source File
# Begin Source File

SOURCE=.\DlgPregledSmjerGodinaVizualno.h
# End Source File
# Begin Source File

SOURCE=.\DlgPregledZelja.h
# End Source File
# Begin Source File

SOURCE=.\DlgVizualniPrikaz.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\OptRokDoc.h
# End Source File
# Begin Source File

SOURCE=.\OptRokova.h
# End Source File
# Begin Source File

SOURCE=.\OptRokView.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\PregledSmjeroviGodinaDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor.h
# End Source File
# Begin Source File

SOURCE=.\scrollbar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\testcontrolempty.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\OptRokDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\OptRokova.ico
# End Source File
# Begin Source File

SOURCE=.\res\OptRokova.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\IspitiIstiDan.txt
# End Source File
# Begin Source File

SOURCE=.\nasprog1.txt
# End Source File
# Begin Source File

SOURCE=.\nasprogram.txt
# End Source File
# Begin Source File

SOURCE=.\predmet.txt
# End Source File
# Begin Source File

SOURCE=.\presjek.txt
# End Source File
# Begin Source File

SOURCE=.\presjek1.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section OptRokova : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
# Section OptRokova : {083039C2-13F4-11D1-8B7E-0000F8754DA1}
# 	2:5:Class:CCommonDialog1
# 	2:10:HeaderFile:commondialog.h
# 	2:8:ImplFile:commondialog.cpp
# End Section
# Section OptRokova : {603C7E7E-87C2-11D1-8BE3-0000F8754DA1}
# 	2:5:Class:CUpDown
# 	2:10:HeaderFile:updown.h
# 	2:8:ImplFile:updown.cpp
# End Section
# Section OptRokova : {AC61CBDE-4407-4F59-8B17-09FD23DB1DBC}
# 	2:21:DefaultSinkHeaderFile:testcontrolempty.h
# 	2:16:DefaultSinkClass:CTestControlEmpty
# End Section
# Section OptRokova : {04598FC3-866C-11CF-AB7C-00AA00C08FCF}
# 	2:5:Class:CScrollbar
# 	2:10:HeaderFile:scrollbar.h
# 	2:8:ImplFile:scrollbar.cpp
# End Section
# Section OptRokova : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section OptRokova : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section OptRokova : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section OptRokova : {F9043C85-F6F2-101A-A3C9-08002B2F49FB}
# 	2:21:DefaultSinkHeaderFile:commondialog.h
# 	2:16:DefaultSinkClass:CCommonDialog1
# End Section
# Section OptRokova : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section OptRokova : {603C7E80-87C2-11D1-8BE3-0000F8754DA1}
# 	2:21:DefaultSinkHeaderFile:updown.h
# 	2:16:DefaultSinkClass:CUpDown
# End Section
# Section OptRokova : {DFD181E0-5E2F-11CE-A449-00AA004A803D}
# 	2:21:DefaultSinkHeaderFile:scrollbar.h
# 	2:16:DefaultSinkClass:CScrollbar
# End Section
# Section OptRokova : {4476A6C8-6595-4547-9574-1659F520BAAE}
# 	2:5:Class:CTestControlEmpty
# 	2:10:HeaderFile:testcontrolempty.h
# 	2:8:ImplFile:testcontrolempty.cpp
# End Section
