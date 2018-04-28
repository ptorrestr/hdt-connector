#include "HDTConnector.h"

HDTConnector::HDTConnector(const string &hdt_file, bool notify) : hdt(NULL)
{
	try {
		ConvertProgress prog(notify);
		hdt = HDTManager::mapIndexedHDT(hdt_file.c_str(), &prog);
		if (get_header_property("_:dictionary", "<http://purl.org/dc/terms/format>")
      == "<http://purl.org/HDT/hdt#dictionaryLiteral>")
		{
			is_dictionary_literal = true;
			number_objects_literals = hdt ->getDictionary() ->getNobjectsLiterals();
		}
		number_shared = hdt -> getDictionary() ->getNshared();
		number_subjects = hdt ->getDictionary()  ->getNsubjects();
		mapping = hdt -> getDictionary() ->getMapping();
	}
	catch (...)
	{
	cerr << "Error when opening HDT file" << endl;
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
HDTConnector::search_id(const wstring& uri1, const wstring& uri2, const wstring &uri3, bool ext)
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
		return make_shared<HDTIteratorTripleID>( new IteratorTripleID(), this, ext);
	}
	return search_id(tid, ext);
}

shared_ptr<HDTIteratorTripleID>
HDTConnector::search_id(unsigned int id1, unsigned int id2, unsigned int id3, bool ext)
{
	TripleID tid(id1, id2, id3);
	return search_id(tid, ext);
}

shared_ptr<HDTIteratorTripleID>
HDTConnector::search_id(TripleID& triple, bool ext)
{
	// search should receive a const tripleID&
	return make_shared<HDTIteratorTripleID>( hdt -> getTriples() -> search(triple), this, ext);
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

bool
HDTConnector::is_shared(unsigned int object_id)
{
	return object_id <= number_shared ? true : false;
}

bool
HDTConnector::is_literal(unsigned int object_id)
{
	if ( is_dictionary_literal )
	{
		if ( is_shared(object_id) )
			return false;
		unsigned int local_object_id = mapping == MAPPING2 ?
			object_id - number_shared :	object_id - number_shared - number_subjects + 2;
		return local_object_id <= number_objects_literals ?  true : false ;
	}
	else
	{
		wstring uri = id_to_uri(object_id, TripleComponentRole::OBJECT);
		if ( uri.front() == '\'' || uri.front() == '"')
			return true;
		return false;
	}
}

string
HDTConnector::get_header_property(const string& subject, const string& predicate)
{
	string element("");
	IteratorTripleString *it = hdt ->getHeader() ->search(subject.c_str(), predicate.c_str(), "");
	if ( it ->hasNext() )
	{
		element = it ->next() ->getObject();
	}
	delete it;
	if ( element.size() <= 0 )
	{
		throw runtime_error("Property not found");
	}
	return element;
}
