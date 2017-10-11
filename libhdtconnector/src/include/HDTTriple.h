#ifndef HDTTRIPLE_H
#define HDTTRIPLE_H

#include <string>
#include <boost/python.hpp>
#include <HDTManager.hpp>

using namespace std;
using namespace hdt;
using namespace boost::python;

class HDTTriple
{
private:
  TripleString *triple = NULL;

public:
  HDTTriple(TripleString *triple);
  virtual ~HDTTriple();

  string get_subject() const;
  string get_predicate() const;
  string get_object() const;
};

#endif
