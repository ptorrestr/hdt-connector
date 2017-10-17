#include <boost/python.hpp>
#include <memory>
#include "HDTConnector.h"
#include "HDTIterator.h"
#include "HDTIteratorTripleID.h"
#include "HDTTriple.h"
#include "HDTTripleID.h"

using namespace std;
using namespace boost::python;

static shared_ptr<HDTConnector> init_from_c_string(const string &val)
{
	return make_shared<HDTConnector>(val);
}

BOOST_PYTHON_MODULE(libhdtconnector)
{
  enum_<TripleComponentRole>("triple_role")
    .value("subject", SUBJECT)
    .value("predicate", PREDICATE)
    .value("object", OBJECT)
    ; 

  class_<HDTTriple, shared_ptr<HDTTriple> >("HDTTriple", no_init)
    .def("get_subject", &HDTTriple::get_subject )
    .def("get_predicate", &HDTTriple::get_predicate )
    .def("get_object", &HDTTriple::get_object )
    ;
  class_<HDTTripleID, shared_ptr<HDTTripleID> >("HDTTripleID", no_init)
    .def("get_subject", &HDTTripleID::get_subject )
    .def("get_predicate", &HDTTripleID::get_predicate )
    .def("get_object", &HDTTripleID::get_object )
    ;

	class_<HDTIterator, shared_ptr<HDTIterator> >("HDTIterator", no_init)
		.def("has_next", &HDTIterator::has_next)
		.def("next", &HDTIterator::next)
	  ;
  class_<HDTIteratorTripleID, shared_ptr<HDTIteratorTripleID> >("HDTIteratorTripleID", no_init)
    .def("has_next", &HDTIteratorTripleID::has_next)
    .def("next", &HDTIteratorTripleID::next)
	  ;

	class_<HDTConnector, shared_ptr<HDTConnector> >("HDTConnector", no_init)
		.def("__init__", make_constructor(&init_from_c_string))
		.def("search", &HDTConnector::search)
    .def("search_id", &HDTConnector::search_id)
    .def("id_to_uri", &HDTConnector::id_to_uri)
    .def("uri_to_id", &HDTConnector::uri_to_id)
	  ;
}
