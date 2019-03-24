

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Feb 16 14:34:49 2017
 */
/* Compiler settings for GraphControl.odl:
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


#ifndef __GraphControl_h_h__
#define __GraphControl_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DGraph_FWD_DEFINED__
#define ___DGraph_FWD_DEFINED__
typedef interface _DGraph _DGraph;
#endif 	/* ___DGraph_FWD_DEFINED__ */


#ifndef ___DGraphEvents_FWD_DEFINED__
#define ___DGraphEvents_FWD_DEFINED__
typedef interface _DGraphEvents _DGraphEvents;
#endif 	/* ___DGraphEvents_FWD_DEFINED__ */


#ifndef __Graph_FWD_DEFINED__
#define __Graph_FWD_DEFINED__

#ifdef __cplusplus
typedef class Graph Graph;
#else
typedef struct Graph Graph;
#endif /* __cplusplus */

#endif 	/* __Graph_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __GRAPHCONTROLLib_LIBRARY_DEFINED__
#define __GRAPHCONTROLLib_LIBRARY_DEFINED__

/* library GRAPHCONTROLLib */
/* [control][helpstring][helpfile][version][uuid] */ 


DEFINE_GUID(LIBID_GRAPHCONTROLLib,0x106D39E5,0xC7AF,0x11D1,0xAF,0xFE,0x00,0x00,0xC0,0x3E,0x61,0x8C);

#ifndef ___DGraph_DISPINTERFACE_DEFINED__
#define ___DGraph_DISPINTERFACE_DEFINED__

/* dispinterface _DGraph */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DGraph,0x106D39E6,0xC7AF,0x11D1,0xAF,0xFE,0x00,0x00,0xC0,0x3E,0x61,0x8C);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("106D39E6-C7AF-11D1-AFFE-0000C03E618C")
    _DGraph : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGraphVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGraph * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGraph * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGraph * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGraph * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGraph * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGraph * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGraph * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DGraphVtbl;

    interface _DGraph
    {
        CONST_VTBL struct _DGraphVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGraph_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGraph_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGraph_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGraph_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGraph_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGraph_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGraph_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGraph_DISPINTERFACE_DEFINED__ */


#ifndef ___DGraphEvents_DISPINTERFACE_DEFINED__
#define ___DGraphEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DGraphEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DGraphEvents,0x106D39E7,0xC7AF,0x11D1,0xAF,0xFE,0x00,0x00,0xC0,0x3E,0x61,0x8C);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("106D39E7-C7AF-11D1-AFFE-0000C03E618C")
    _DGraphEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGraphEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGraphEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGraphEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGraphEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGraphEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGraphEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGraphEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGraphEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DGraphEventsVtbl;

    interface _DGraphEvents
    {
        CONST_VTBL struct _DGraphEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGraphEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGraphEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGraphEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGraphEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGraphEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGraphEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGraphEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGraphEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Graph,0x106D39E8,0xC7AF,0x11D1,0xAF,0xFE,0x00,0x00,0xC0,0x3E,0x61,0x8C);

#ifdef __cplusplus

class DECLSPEC_UUID("106D39E8-C7AF-11D1-AFFE-0000C03E618C")
Graph;
#endif
#endif /* __GRAPHCONTROLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


