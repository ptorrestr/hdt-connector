#include "HDTIterator.h"

HDTIterator::HDTIterator(IteratorTripleString *iter) : iter(iter)
{
}

HDTIterator::~HDTIterator()
{
	if ( iter )
	{
		delete iter;
		iter = NULL;
	}
}

boost::python::tuple
HDTIterator::next()
{
	if ( iter->hasNext() ) //Iterator has next element
	{
		TripleString *next = iter ->next();
		return boost::python::make_tuple(next ->getSubject(),
				next ->getPredicate(),
				next ->getObject());
	}
  PyErr_SetString(PyExc_StopIteration, "No more data");
  throw_error_already_set();
	return boost::python::make_tuple();
}
