#ifndef HDTITERATOR_H
#define HDTITERATOR_H

#include <HDTManager.hpp>
#include <boost/python.hpp>
#include <memory>

using namespace std;
using namespace hdt;
using namespace boost::python;

class HDTIterator
{
private:
	IteratorTripleString *iter = NULL;

public:
	HDTIterator(IteratorTripleString *iter);
	virtual ~HDTIterator();

	boost::python::tuple next();
};

#endif 
