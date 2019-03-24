

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Feb 16 14:34:49 2017
 */
/* Compiler settings for PrikazRasporedaIspita.odl:
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


#ifndef __PrikazRasporedaIspita_h_h__
#define __PrikazRasporedaIspita_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DPrikazRasporedaIspita_FWD_DEFINED__
#define ___DPrikazRasporedaIspita_FWD_DEFINED__
typedef interface _DPrikazRasporedaIspita _DPrikazRasporedaIspita;
#endif 	/* ___DPrikazRasporedaIspita_FWD_DEFINED__ */


#ifndef ___DPrikazRasporedaIspitaEvents_FWD_DEFINED__
#define ___DPrikazRasporedaIspitaEvents_FWD_DEFINED__
typedef interface _DPrikazRasporedaIspitaEvents _DPrikazRasporedaIspitaEvents;
#endif 	/* ___DPrikazRasporedaIspitaEvents_FWD_DEFINED__ */


#ifndef __PrikazRasporedaIspita_FWD_DEFINED__
#define __PrikazRasporedaIspita_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrikazRasporedaIspita PrikazRasporedaIspita;
#else
typedef struct PrikazRasporedaIspita PrikazRasporedaIspita;
#endif /* __cplusplus */

#endif 	/* __PrikazRasporedaIspita_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __PRIKAZRASPOREDAISPITALib_LIBRARY_DEFINED__
#define __PRIKAZRASPOREDAISPITALib_LIBRARY_DEFINED__

/* library PRIKAZRASPOREDAISPITALib */
/* [control][helpstring][helpfile][version][uuid] */ 


DEFINE_GUID(LIBID_PRIKAZRASPOREDAISPITALib,0xA76A2D98,0x8C06,0x4671,0xB7,0x10,0x97,0xDC,0x48,0xCC,0x5D,0x85);

#ifndef ___DPrikazRasporedaIspita_DISPINTERFACE_DEFINED__
#define ___DPrikazRasporedaIspita_DISPINTERFACE_DEFINED__

/* dispinterface _DPrikazRasporedaIspita */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DPrikazRasporedaIspita,0x1030F5CF,0xFA20,0x413B,0x82,0x4F,0xC0,0xD8,0x9D,0x37,0x27,0x2D);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1030F5CF-FA20-413B-824F-C0D89D37272D")
    _DPrikazRasporedaIspita : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DPrikazRasporedaIspitaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DPrikazRasporedaIspita * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DPrikazRasporedaIspita * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DPrikazRasporedaIspita * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DPrikazRasporedaIspita * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DPrikazRasporedaIspita * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DPrikazRasporedaIspita * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DPrikazRasporedaIspita * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DPrikazRasporedaIspitaVtbl;

    interface _DPrikazRasporedaIspita
    {
        CONST_VTBL struct _DPrikazRasporedaIspitaVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DPrikazRasporedaIspita_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DPrikazRasporedaIspita_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DPrikazRasporedaIspita_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DPrikazRasporedaIspita_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DPrikazRasporedaIspita_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DPrikazRasporedaIspita_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DPrikazRasporedaIspita_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DPrikazRasporedaIspita_DISPINTERFACE_DEFINED__ */


#ifndef ___DPrikazRasporedaIspitaEvents_DISPINTERFACE_DEFINED__
#define ___DPrikazRasporedaIspitaEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DPrikazRasporedaIspitaEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DPrikazRasporedaIspitaEvents,0x285F6332,0x4359,0x418F,0xBE,0xF2,0xB1,0xF6,0x9A,0x5F,0xB6,0x78);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("285F6332-4359-418F-BEF2-B1F69A5FB678")
    _DPrikazRasporedaIspitaEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DPrikazRasporedaIspitaEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DPrikazRasporedaIspitaEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DPrikazRasporedaIspitaEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DPrikazRasporedaIspitaEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DPrikazRasporedaIspitaEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DPrikazRasporedaIspitaEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DPrikazRasporedaIspitaEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DPrikazRasporedaIspitaEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DPrikazRasporedaIspitaEventsVtbl;

    interface _DPrikazRasporedaIspitaEvents
    {
        CONST_VTBL struct _DPrikazRasporedaIspitaEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DPrikazRasporedaIspitaEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DPrikazRasporedaIspitaEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DPrikazRasporedaIspitaEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DPrikazRasporedaIspitaEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DPrikazRasporedaIspitaEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DPrikazRasporedaIspitaEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DPrikazRasporedaIspitaEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DPrikazRasporedaIspitaEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_PrikazRasporedaIspita,0x58E19248,0xA94F,0x4762,0xB5,0x43,0x0F,0x1C,0xD6,0xC3,0xB7,0x1D);

#ifdef __cplusplus

class DECLSPEC_UUID("58E19248-A94F-4762-B543-0F1CD6C3B71D")
PrikazRasporedaIspita;
#endif
#endif /* __PRIKAZRASPOREDAISPITALib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


