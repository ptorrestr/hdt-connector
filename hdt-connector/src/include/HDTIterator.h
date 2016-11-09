#ifndef HDTITERATOR_H
#define HDTITERATOR_H

#include <hdt/HDTManager.hpp>
#include <boost/python.hpp>

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

	bool has_next();
	boost::python::list next();
};

#endif 
