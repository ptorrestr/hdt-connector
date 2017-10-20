#include "HDTTripleID.h"

HDTTripleID::HDTTripleID(TripleID *triple)
{
  // The triple provided by the interator is local
  // to the Iterator class, thus if next is call the object
  // is changed. To avoid inconsistency with pre-fetching, we
  // copy the value into a local variable that is deleted only
  // when the this object is not used anymore.
  this -> triple = new TripleID(triple -> getSubject(),
                        triple -> getPredicate(),
                        triple -> getObject());
}

HDTTripleID::~HDTTripleID()
{
  if ( triple )
  {
    delete triple;
    triple = NULL;
  }
}

unsigned int
HDTTripleID::get_subject() const
{
  return triple -> getSubject();
}

unsigned int
HDTTripleID::get_predicate() const
{
  return triple -> getPredicate();
}

unsigned int
HDTTripleID::get_object() const
{
  return triple -> getObject();
}
