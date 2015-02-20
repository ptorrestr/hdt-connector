#ifndef HDT_CONNECTOR
#define HDT_CONNECTOR

#include <iostream>
#include <HDTManager.hpp>
#include <ConvertProgress.h>
#include <boost/python.hpp>
#include <HDTIterator.h>

using namespace std;
using namespace hdt;
using namespace boost::python;

class HDTConnector
{
private: 
	HDT *hdt;

public:
	HDTConnector(const string &hdt_file);
	virtual ~HDTConnector();
	boost::shared_ptr<HDTIterator> search(const string& uri1, const string& uri2, const string& uri3);
};

#endif
