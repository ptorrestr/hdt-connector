#include "HDTIteratorTripleID.h"
#include "HDTConnector.h"

HDTIteratorTripleID::HDTIteratorTripleID(IteratorTripleID *iter, HDTConnector *connector, bool ext)
	: iter(iter), connector(connector), ext(ext)
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
		if ( ext )
		{
			unsigned int subject = next ->getSubject();
			unsigned int predicate = next ->getPredicate();
			unsigned int object = next ->getObject();
			return boost::python::make_tuple( subject, predicate,
					object, connector ->is_shared( subject), 
					connector ->is_shared(object), connector ->is_literal( object)
					);
		}
		else
		{
			return boost::python::make_tuple( next ->getSubject(),
					next ->getPredicate(),
					next ->getObject()
					);
		}
	}
	PyErr_SetString(PyExc_StopIteration, "No more data");
	throw_error_already_set();
	return boost::python::make_tuple();
}
