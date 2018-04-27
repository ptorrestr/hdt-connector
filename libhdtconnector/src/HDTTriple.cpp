#include "HDTTriple.h"

HDTTriple::HDTTriple(TripleString *triple)
{
  // The triple provided by the interator is local
  // to the Iterator class, thus if next is call the object
  // is changed. To avoid inconsistency with pre-fetching, we
  // copy the value into a local variable that is deleted only
  // when the this object is not used anymore.
	this ->subject = Utilities::utf8_to_unicode( triple -> getSubject() );
	this ->predicate = Utilities::utf8_to_unicode( triple -> getPredicate() );
	this ->object = Utilities::utf8_to_unicode( triple -> getObject() );
}

HDTTriple::~HDTTriple()
{
}

wstring
HDTTriple::get_subject() const
{
	return subject;
}

wstring
HDTTriple::get_object() const
{
	return object;
}

wstring
HDTTriple::get_predicate() const
{
	return predicate;
}
