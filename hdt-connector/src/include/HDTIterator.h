#ifndef HDTITERATOR_H
#define HDTITERATOR_H

#include <HDTManager.hpp>
#include <boost/python.hpp>

using namespace std;
using namespace hdt;
namespace py = boost::python;

class HDTIterator
{
private:
	IteratorTripleString *iter = NULL;

public:
	HDTIterator(IteratorTripleString *iter);
	virtual ~HDTIterator();

	bool has_next();
	py::list next();
};

#endif 
