#include "HDTTriple.h"

HDTTriple::HDTTriple(TripleString *triple) : triple(triple)
{
}

HDTTriple::~HDTTriple()
{
  if ( triple )
  {
    triple = NULL;
  }
}

string
HDTTriple::get_subject() const
{
  return triple -> getSubject();
}

string
HDTTriple::get_object() const
{
  return triple -> getObject();
}

string
HDTTriple::get_predicate() const
{
  return triple -> getPredicate();
}
