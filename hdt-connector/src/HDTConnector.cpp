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

boost::shared_ptr<HDTIterator>
HDTConnector::search(const wstring& w_uri1, const wstring& w_uri2, const wstring& w_uri3)
{
	const string uri1( w_uri1.begin(), w_uri1.end() );
	const string uri2( w_uri2.begin(), w_uri2.end() );
	const string uri3( w_uri3.begin(), w_uri3.end() );
	IteratorTripleString *iter = hdt -> search(uri1.c_str(), uri2.c_str(), uri3.c_str());
	return boost::shared_ptr<HDTIterator>(new HDTIterator(iter));
}

