// DBOptimSet.h : interface of the CDBOptimSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBOPTIMSET_H__A2079E5F_C38B_4FFD_AEEC_401746182C50__INCLUDED_)
#define AFX_DBOPTIMSET_H__A2079E5F_C38B_4FFD_AEEC_401746182C50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=39571A2A005D
class CTOptim
{
public:
	//##ModelId=39571A2A00A3
	CTOptim()
	{
		memset( (void*)this, 0, sizeof(*this) );
	};

	//##ModelId=39571A2A0099
	DATE m_EndTime;
	//##ModelId=39571A2A008F
	int m_IDMetodaOptim;
	//##ModelId=39571A2A0085
	int m_IDOptim;
	//##ModelId=39571A2A007D
	DATE m_StartTime;
	//##ModelId=39571A2A0073
	DATE m_Trajanje;


BEGIN_COLUMN_MAP(CTOptim)
		COLUMN_ENTRY_TYPE(3, DBTYPE_DATE, m_EndTime)
		COLUMN_ENTRY_TYPE(5, DBTYPE_I4, m_IDMetodaOptim)
		COLUMN_ENTRY_TYPE(1, DBTYPE_I4, m_IDOptim)
		COLUMN_ENTRY_TYPE(2, DBTYPE_DATE, m_StartTime)
		COLUMN_ENTRY_TYPE(4, DBTYPE_DATE, m_Trajanje)
END_COLUMN_MAP()

};

//##ModelId=39571A280281
class CDBOptimSet : public CCommand<CAccessor<CTOptim> >
{
public:

	//##ModelId=39571A2802B5
	HRESULT Open()
	{
		CDataSource db;
		CSession	session;
		HRESULT		hr;

		CDBPropSet	dbinit(DBPROPSET_DBINIT);
		dbinit.AddProperty(DBPROP_AUTH_CACHE_AUTHINFO, true);
		dbinit.AddProperty(DBPROP_AUTH_ENCRYPT_PASSWORD, false);
		dbinit.AddProperty(DBPROP_AUTH_MASK_PASSWORD, false);
		dbinit.AddProperty(DBPROP_AUTH_PASSWORD, "");
		dbinit.AddProperty(DBPROP_AUTH_USERID, "Admin");
		dbinit.AddProperty(DBPROP_INIT_DATASOURCE, "D:\\Users\\Zvone\\Projects\\Database\\Optimization.mdb");
		dbinit.AddProperty(DBPROP_INIT_MODE, (long)19);
		dbinit.AddProperty(DBPROP_INIT_PROMPT, (short)4);
		dbinit.AddProperty(DBPROP_INIT_PROVIDERSTRING, "");
		dbinit.AddProperty(DBPROP_INIT_LCID, (long)1033);
		dbinit.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);

		hr = db.OpenWithServiceComponents("Microsoft.Jet.OLEDB.4.0", &dbinit);
		if (FAILED(hr))
			return hr;

		hr = session.Open(db);
		if (FAILED(hr))
			return hr;

		CDBPropSet	propset(DBPROPSET_ROWSET);
		propset.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		propset.AddProperty(DBPROP_IRowsetScroll, true);
		propset.AddProperty(DBPROP_IRowsetChange, true);
		propset.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE );

		hr = CCommand<CAccessor<CTOptim> >::Open(session, "SELECT * FROM TOptim", &propset);
		if (FAILED(hr))
			return hr;

		return MoveNext();
	}

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBOPTIMSET_H__A2079E5F_C38B_4FFD_AEEC_401746182C50__INCLUDED_)

