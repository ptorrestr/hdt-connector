#ifndef HDTTRIPLE_H
#define HDTTRIPLE_H

#include <string>
#include <boost/python.hpp>
#include <HDTManager.hpp>
#include "Utilities.h"

using namespace std;
using namespace hdt;
using namespace boost::python;

class HDTTriple
{
private:
	wstring subject;
	wstring predicate;
	wstring object;

public:
  HDTTriple(TripleString *triple);
  virtual ~HDTTriple();

  wstring get_subject() const;
  wstring get_predicate() const;
  wstring get_object() const;
};

#endif
