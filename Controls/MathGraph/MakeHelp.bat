@echo off
REM -- First, make map file from resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by MATHGRAPH.HPJ. > "hlp\MathGraph.hm"
echo. >>hlp\MathGraph.hm
echo // Commands (ID_* and IDM_*) >> "hlp\MathGraph.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >> "hlp\MathGraph.hm"
echo. >> "hlp\MathGraph.hm"
echo // Prompts (IDP_*) >> "hlp\MathGraph.hm"
makehm IDP_,HIDP_,0x30000 resource.h >> "hlp\MathGraph.hm"
echo. >> "hlp\MathGraph.hm"
echo // Resources (IDR_*) >> "hlp\MathGraph.hm"
makehm IDR_,HIDR_,0x20000 resource.h >> "hlp\MathGraph.hm"
echo. >> "hlp\MathGraph.hm"
echo // Dialogs (IDD_*) >> "hlp\MathGraph.hm"
makehm IDD_,HIDD_,0x20000 resource.h >> "hlp\MathGraph.hm"
echo. >> "hlp\MathGraph.hm"
echo // Frame Controls (IDW_*) >> "hlp\MathGraph.hm"
makehm IDW_,HIDW_,0x50000 resource.h >> "hlp\MathGraph.hm"
REM -- Make help for Project MATHGRAPH
start /wait hcw /C /E /M "MathGraph.hpj"
echo.
