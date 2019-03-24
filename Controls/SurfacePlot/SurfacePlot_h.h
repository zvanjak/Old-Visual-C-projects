

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Feb 16 14:34:49 2017
 */
/* Compiler settings for SurfacePlot.odl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __SurfacePlot_h_h__
#define __SurfacePlot_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DSurfacePlot_FWD_DEFINED__
#define ___DSurfacePlot_FWD_DEFINED__
typedef interface _DSurfacePlot _DSurfacePlot;
#endif 	/* ___DSurfacePlot_FWD_DEFINED__ */


#ifndef ___DSurfacePlotEvents_FWD_DEFINED__
#define ___DSurfacePlotEvents_FWD_DEFINED__
typedef interface _DSurfacePlotEvents _DSurfacePlotEvents;
#endif 	/* ___DSurfacePlotEvents_FWD_DEFINED__ */


#ifndef __SurfacePlot_FWD_DEFINED__
#define __SurfacePlot_FWD_DEFINED__

#ifdef __cplusplus
typedef class SurfacePlot SurfacePlot;
#else
typedef struct SurfacePlot SurfacePlot;
#endif /* __cplusplus */

#endif 	/* __SurfacePlot_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __SURFACEPLOTLib_LIBRARY_DEFINED__
#define __SURFACEPLOTLib_LIBRARY_DEFINED__

/* library SURFACEPLOTLib */
/* [control][helpstring][helpfile][version][uuid] */ 


DEFINE_GUID(LIBID_SURFACEPLOTLib,0x7E0D9ED9,0x075A,0x11D2,0x91,0x4A,0x00,0xC0,0xDF,0xE5,0x28,0x74);

#ifndef ___DSurfacePlot_DISPINTERFACE_DEFINED__
#define ___DSurfacePlot_DISPINTERFACE_DEFINED__

/* dispinterface _DSurfacePlot */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DSurfacePlot,0x7E0D9EDA,0x075A,0x11D2,0x91,0x4A,0x00,0xC0,0xDF,0xE5,0x28,0x74);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7E0D9EDA-075A-11D2-914A-00C0DFE52874")
    _DSurfacePlot : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSurfacePlotVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSurfacePlot * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSurfacePlot * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSurfacePlot * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSurfacePlot * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSurfacePlot * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSurfacePlot * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSurfacePlot * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSurfacePlotVtbl;

    interface _DSurfacePlot
    {
        CONST_VTBL struct _DSurfacePlotVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSurfacePlot_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSurfacePlot_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSurfacePlot_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSurfacePlot_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSurfacePlot_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSurfacePlot_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSurfacePlot_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSurfacePlot_DISPINTERFACE_DEFINED__ */


#ifndef ___DSurfacePlotEvents_DISPINTERFACE_DEFINED__
#define ___DSurfacePlotEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DSurfacePlotEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DSurfacePlotEvents,0x7E0D9EDB,0x075A,0x11D2,0x91,0x4A,0x00,0xC0,0xDF,0xE5,0x28,0x74);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7E0D9EDB-075A-11D2-914A-00C0DFE52874")
    _DSurfacePlotEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSurfacePlotEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSurfacePlotEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSurfacePlotEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSurfacePlotEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSurfacePlotEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSurfacePlotEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSurfacePlotEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSurfacePlotEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSurfacePlotEventsVtbl;

    interface _DSurfacePlotEvents
    {
        CONST_VTBL struct _DSurfacePlotEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSurfacePlotEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSurfacePlotEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSurfacePlotEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSurfacePlotEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSurfacePlotEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSurfacePlotEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSurfacePlotEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSurfacePlotEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_SurfacePlot,0x7E0D9EDC,0x075A,0x11D2,0x91,0x4A,0x00,0xC0,0xDF,0xE5,0x28,0x74);

#ifdef __cplusplus

class DECLSPEC_UUID("7E0D9EDC-075A-11D2-914A-00C0DFE52874")
SurfacePlot;
#endif
#endif /* __SURFACEPLOTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


