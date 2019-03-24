

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Feb 16 14:34:49 2017
 */
/* Compiler settings for MathGraph.odl:
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


#ifndef __MathGraph_h_h__
#define __MathGraph_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DMathGraph_FWD_DEFINED__
#define ___DMathGraph_FWD_DEFINED__
typedef interface _DMathGraph _DMathGraph;
#endif 	/* ___DMathGraph_FWD_DEFINED__ */


#ifndef ___DMathGraphEvents_FWD_DEFINED__
#define ___DMathGraphEvents_FWD_DEFINED__
typedef interface _DMathGraphEvents _DMathGraphEvents;
#endif 	/* ___DMathGraphEvents_FWD_DEFINED__ */


#ifndef __MathGraph_FWD_DEFINED__
#define __MathGraph_FWD_DEFINED__

#ifdef __cplusplus
typedef class MathGraph MathGraph;
#else
typedef struct MathGraph MathGraph;
#endif /* __cplusplus */

#endif 	/* __MathGraph_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MATHGRAPHLib_LIBRARY_DEFINED__
#define __MATHGRAPHLib_LIBRARY_DEFINED__

/* library MATHGRAPHLib */
/* [control][helpstring][helpfile][version][uuid] */ 


DEFINE_GUID(LIBID_MATHGRAPHLib,0x81936D26,0xBE53,0x11D1,0xAF,0xF7,0x00,0x00,0xC0,0x3E,0x61,0x8C);

#ifndef ___DMathGraph_DISPINTERFACE_DEFINED__
#define ___DMathGraph_DISPINTERFACE_DEFINED__

/* dispinterface _DMathGraph */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMathGraph,0x81936D27,0xBE53,0x11D1,0xAF,0xF7,0x00,0x00,0xC0,0x3E,0x61,0x8C);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("81936D27-BE53-11D1-AFF7-0000C03E618C")
    _DMathGraph : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMathGraphVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMathGraph * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMathGraph * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMathGraph * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMathGraph * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMathGraph * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMathGraph * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMathGraph * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DMathGraphVtbl;

    interface _DMathGraph
    {
        CONST_VTBL struct _DMathGraphVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMathGraph_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMathGraph_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMathGraph_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMathGraph_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMathGraph_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMathGraph_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMathGraph_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMathGraph_DISPINTERFACE_DEFINED__ */


#ifndef ___DMathGraphEvents_DISPINTERFACE_DEFINED__
#define ___DMathGraphEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMathGraphEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMathGraphEvents,0x81936D28,0xBE53,0x11D1,0xAF,0xF7,0x00,0x00,0xC0,0x3E,0x61,0x8C);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("81936D28-BE53-11D1-AFF7-0000C03E618C")
    _DMathGraphEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMathGraphEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMathGraphEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMathGraphEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMathGraphEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMathGraphEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMathGraphEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMathGraphEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMathGraphEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DMathGraphEventsVtbl;

    interface _DMathGraphEvents
    {
        CONST_VTBL struct _DMathGraphEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMathGraphEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMathGraphEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMathGraphEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMathGraphEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMathGraphEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMathGraphEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMathGraphEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMathGraphEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MathGraph,0x81936D29,0xBE53,0x11D1,0xAF,0xF7,0x00,0x00,0xC0,0x3E,0x61,0x8C);

#ifdef __cplusplus

class DECLSPEC_UUID("81936D29-BE53-11D1-AFF7-0000C03E618C")
MathGraph;
#endif
#endif /* __MATHGRAPHLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


