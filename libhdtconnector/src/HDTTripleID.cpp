#include "HDTTripleID.h"

HDTTripleID::HDTTripleID(TripleID *triple) : triple(triple)
{
}

HDTTripleID::~HDTTripleID()
{
  if ( triple )
  {
    // Note that triple is a reference, hence it 
    // cannot be deleted
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
