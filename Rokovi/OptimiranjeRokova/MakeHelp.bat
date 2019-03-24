@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by OPTIMIRANJEROKOVA.HPJ. >"hlp\OptimiranjeRokova.hm"
echo. >>"hlp\OptimiranjeRokova.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\OptimiranjeRokova.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\OptimiranjeRokova.hm"
echo. >>"hlp\OptimiranjeRokova.hm"
echo // Prompts (IDP_*) >>"hlp\OptimiranjeRokova.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\OptimiranjeRokova.hm"
echo. >>"hlp\OptimiranjeRokova.hm"
echo // Resources (IDR_*) >>"hlp\OptimiranjeRokova.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\OptimiranjeRokova.hm"
echo. >>"hlp\OptimiranjeRokova.hm"
echo // Dialogs (IDD_*) >>"hlp\OptimiranjeRokova.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\OptimiranjeRokova.hm"
echo. >>"hlp\OptimiranjeRokova.hm"
echo // Frame Controls (IDW_*) >>"hlp\OptimiranjeRokova.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\OptimiranjeRokova.hm"
REM -- Make help for Project OPTIMIRANJEROKOVA


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\OptimiranjeRokova.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\OptimiranjeRokova.hlp" goto :Error
if not exist "hlp\OptimiranjeRokova.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\OptimiranjeRokova.hlp" Debug
if exist Debug\nul copy "hlp\OptimiranjeRokova.cnt" Debug
if exist Release\nul copy "hlp\OptimiranjeRokova.hlp" Release
if exist Release\nul copy "hlp\OptimiranjeRokova.cnt" Release
echo.
goto :done

:Error
echo hlp\OptimiranjeRokova.hpj(1) : error: Problem encountered creating help file

:done
echo.
