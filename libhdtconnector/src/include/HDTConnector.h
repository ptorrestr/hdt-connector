#ifndef HDT_CONNECTOR
#define HDT_CONNECTOR

#include <iostream>
#include <memory>
#include <HDTManager.hpp>
#include "ConvertProgress.h"
#include "HDTIterator.h"
#include "HDTIteratorTripleID.h"

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
  shared_ptr<HDTIteratorTripleID> search_id(const wstring& uri1, const wstring& uri2, const wstring& uri3);
  string id_to_uri(unsigned int id, TripleComponentRole role);
  unsigned int uri_to_id(string uri, TripleComponentRole role);
};

#endif
