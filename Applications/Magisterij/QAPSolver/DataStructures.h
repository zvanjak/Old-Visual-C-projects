#ifndef __DATA_STRUCTURES
#define __DATA_STRUCTURES

class ThreadParam {
public:
	CDocument		*pDoc;
	IQAPSolver	*pQAP;

	ThreadParam(CDocument *inDoc, IQAPSolver *inQAP) { pDoc=inDoc; pQAP=inQAP; }
	ThreadParam(const ThreadParam &copy) { pDoc=copy.pDoc; pQAP=copy.pQAP; }
};

#endif

