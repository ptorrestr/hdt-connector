#include "HDTTripleID.h"

HDTTripleID::HDTTripleID(TripleID *triple)
{
  // The triple provided by the interator is local
  // to the Iterator class, thus if next is call the object
  // is changed. To avoid inconsistency with pre-fetching, we
  // copy the value into a local variable that is deleted only
  // when the this object is not used anymore.
	this ->subject = triple ->getSubject();
	this ->predicate = triple ->getPredicate();
	this ->object = triple ->getObject(); 
}

HDTTripleID::~HDTTripleID()
{
}

unsigned int
HDTTripleID::get_subject() const
{
  return subject;
}

unsigned int
HDTTripleID::get_predicate() const
{
  return predicate;
}

unsigned int
HDTTripleID::get_object() const
{
  return object;
}
