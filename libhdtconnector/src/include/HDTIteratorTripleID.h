#ifndef HDTITERATORTRIPLEID_H
#define HDTITERATORTRIPLEID_H

#include <HDTManager.hpp>
#include <boost/python.hpp>
#include <memory>

using namespace std;
using namespace hdt;
using namespace boost::python;

class HDTConnector;

class HDTIteratorTripleID
{
private:
  IteratorTripleID *iter = NULL;
	HDTConnector *connector = NULL;
	bool ext = false;

public:
  HDTIteratorTripleID(IteratorTripleID *iter, HDTConnector *connector, bool ext);
  virtual ~HDTIteratorTripleID();

	boost::python::tuple next();
};

#endif
