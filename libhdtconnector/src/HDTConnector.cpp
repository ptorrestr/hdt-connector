#include "HDTConnector.h"

HDTConnector::HDTConnector(const string &hdt_file) : hdt(NULL)
{
	try {
		ConvertProgress prog;
		hdt = HDTManager::mapIndexedHDT(hdt_file.c_str(), &prog);
	}
	catch (...)
	{
		cerr << "Error createing the HDT!" << endl;
	}
}

HDTConnector::~HDTConnector()
{
	if ( hdt )
	{
		delete hdt;
		hdt = NULL;
	}
}

shared_ptr<HDTIterator>
HDTConnector::search(const wstring& w_uri1, const wstring& w_uri2, const wstring& w_uri3)
{
	const string uri1( w_uri1.begin(), w_uri1.end() );
	const string uri2( w_uri2.begin(), w_uri2.end() );
	const string uri3( w_uri3.begin(), w_uri3.end() );
	IteratorTripleString *iter = hdt -> search(uri1.c_str(), uri2.c_str(), uri3.c_str());
	return make_shared<HDTIterator>(iter);
}

shared_ptr<HDTIteratorTripleID>
HDTConnector::search_id(const wstring& uri1, const wstring& uri2, const wstring &uri3)
{
  const string suri1 = Utilities::unicode_to_utf8(uri1);
  const string suri2 = Utilities::unicode_to_utf8(uri2);
  const string suri3 = Utilities::unicode_to_utf8(uri3);
  TripleString ts(suri1, suri2, suri3);
  TripleID tid;
  hdt -> getDictionary() -> tripleStringtoTripleID(ts, tid);
  // Check if ids were found in hdtfile.
  if ( ( tid.getSubject() == 0 && !suri1.empty() ) ||
       ( tid.getPredicate() == 0 && !suri2.empty() ) ||
       ( tid.getObject() == 0 && !suri3.empty() ) )
  {
    // If couldn't found the uris, return an empty iterator
    return make_shared<HDTIteratorTripleID>( new IteratorTripleID() );
  }
  return search_id(tid);
}

shared_ptr<HDTIteratorTripleID>
HDTConnector::search_id(unsigned int id1, unsigned int id2, unsigned int id3)
{
  TripleID tid(id1, id2, id3);
  return search_id(tid);
}

shared_ptr<HDTIteratorTripleID>
HDTConnector::search_id(TripleID& triple)
{
  // search should receive a const tripleID&
  return make_shared<HDTIteratorTripleID>( hdt -> getTriples() -> search(triple) );
}

wstring
HDTConnector::id_to_uri(unsigned int id, const TripleComponentRole& role)
{
  return Utilities::utf8_to_unicode(hdt -> getDictionary() -> idToString(id, role));
}

unsigned int
HDTConnector::uri_to_id(const wstring& uri, const TripleComponentRole& role)
{
  return hdt -> getDictionary() -> stringToId(
      Utilities::unicode_to_utf8(uri), role);
}
