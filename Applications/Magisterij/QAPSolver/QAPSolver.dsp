# Microsoft Developer Studio Project File - Name="QAPSolver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=QAPSolver - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QAPSolver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QAPSolver.mak" CFG="QAPSolver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QAPSolver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "QAPSolver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/QAPSolver", YJAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QAPSolver - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FAs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41a /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 QAPLibrary.lib Win32Serialize.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "QAPSolver - Win32 Debug"

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
# ADD LINK32 QAPLibraryDbg.lib Win32SerializeDbg.lib /nologo /subsystem:windows /pdb:none /debug /machine:I386

!ENDIF 

# Begin Target

# Name "QAPSolver - Win32 Release"
# Name "QAPSolver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlgDepQualityOfSolution.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGeneric.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelectGraphNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetProblemInstances.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTestChart.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTimeToReachSol.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewBestSolution.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewGraphResults.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewResults.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\QAPCompareDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\QAPCompareView.cpp
# End Source File
# Begin Source File

SOURCE=.\QAPSolver.cpp
# End Source File
# Begin Source File

SOURCE=.\QAPSolver.rc
# End Source File
# Begin Source File

SOURCE=.\QAPSolverDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\QAPSolverView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlgDepQualityOfSolution.h
# End Source File
# Begin Source File

SOURCE=.\DlgGeneric.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptimizationGenetic.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptimizationGRASP.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptimizationLocal.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptimizationSimAnnealing.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptimizationTabuSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelectGraphNumber.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetProblemInstances.h
# End Source File
# Begin Source File

SOURCE=.\DlgTestChart.h
# End Source File
# Begin Source File

SOURCE=.\DlgTimeToReachSol.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewBestSolution.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewData.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewGraphResults.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewResults.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\QAPCompareDoc.h
# End Source File
# Begin Source File

SOURCE=.\QAPCompareView.h
# End Source File
# Begin Source File

SOURCE=.\QAPSolver.h
# End Source File
# Begin Source File

SOURCE=.\QAPSolverDoc.h
# End Source File
# Begin Source File

SOURCE=.\QAPSolverView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\qap_comp.ico
# End Source File
# Begin Source File

SOURCE=.\res\QAPSolver.ico
# End Source File
# Begin Source File

SOURCE=.\res\QAPSolver.rc2
# End Source File
# Begin Source File

SOURCE=.\res\QAPSolverDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Control files - headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\commondialog.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\graph.h
# End Source File
# Begin Source File

SOURCE=.\mschart.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\prikazrasporedaispita.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor.h
# End Source File
# Begin Source File

SOURCE=.\simplegraph.h
# End Source File
# Begin Source File

SOURCE=.\vcaxis.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisgrid.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisscale.h
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle.h
# End Source File
# Begin Source File

SOURCE=.\vcbackdrop.h
# End Source File
# Begin Source File

SOURCE=.\vcbrush.h
# End Source File
# Begin Source File

SOURCE=.\vccategoryscale.h
# End Source File
# Begin Source File

SOURCE=.\vccolor.h
# End Source File
# Begin Source File

SOURCE=.\vccoor.h
# End Source File
# Begin Source File

SOURCE=.\vcdatagrid.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapoint.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapointlabel.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapoints.h
# End Source File
# Begin Source File

SOURCE=.\vcfill.h
# End Source File
# Begin Source File

SOURCE=.\vcfont.h
# End Source File
# Begin Source File

SOURCE=.\vcfootnote.h
# End Source File
# Begin Source File

SOURCE=.\vcframe.h
# End Source File
# Begin Source File

SOURCE=.\vcintersection.h
# End Source File
# Begin Source File

SOURCE=.\vclabel.h
# End Source File
# Begin Source File

SOURCE=.\vclabels.h
# End Source File
# Begin Source File

SOURCE=.\vclcoor.h
# End Source File
# Begin Source File

SOURCE=.\vclegend.h
# End Source File
# Begin Source File

SOURCE=.\vclight.h
# End Source File
# Begin Source File

SOURCE=.\vclightsource.h
# End Source File
# Begin Source File

SOURCE=.\vclightsources.h
# End Source File
# Begin Source File

SOURCE=.\vclocation.h
# End Source File
# Begin Source File

SOURCE=.\vcmarker.h
# End Source File
# Begin Source File

SOURCE=.\vcpen.h
# End Source File
# Begin Source File

SOURCE=.\vcplot.h
# End Source File
# Begin Source File

SOURCE=.\vcplotbase.h
# End Source File
# Begin Source File

SOURCE=.\vcrect.h
# End Source File
# Begin Source File

SOURCE=.\vcseries.h
# End Source File
# Begin Source File

SOURCE=.\vcseriescollection.h
# End Source File
# Begin Source File

SOURCE=.\vcseriesmarker.h
# End Source File
# Begin Source File

SOURCE=.\vcseriesposition.h
# End Source File
# Begin Source File

SOURCE=.\vcshadow.h
# End Source File
# Begin Source File

SOURCE=.\vcstatline.h
# End Source File
# Begin Source File

SOURCE=.\vctextlayout.h
# End Source File
# Begin Source File

SOURCE=.\vctick.h
# End Source File
# Begin Source File

SOURCE=.\vctitle.h
# End Source File
# Begin Source File

SOURCE=.\vcvaluescale.h
# End Source File
# Begin Source File

SOURCE=.\vcview3d.h
# End Source File
# Begin Source File

SOURCE=.\vcwall.h
# End Source File
# Begin Source File

SOURCE=.\vcweighting.h
# End Source File
# End Group
# Begin Group "Controls files - cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\commondialog.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\graph.cpp
# End Source File
# Begin Source File

SOURCE=.\mschart.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\prikazrasporedaispita.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\simplegraph.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxis.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxisgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxisscale.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle.cpp
# End Source File
# Begin Source File

SOURCE=.\vcbackdrop.cpp
# End Source File
# Begin Source File

SOURCE=.\vcbrush.cpp
# End Source File
# Begin Source File

SOURCE=.\vccategoryscale.cpp
# End Source File
# Begin Source File

SOURCE=.\vccolor.cpp
# End Source File
# Begin Source File

SOURCE=.\vccoor.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatagrid.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapoint.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapointlabel.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapoints.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfill.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfont.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfootnote.cpp
# End Source File
# Begin Source File

SOURCE=.\vcframe.cpp
# End Source File
# Begin Source File

SOURCE=.\vcintersection.cpp
# End Source File
# Begin Source File

SOURCE=.\vclabel.cpp
# End Source File
# Begin Source File

SOURCE=.\vclabels.cpp
# End Source File
# Begin Source File

SOURCE=.\vclcoor.cpp
# End Source File
# Begin Source File

SOURCE=.\vclegend.cpp
# End Source File
# Begin Source File

SOURCE=.\vclight.cpp
# End Source File
# Begin Source File

SOURCE=.\vclightsource.cpp
# End Source File
# Begin Source File

SOURCE=.\vclightsources.cpp
# End Source File
# Begin Source File

SOURCE=.\vclocation.cpp
# End Source File
# Begin Source File

SOURCE=.\vcmarker.cpp
# End Source File
# Begin Source File

SOURCE=.\vcpen.cpp
# End Source File
# Begin Source File

SOURCE=.\vcplot.cpp
# End Source File
# Begin Source File

SOURCE=.\vcplotbase.cpp
# End Source File
# Begin Source File

SOURCE=.\vcrect.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseries.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriescollection.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriesmarker.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriesposition.cpp
# End Source File
# Begin Source File

SOURCE=.\vcshadow.cpp
# End Source File
# Begin Source File

SOURCE=.\vcstatline.cpp
# End Source File
# Begin Source File

SOURCE=.\vctextlayout.cpp
# End Source File
# Begin Source File

SOURCE=.\vctick.cpp
# End Source File
# Begin Source File

SOURCE=.\vctitle.cpp
# End Source File
# Begin Source File

SOURCE=.\vcvaluescale.cpp
# End Source File
# Begin Source File

SOURCE=.\vcview3d.cpp
# End Source File
# Begin Source File

SOURCE=.\vcwall.cpp
# End Source File
# Begin Source File

SOURCE=.\vcweighting.cpp
# End Source File
# End Group
# Begin Group "Extra headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE="..\..\..\..\..\LIBRARY\C++\Include\Optimization\Base.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Library\C++\Include\Mathlib\Matrix.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\LIBRARY\C++\Include\Optimization\Optimization.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\LIBRARY\C++\Include\Optimization\OptimizationResult.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\LIBRARY\C++\Include\Optimization\OptRefresh.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\LIBRARY\C++\Include\QAP\QAP.H"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\LIBRARY\C++\Include\QAP\QAPTabuSearch.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Library\C++\Include\QAP\Win32Serialize.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section QAPSolver : {E9E07511-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeries
# 	2:10:HeaderFile:vcseries.h
# 	2:8:ImplFile:vcseries.cpp
# End Section
# Section QAPSolver : {E9E0751D-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcIntersection
# 	2:10:HeaderFile:vcintersection.h
# 	2:8:ImplFile:vcintersection.cpp
# End Section
# Section QAPSolver : {E9E074D5-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTextLayout
# 	2:10:HeaderFile:vctextlayout.h
# 	2:8:ImplFile:vctextlayout.cpp
# End Section
# Section QAPSolver : {E9E074E0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFrame
# 	2:10:HeaderFile:vcframe.h
# 	2:8:ImplFile:vcframe.cpp
# End Section
# Section QAPSolver : {E9E074EC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSource
# 	2:10:HeaderFile:vclightsource.h
# 	2:8:ImplFile:vclightsource.cpp
# End Section
# Section QAPSolver : {E9E074FC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWall
# 	2:10:HeaderFile:vcwall.h
# 	2:8:ImplFile:vcwall.cpp
# End Section
# Section QAPSolver : {E9E07521-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisScale
# 	2:10:HeaderFile:vcaxisscale.h
# 	2:8:ImplFile:vcaxisscale.cpp
# End Section
# Section QAPSolver : {E9E074DC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcShadow
# 	2:10:HeaderFile:vcshadow.h
# 	2:8:ImplFile:vcshadow.cpp
# End Section
# Section QAPSolver : {E9E074F0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLight
# 	2:10:HeaderFile:vclight.h
# 	2:8:ImplFile:vclight.cpp
# End Section
# Section QAPSolver : {E9E07515-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisTitle
# 	2:10:HeaderFile:vcaxistitle.h
# 	2:8:ImplFile:vcaxistitle.cpp
# End Section
# Section QAPSolver : {E9E07525-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxis
# 	2:10:HeaderFile:vcaxis.h
# 	2:8:ImplFile:vcaxis.cpp
# End Section
# Section QAPSolver : {E9E074C9-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCoor
# 	2:10:HeaderFile:vccoor.h
# 	2:8:ImplFile:vccoor.cpp
# End Section
# Section QAPSolver : {E9E0750C-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPointLabel
# 	2:10:HeaderFile:vcdatapointlabel.h
# 	2:8:ImplFile:vcdatapointlabel.cpp
# End Section
# Section QAPSolver : {E9E074CB-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLCoor
# 	2:10:HeaderFile:vclcoor.h
# 	2:8:ImplFile:vclcoor.cpp
# End Section
# Section QAPSolver : {E9E074F4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlotBase
# 	2:10:HeaderFile:vcplotbase.h
# 	2:8:ImplFile:vcplotbase.cpp
# End Section
# Section QAPSolver : {E9E074E4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTitle
# 	2:10:HeaderFile:vctitle.h
# 	2:8:ImplFile:vctitle.cpp
# End Section
# Section QAPSolver : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
# Section QAPSolver : {E9E07504-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesMarker
# 	2:10:HeaderFile:vcseriesmarker.h
# 	2:8:ImplFile:vcseriesmarker.cpp
# End Section
# Section QAPSolver : {E9E074D8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFont
# 	2:10:HeaderFile:vcfont.h
# 	2:8:ImplFile:vcfont.cpp
# End Section
# Section QAPSolver : {106D39E6-C7AF-11D1-AFFE-0000C03E618C}
# 	2:5:Class:CGraph1
# 	2:10:HeaderFile:graph1.h
# 	2:8:ImplFile:graph1.cpp
# End Section
# Section QAPSolver : {E9E074D3-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcMarker
# 	2:10:HeaderFile:vcmarker.h
# 	2:8:ImplFile:vcmarker.cpp
# End Section
# Section QAPSolver : {E9E0751B-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisGrid
# 	2:10:HeaderFile:vcaxisgrid.h
# 	2:8:ImplFile:vcaxisgrid.cpp
# End Section
# Section QAPSolver : {E9E074E8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLegend
# 	2:10:HeaderFile:vclegend.h
# 	2:8:ImplFile:vclegend.cpp
# End Section
# Section QAPSolver : {E9E074CF-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcColor
# 	2:10:HeaderFile:vccolor.h
# 	2:8:ImplFile:vccolor.cpp
# End Section
# Section QAPSolver : {E9E074FA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWeighting
# 	2:10:HeaderFile:vcweighting.h
# 	2:8:ImplFile:vcweighting.cpp
# End Section
# Section QAPSolver : {E9E074EA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataGrid
# 	2:10:HeaderFile:vcdatagrid.h
# 	2:8:ImplFile:vcdatagrid.cpp
# End Section
# Section QAPSolver : {E9E074DA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBrush
# 	2:10:HeaderFile:vcbrush.h
# 	2:8:ImplFile:vcbrush.cpp
# End Section
# Section QAPSolver : {083039C2-13F4-11D1-8B7E-0000F8754DA1}
# 	2:5:Class:CCommonDialog1
# 	2:10:HeaderFile:commondialog.h
# 	2:8:ImplFile:commondialog.cpp
# End Section
# Section QAPSolver : {1030F5CF-FA20-413B-824F-C0D89D37272D}
# 	2:5:Class:CPrikazRasporedaIspita
# 	2:10:HeaderFile:prikazrasporedaispita.h
# 	2:8:ImplFile:prikazrasporedaispita.cpp
# End Section
# Section QAPSolver : {3A2B370C-BA0A-11D1-B137-0000F8753F5D}
# 	2:21:DefaultSinkHeaderFile:mschart.h
# 	2:16:DefaultSinkClass:CMSChart
# End Section
# Section QAPSolver : {E9E07508-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabel
# 	2:10:HeaderFile:vclabel.h
# 	2:8:ImplFile:vclabel.cpp
# End Section
# Section QAPSolver : {FA54AEE2-B3C1-4897-AFDA-19D2FDED9B03}
# 	2:21:DefaultSinkHeaderFile:simplegraph.h
# 	2:16:DefaultSinkClass:CSimpleGraph
# End Section
# Section QAPSolver : {E9E07523-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcValueScale
# 	2:10:HeaderFile:vcvaluescale.h
# 	2:8:ImplFile:vcvaluescale.cpp
# End Section
# Section QAPSolver : {E9E07513-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesCollection
# 	2:10:HeaderFile:vcseriescollection.h
# 	2:8:ImplFile:vcseriescollection.cpp
# End Section
# Section QAPSolver : {E9E0751F-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTick
# 	2:10:HeaderFile:vctick.h
# 	2:8:ImplFile:vctick.cpp
# End Section
# Section QAPSolver : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section QAPSolver : {E9E074F2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcView3d
# 	2:10:HeaderFile:vcview3d.h
# 	2:8:ImplFile:vcview3d.cpp
# End Section
# Section QAPSolver : {E9E0752A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoints
# 	2:10:HeaderFile:vcdatapoints.h
# 	2:8:ImplFile:vcdatapoints.cpp
# End Section
# Section QAPSolver : {E9E074E2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBackdrop
# 	2:10:HeaderFile:vcbackdrop.h
# 	2:8:ImplFile:vcbackdrop.cpp
# End Section
# Section QAPSolver : {E9E0750A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabels
# 	2:10:HeaderFile:vclabels.h
# 	2:8:ImplFile:vclabels.cpp
# End Section
# Section QAPSolver : {E9E074DE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFill
# 	2:10:HeaderFile:vcfill.h
# 	2:8:ImplFile:vcfill.cpp
# End Section
# Section QAPSolver : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section QAPSolver : {E9E074EE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSources
# 	2:10:HeaderFile:vclightsources.h
# 	2:8:ImplFile:vclightsources.cpp
# End Section
# Section QAPSolver : {CF614461-608B-40F3-A462-CF4094530FE2}
# 	2:5:Class:CSimpleGraph
# 	2:10:HeaderFile:simplegraph.h
# 	2:8:ImplFile:simplegraph.cpp
# End Section
# Section QAPSolver : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section QAPSolver : {E9E0750E-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoint
# 	2:10:HeaderFile:vcdatapoint.h
# 	2:8:ImplFile:vcdatapoint.cpp
# End Section
# Section QAPSolver : {E9E07527-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlot
# 	2:10:HeaderFile:vcplot.h
# 	2:8:ImplFile:vcplot.cpp
# End Section
# Section QAPSolver : {F9043C85-F6F2-101A-A3C9-08002B2F49FB}
# 	2:21:DefaultSinkHeaderFile:commondialog.h
# 	2:16:DefaultSinkClass:CCommonDialog1
# End Section
# Section QAPSolver : {58E19248-A94F-4762-B543-0F1CD6C3B71D}
# 	2:21:DefaultSinkHeaderFile:prikazrasporedaispita.h
# 	2:16:DefaultSinkClass:CPrikazRasporedaIspita
# End Section
# Section QAPSolver : {E9E07517-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCategoryScale
# 	2:10:HeaderFile:vccategoryscale.h
# 	2:8:ImplFile:vccategoryscale.cpp
# End Section
# Section QAPSolver : {E9E074CD-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcRect
# 	2:10:HeaderFile:vcrect.h
# 	2:8:ImplFile:vcrect.cpp
# End Section
# Section QAPSolver : {E9E07502-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesPosition
# 	2:10:HeaderFile:vcseriesposition.h
# 	2:8:ImplFile:vcseriesposition.cpp
# End Section
# Section QAPSolver : {E9E074D6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLocation
# 	2:10:HeaderFile:vclocation.h
# 	2:8:ImplFile:vclocation.cpp
# End Section
# Section QAPSolver : {E9E074E6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFootnote
# 	2:10:HeaderFile:vcfootnote.h
# 	2:8:ImplFile:vcfootnote.cpp
# End Section
# Section QAPSolver : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section QAPSolver : {3A2B370A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CMSChart
# 	2:10:HeaderFile:mschart.h
# 	2:8:ImplFile:mschart.cpp
# End Section
# Section QAPSolver : {E9E074D1-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPen
# 	2:10:HeaderFile:vcpen.h
# 	2:8:ImplFile:vcpen.cpp
# End Section
# Section QAPSolver : {E9E07506-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcStatLine
# 	2:10:HeaderFile:vcstatline.h
# 	2:8:ImplFile:vcstatline.cpp
# End Section
# Section QAPSolver : {106D39E8-C7AF-11D1-AFFE-0000C03E618C}
# 	2:21:DefaultSinkHeaderFile:graph.h
# 	2:16:DefaultSinkClass:CGraph
# End Section
