#ifndef HDTITERATORTRIPLEID_H
#define HDTITERATORTRIPLEID_H

#include <HDTManager.hpp>
#include <boost/python.hpp>
#include <memory>

using namespace std;
using namespace hdt;
using namespace boost::python;

class HDTIteratorTripleID
{
private:
  IteratorTripleID *iter = NULL;

public:
  HDTIteratorTripleID(IteratorTripleID *iter);
  virtual ~HDTIteratorTripleID();

	boost::python::tuple next();
};

#endif
