#include <DBpediaHDTConnector.h>

// Transform std::vector into python list
template<class T>
py::list
std_vector_to_py_list(const std::vector<T>& v)
{
	typename std::vector<T>::const_iterator iter;
	py::list l;
	for (iter = v.begin(); iter!= v.end(); ++iter) {
		l.append(*iter);
	}
	return l;
}

// Function to transform std::set into python list
template<class T>
py::list 
std_set_to_py_list(const std::set<T>& v)
{
	cout << "transforming" << endl;
	std::vector<T> u(v.begin(), v.end());
	return std_vector_to_py_list(u);
}

const string DBpediaHDTConnector::REDIRECT_PROP = "http://dbpedia.org/ontology/wikiPageRedirects";
const string DBpediaHDTConnector::CONCEPT_TITLE_PROP = "http://www.w3.org/2000/01/rdf-schema#label";
const string DBpediaHDTConnector::DISAMB_PROP = "http://dbpedia.org/ontology/wikiPageDisambiguates";
const string DBpediaHDTConnector::COMMENT_PROP = "http://www.w3.org/2000/01/rdf-schema#comment";
const string DBpediaHDTConnector::LABEL_PROP = "http://www.w3.org/2000/01/rdf-schema#label";
const string DBpediaHDTConnector::RDF_TYPE = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
const string DBpediaHDTConnector::DCTERMS_SUBJ = "http://purl.org/dc/terms/subject";

DBpediaHDTConnector::DBpediaHDTConnector(const string &hdt_file) : dbpediaHDT(NULL)
{
	try {
		ConvertProgress prog;
		this->dbpediaHDT = HDTManager::mapHDT(hdt_file.c_str(), &prog);
	}
	catch (...)
	{
		cerr << "Error createing the HDT!" << endl;
	}
}

DBpediaHDTConnector::~DBpediaHDTConnector()
{
	cout << "deleting HDT connector" << endl;
	if ( dbpediaHDT )
	{
		delete dbpediaHDT;
		dbpediaHDT = NULL;
	}
}

IteratorTripleString
*DBpediaHDTConnector::get_iterator_over_all_concepts()
{
	return this->dbpediaHDT->search("", "", "");
}

string 
DBpediaHDTConnector::get_definition(const string &uri)
{
	string result = "Wikipedia Category";
	IteratorTripleString *it = dbpediaHDT->search(uri.c_str(), 
					DBpediaHDTConnector::COMMENT_PROP.c_str(), 
					"");
	if ( it -> hasNext() )
	{
		TripleString *ts = it -> next();
		result = ts -> getObject().c_str();
	}

	if ( it )
	{
		delete it;
		it = NULL;
	}
	return result;
}

bool 
DBpediaHDTConnector::is_redirect(const string &from_uri, const string &to_uri)
{
	bool result = false;
	IteratorTripleString *it = dbpediaHDT->search(from_uri.c_str(), 
					DBpediaHDTConnector::REDIRECT_PROP.c_str(), 
					to_uri.c_str());
	if ( it -> hasNext() )
		result = true;
	if ( it )
	{
		delete it;
		it = NULL;
	}	
	return result;
}

py::list 
DBpediaHDTConnector::get_dbpedia_categories_of_res(const string &uri)
{
	set<string> elements;
	IteratorTripleString *it = dbpediaHDT->search(uri.c_str(),
					DBpediaHDTConnector::DCTERMS_SUBJ.c_str(),
					"");
	while ( it -> hasNext() )
	{
		TripleString *res = it -> next();
		const char *cat = res -> getObject().c_str();
		elements.insert(cat);
	}
	if ( it )
	{
		delete it;
		it = NULL;
	}
	return std_set_to_py_list(elements);
}

py::list 
DBpediaHDTConnector::get_dbpedia_classes_of_res(const string &uri)
{
	set<string> elements;
	IteratorTripleString *it = dbpediaHDT -> search(uri.c_str(),
					DBpediaHDTConnector::RDF_TYPE.c_str(),
					"");
	while ( it -> hasNext() )
	{
		TripleString *res = it -> next();
		const char *cat = res -> getObject().c_str();
		elements.insert(cat);
	}
	if ( it )
	{
		delete it;
		it = NULL;
	}
	return std_set_to_py_list(elements);
}

py::list 
DBpediaHDTConnector::get_dbpedia_labels(const string &uri)
{
	set<string> elements;
	IteratorTripleString *it = dbpediaHDT -> search(uri.c_str(),
					DBpediaHDTConnector::LABEL_PROP.c_str(),
					"");
	while ( it -> hasNext() )
	{
		TripleString *res = it -> next();
		string lbl = res -> getObject().c_str();
		if ( lbl.substr(0,1) == "\"" )
			lbl = lbl.substr(1);
		if ( lbl.substr(lbl.size()-4,lbl.size()) == "\"@en" )
			lbl = lbl.substr(0, lbl.size() - 4);
		elements.insert(lbl);
	}
	if ( it )
	{
		delete it;
		it = NULL;
	}
	return std_set_to_py_list(elements);
}

py::list 
DBpediaHDTConnector::disambiguation_pages(const string &dbpedia_page)
{
	set<string> elements;
	IteratorTripleString *it = dbpediaHDT -> search(dbpedia_page.c_str(),
					DBpediaHDTConnector::DISAMB_PROP.c_str(),
					"");
	while ( it -> hasNext() )
	{
		TripleString *ts = it -> next();
		string subj = ts -> getObject().c_str();
		elements.insert(subj);
	}
	if ( it )
	{
		delete it;
		it = NULL;
	}
	return std_set_to_py_list(elements);
}

//TODO: Check if this function is properly used
string 
DBpediaHDTConnector::get_ambigous_page(const string &dbpedia_url)
{
	string result = "";
	IteratorTripleString *it = dbpediaHDT -> search("",
					DBpediaHDTConnector::DISAMB_PROP.c_str(),
					dbpedia_url.c_str());
	while ( it -> hasNext() )
	{
		TripleString *ts = it -> next();
		string subj = ts -> getSubject().c_str();
		result = subj;
	}
	if ( it )
	{
		delete it;
		it = NULL;
	}
	return result;
}

// TODO: Check if this function is properly used
string 
DBpediaHDTConnector::select_rdfs_comment_of_resource(const string &dbpedia_page)
{
	string result = "";
	IteratorTripleString *it = dbpediaHDT -> search("",
					DBpediaHDTConnector::COMMENT_PROP.c_str(),
					"");
	while ( it -> hasNext() )
	{
		TripleString *ts = it -> next();
		string obj = ts -> getObject().c_str();
		result = obj;
	}
	if ( it )
	{
		delete it;
		it = NULL;
	}
	return result;
}

//TODO: Check if method is properly written
bool 
DBpediaHDTConnector::is_disambiugation_page(const string &dbpedia_page)
{
	bool result = false;
	IteratorTripleString *it = dbpediaHDT -> search(dbpedia_page.c_str(),
					DBpediaHDTConnector::DISAMB_PROP.c_str(),
					"");
	if ( it -> hasNext() )
		result = true;
	if ( it )
	{
		delete it;
		it = NULL;
	}
	return result;
}

py::list 
DBpediaHDTConnector::select_redirected_pages_to(const string &dbpedia_page)
{
	set<string> elements;
	IteratorTripleString *it = dbpediaHDT -> search("",
					DBpediaHDTConnector::REDIRECT_PROP.c_str(),
					dbpedia_page.c_str());
	while ( it -> hasNext() )
	{
		TripleString *ts = it -> next();
		string subj = ts -> getSubject().c_str();
		elements.insert(subj);
	}
	if ( it )
	{
		delete it;
		it = NULL;
	}
	return std_set_to_py_list(elements);
}

string 
DBpediaHDTConnector::select_dbpedia_url_of_title(const string &title)
{
	string eng_title = "\"" + title + "\"@en";
	string result = "";
	IteratorTripleString *it = NULL;
	try 
	{
		it = dbpediaHDT -> search("",
					DBpediaHDTConnector::REDIRECT_PROP.c_str(),
					eng_title.c_str());
		while ( it -> hasNext() )
		{
			TripleString *ts = it -> next();
			string subj = ts -> getSubject().c_str();
			string prefix1 = "http://dbpedia.org/resource/";
			string prefix2 = "http://dbpedia.org/resource/Category:";
			if ( subj.substr(0, prefix1.size()) == prefix1 
				&& !(subj.substr(0, prefix2.size()) == prefix2))
			{
				result = subj;
				break;
			} 
		}

		if ( result.size () == 0) 
		{
			string possible_url = get_dbpedia_url_for_title(title);
			IteratorTripleString *it2 = dbpediaHDT -> search("",
					possible_url.c_str(), 
					"");	
			if ( it -> hasNext() )
				result = possible_url;
		}
	}
	catch ( char *e)
	{
		cerr << "Error in select_dbpedia_url_of_title: " << e << endl;
	}
	if ( it )
	{
		delete it;
		it = NULL;
	}
	return result;
}

string      
replaceAll(string subject, const string& search, const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}


string 
DBpediaHDTConnector::get_dbpedia_url_for_title(const string &title)
{
	string result = replaceAll(title, " ", "_");
	result = "http://dbpedia.org/resource/" + result;
	return result;
}

bool
DBpediaHDTConnector::is_redirected(const string &uri)
{
	bool result = false;
	IteratorTripleString *it = dbpediaHDT -> search (uri.c_str(),
                                        DBpediaHDTConnector::REDIRECT_PROP.c_str(),
                                        "");
        if ( it -> hasNext() )
                result = true;
	if ( it )
	{
		delete it;
		it = NULL;
	}
        return result;
}
