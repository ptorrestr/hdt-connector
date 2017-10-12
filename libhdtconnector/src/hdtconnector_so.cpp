#include <boost/python.hpp>
#include <memory>
#include "HDTConnector.h"
#include "HDTIterator.h"
#include "HDTTriple.h"

using namespace std;
using namespace boost::python;

static shared_ptr<HDTConnector> init_from_c_string(const string &val)
{
	return make_shared<HDTConnector>(val);
}

BOOST_PYTHON_MODULE(libhdtconnector)
{
  class_<HDTTriple, shared_ptr<HDTTriple> >("HDTTriple", no_init)
    .def("get_subject", &HDTTriple::get_subject )
    .def("get_predicate", &HDTTriple::get_predicate )
    .def("get_object", &HDTTriple::get_object )
  ;
  //register_ptr_to_python< shared_ptr<HDTTriple> >();

	class_<HDTIterator, shared_ptr<HDTIterator> >("HDTIterator", no_init)
		.def("has_next", &HDTIterator::has_next)
		.def("next", &HDTIterator::next)
	;
	//register_ptr_to_python< shared_ptr<HDTIterator> >();
	
	class_<HDTConnector, shared_ptr<HDTConnector> >("HDTConnector", no_init)
		.def("__init__", make_constructor(&init_from_c_string))
		.def("search", &HDTConnector::search)
	;
}
