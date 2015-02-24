#include <HDTConnector.h>

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
HDTConnector::search(const string& uri1, const string& uri2, const string& uri3)
{
	IteratorTripleString *iter = hdt -> search(uri1.c_str(), uri2.c_str(), uri3.c_str());
	return boost::shared_ptr<HDTIterator>(new HDTIterator(iter));
}

