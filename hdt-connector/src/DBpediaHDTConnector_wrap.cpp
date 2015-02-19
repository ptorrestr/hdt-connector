#include <boost/python.hpp>
#include <DBpediaHDTConnector.h>

using namespace boost::python;

static boost::shared_ptr<DBpediaHDTConnector> makeClass(const string &val)
{
	return boost::shared_ptr<DBpediaHDTConnector>(new DBpediaHDTConnector(val));
}

BOOST_PYTHON_MODULE(hdtconnector)
{
	
	class_<DBpediaHDTConnector, boost::shared_ptr<DBpediaHDTConnector> >("DBpediaHDTConnector", init<string>())
		.def("__init__", make_constructor(makeClass))
		.def("is_redirected", &DBpediaHDTConnector::is_redirected)
		.def("get_dbpedia_url_for_title", &DBpediaHDTConnector::get_dbpedia_url_for_title)
		.def("select_dbpedia_url_of_title", &DBpediaHDTConnector::select_dbpedia_url_of_title)
		.def("select_redirected_pages_to", &DBpediaHDTConnector::select_redirected_pages_to)
		.def("is_disambiugation_page", &DBpediaHDTConnector::is_disambiugation_page)
		.def("select_rdfs_comment_of_resource", &DBpediaHDTConnector::select_rdfs_comment_of_resource)
		.def("get_ambigous_page", &DBpediaHDTConnector::get_ambigous_page)
		.def("disambiguation_pages", &DBpediaHDTConnector::disambiguation_pages)
		.def("get_dbpedia_labels", &DBpediaHDTConnector::get_dbpedia_labels)
		.def("get_dbpedia_classes_of_res", &DBpediaHDTConnector::get_dbpedia_classes_of_res)
		.def("get_dbpedia_categories_of_res", &DBpediaHDTConnector::get_dbpedia_categories_of_res)
		.def("is_redirect", &DBpediaHDTConnector::is_redirect)
		.def("get_definition", &DBpediaHDTConnector::get_definition)
	;
}
