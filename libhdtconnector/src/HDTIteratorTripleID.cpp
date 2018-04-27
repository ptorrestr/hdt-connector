#include "HDTIteratorTripleID.h"

HDTIteratorTripleID::HDTIteratorTripleID(IteratorTripleID *iter) : iter(iter)
{
}

HDTIteratorTripleID::~HDTIteratorTripleID()
{
	if ( iter )
	{
		delete iter;
		iter = NULL;
	}
}

boost::python::tuple
HDTIteratorTripleID::next()
{
	if ( iter -> hasNext() )
	{
		// Copy values directly into python tuple.
		// This way, we can save tansfer time.
		TripleID *next = iter ->next();
		return boost::python::make_tuple(next ->getSubject(), 
				next ->getPredicate(),
				next ->getObject());
	}
	PyErr_SetString(PyExc_StopIteration, "No more data");
	throw_error_already_set();
	return boost::python::make_tuple();
}
