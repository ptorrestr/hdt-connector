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
  const string suri1( uri1.begin(), uri1.end() );
  const string suri2( uri2.begin(), uri2.end() );
  const string suri3( uri3.begin(), uri3.end() );
  TripleString ts(suri1, suri2, suri3);
  TripleID tid;
  hdt -> getDictionary() -> tripleStringtoTripleID(ts, tid);
  // Check if ids were found in hdtfile.
  if ( ( tid.getSubject() == 0 && !suri1.empty() ) ||
       ( tid.getPredicate() == 0 && !suri2.empty() ) ||
       ( tid.getObject() == 0 ) && !suri3.empty() )
  {
    return nullptr;
  }

  return make_shared<HDTIteratorTripleID>( hdt -> getTriples() -> search(tid) );
}
