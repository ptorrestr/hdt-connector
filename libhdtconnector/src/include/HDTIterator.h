#ifndef HDTITERATOR_H
#define HDTITERATOR_H

#include <HDTManager.hpp>
#include <boost/python.hpp>
#include <memory>
#include "HDTTriple.h"

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

	shared_ptr<HDTTriple> next();
};

#endif 
