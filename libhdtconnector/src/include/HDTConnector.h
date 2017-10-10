#ifndef HDT_CONNECTOR
#define HDT_CONNECTOR

#include <iostream>
#include <HDTManager.hpp>
#include "ConvertProgress.h"
#include "HDTIterator.h"

using namespace std;
using namespace hdt;

class HDTConnector
{
private: 
	HDT *hdt;

public:
	HDTConnector(const string &hdt_file);
	virtual ~HDTConnector();
	shared_ptr<HDTIterator> search(const wstring& uri1, const wstring& uri2, const wstring& uri3);
};

#endif
