#ifndef HDT_CONNECTOR
#define HDT_CONNECTOR

#include <iostream>
#include <memory>
#include <HDTManager.hpp>
#include "ConvertProgress.h"
#include "HDTIterator.h"
#include "HDTIteratorTripleID.h"
#include "Utilities.h"

using namespace std;
using namespace hdt;

class HDTConnector
{
private:
	HDT *hdt;
	bool is_dictionary_literal = false;

public:
	HDTConnector(const string &hdt_file, bool notify);
	virtual ~HDTConnector();
	shared_ptr<HDTIterator> search(const wstring& uri1, const wstring& uri2, const wstring& uri3);
  shared_ptr<HDTIteratorTripleID> search_id(const wstring& uri1, const wstring& uri2, const wstring& uri3, bool ext=false);
  shared_ptr<HDTIteratorTripleID> search_id(unsigned int id1, unsigned int id2, unsigned int id3, bool ext=false);
  shared_ptr<HDTIteratorTripleID> search_id(TripleID& triple, bool ext);
  wstring id_to_uri(unsigned int id, const TripleComponentRole& role);
  unsigned int uri_to_id(const wstring& uri, const TripleComponentRole& role);
	bool is_shared(unsigned int object_id);
	bool is_literal(unsigned int object_id);
	string get_header_property(const string& subject, const string& predicate);
};

#endif
