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

shared_ptr<HDTTriple>
HDTIterator::next()
{
	if ( iter->hasNext() ) //Iterator has next element
	{
		return make_shared<HDTTriple>( iter -> next());
	}
  PyErr_SetString(PyExc_StopIteration, "No more data");
  throw_error_already_set();
	return nullptr;
}
