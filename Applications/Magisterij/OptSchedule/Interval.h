//////////////////////////////////////////////////////////////////////////////////////
//			Interval tipa [ )
//////////////////////////////////////////////////////////////////////////////////////
template <class _T> class Interval {
public:
	Interval() {}
	Interval(_T LowerBound, _T UpperBound);

	virtual	bool	IsIn( _T point );
	bool					IsOut( _T point ) { return !IsIn(point); }

	_T		GetLB() { return lb; }
	_T		GetUB() { return ub; }
private:
	_T		lb;
	_T		ub;
};

template<class _T> bool Interval<_T>::IsIn(_T pnt) 
{
	if( pnt >= lb && pnt < ub )
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////////////////
//			Interval tipa [ ]
//////////////////////////////////////////////////////////////////////////////////////
template<class _T> class ClosedInterval : public Interval<_T> {
public:
	bool IsIn(_T point);
};

template<class _T> bool ClosedInterval<_T>::IsIn(_T pnt) 
{
	if( pnt >= lb && pnt <= ub )
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////////////////
//			Interval tipa ( )
//////////////////////////////////////////////////////////////////////////////////////
template<class _T> class OpenInterval : public Interval<_T> {
public:
	bool IsIn(_T point);
};

template<class _T> bool OpenInterval<_T>::IsIn(_T point) 
{
	if( point > lb && point < ub )
		return true;
	else
		return false;
}
