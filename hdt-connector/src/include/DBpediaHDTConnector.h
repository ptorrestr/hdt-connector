#ifndef DBPEDIA_HDT_CONNECTOR
#define DBPEDIA_HDT_CONNECTOR

#include <iostream>
#include <HDTManager.hpp>
#include <ConvertProgress.h>
#include <boost/python.hpp>
#include <HDTIterator.h>

using namespace std;
using namespace hdt;
namespace py = boost::python;

class DBpediaHDTConnector
{
private: 
	static const string REDIRECT_PROP;
	static const string CONCEPT_TITLE_PROP;
	static const string DISAMB_PROP;
	static const string COMMENT_PROP;
	static const string LABEL_PROP;
	static const string RDF_TYPE;
	static const string DCTERMS_SUBJ;
	HDT *dbpediaHDT;

public:
	DBpediaHDTConnector(const string &hdt_file);
	~DBpediaHDTConnector();
	boost::shared_ptr<HDTIterator> get_iterator_over_all_concepts();
	py::list get_all_subjects();
	string get_definition(const string &uri);
	bool is_redirect(const string &from_uri, const string &to_uri);
	py::list get_dbpedia_categories_of_res(const string &uri);
	py::list get_dbpedia_classes_of_res(const string &uri);
	py::list get_dbpedia_labels(const string &uri);
	py::list disambiguation_pages(const string &dbpedia_page);
	string get_ambigous_page(const string &dbpedia_url);
	string select_rdfs_comment_of_resource(const string &dbpedia_page);
	bool is_disambiugation_page(const string &dbpedia_page);
	py::list select_redirected_pages_to(const string &dbpedia_page);
	string select_dbpedia_url_of_title(const string &title);
	string get_dbpedia_url_for_title(const string &title);
	bool is_redirected(const string &uri);

};

#endif
