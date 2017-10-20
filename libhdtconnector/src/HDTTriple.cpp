#include "HDTTriple.h"

HDTTriple::HDTTriple(TripleString *triple)
{
  // The triple provided by the interator is local
  // to the Iterator class, thus if next is call the object
  // is changed. To avoid inconsistency with pre-fetching, we
  // copy the value into a local variable that is deleted only
  // when the this object is not used anymore.
  this -> triple = new TripleString( triple -> getSubject(), 
                             triple -> getPredicate(),
                             triple -> getObject() );
}

HDTTriple::~HDTTriple()
{
  if ( triple )
  {
    delete triple;
    triple = NULL;
  }
}

wstring
HDTTriple::get_subject() const
{
  return Utilities::utf8_to_unicode( triple -> getSubject() );
}

wstring
HDTTriple::get_object() const
{
  return Utilities::utf8_to_unicode( triple -> getObject() );
}

wstring
HDTTriple::get_predicate() const
{
  return Utilities::utf8_to_unicode( triple -> getPredicate() );
}
