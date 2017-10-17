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

bool
HDTIteratorTripleID::has_next() const
{
  if ( !iter )
  {
    return false;
  }
  return iter -> hasNext();
}

shared_ptr<HDTTripleID>
HDTIteratorTripleID::next()
{
  if ( iter -> hasNext() )
  {
    return make_shared<HDTTripleID>( iter -> next() );
  }
  return nullptr;
}
