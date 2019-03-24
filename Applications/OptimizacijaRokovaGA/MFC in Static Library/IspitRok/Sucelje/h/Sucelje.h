#ifndef WS_VISCHILD
   #define WS_VISCHILD (WS_VISIBLE | WS_CHILD)
#endif

#include <afxwin.h>  
#include <afxext.h>  
#include <afxcmn.h>  
#include <afxres.h>  
#include <afxdlgs.h> 
#include <afxmt.h>
#include <math.h>
#include <time.h>
#include <fstream.h>

#include "..\..\Optim\h\struct.h"
#include "..\..\Optim\h\pomoc_klas.h"
#include "..\..\Optim\h\podat_klas.h"
#include "..\..\Optim\h\gen_klas.h"
#include "..\..\Optim\h\gen_alg.h"
#include "..\..\Optim\h\fiks_ispit_klas.h"
#include "..\..\Optim\h\opt_god_klas.h"
#include "OptimizacijaThread_klas.h"
#include "Prozor.h"
#include "..\..\Resource\resource.h"
#include "dlgfiks.h"
#include "dlgUcit.h"
#include "dlgParam.h"
#include "dlgPred.h"
#include "dlgUcitMasovni.h"
#include "dlgGreska.h"
