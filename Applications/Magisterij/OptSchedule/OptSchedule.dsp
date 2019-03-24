# Microsoft Developer Studio Project File - Name="OptSchedule" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=OptSchedule - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OptSchedule.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OptSchedule.mak" CFG="OptSchedule - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OptSchedule - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OptSchedule - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/OptSchedule", QIAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OptSchedule - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41a /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 OptRokova.lib ScheduleFramework.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "OptSchedule - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41a /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41a /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 OptRokovaDbg.lib ScheduleFrameworkDbg.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "OptSchedule - Win32 Release"
# Name "OptSchedule - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetModelDescr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewData.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\OptSchedule.odl
# End Source File
# Begin Source File

SOURCE=.\OptSchedule.rc
# End Source File
# Begin Source File

SOURCE=.\OptScheduleDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\OptScheduleView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Win32Serialize.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetModelDescr.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewData.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OptSchedule.h
# End Source File
# Begin Source File

SOURCE=.\OptScheduleDoc.h
# End Source File
# Begin Source File

SOURCE=.\OptScheduleView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Win32Serialize.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\OptSchedule.ico
# End Source File
# Begin Source File

SOURCE=.\res\OptSchedule.rc2
# End Source File
# Begin Source File

SOURCE=.\res\OptScheduleDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Extra headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Calendar.h
# End Source File
# Begin Source File

SOURCE=.\CalendarData.h
# End Source File
# Begin Source File

SOURCE=.\GeneticAlgNew.h
# End Source File
# Begin Source File

SOURCE=.\Interval.h
# End Source File
# Begin Source File

SOURCE=.\IOptRok.h
# End Source File
# Begin Source File

SOURCE=.\IRokData.h
# End Source File
# Begin Source File

SOURCE=.\Matrix.h
# End Source File
# Begin Source File

SOURCE=.\Optimization.h
# End Source File
# Begin Source File

SOURCE=.\OptProblem.h
# End Source File
# Begin Source File

SOURCE=.\QAPNew.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\OptSchedule.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section OptSchedule : {C74190B6-8589-11D1-B16A-00C0F0283628}
# 	2:21:DefaultSinkHeaderFile:treeview.h
# 	2:16:DefaultSinkClass:CTreeView1
# End Section
# Section OptSchedule : {C74190B4-8589-11D1-B16A-00C0F0283628}
# 	2:5:Class:CTreeView1
# 	2:10:HeaderFile:treeview.h
# 	2:8:ImplFile:treeview.cpp
# End Section
# Section OptSchedule : {C74190B8-8589-11D1-B16A-00C0F0283628}
# 	2:5:Class:CNode
# 	2:10:HeaderFile:node.h
# 	2:8:ImplFile:node.cpp
# End Section
# Section OptSchedule : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section OptSchedule : {C74190B7-8589-11D1-B16A-00C0F0283628}
# 	2:5:Class:CNodes
# 	2:10:HeaderFile:nodes.h
# 	2:8:ImplFile:nodes.cpp
# End Section
# Section OptSchedule : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
