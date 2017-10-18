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

shared_ptr<HDTTripleID>
HDTIteratorTripleID::next()
{
  if ( iter -> hasNext() )
  {
    return make_shared<HDTTripleID>( iter -> next() );
  }
  PyErr_SetString(PyExc_StopIteration, "No more data");
  throw_error_already_set();
  return nullptr;
}
