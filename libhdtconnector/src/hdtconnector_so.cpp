#include <boost/python.hpp>
#include "HDTConnector.h"
#include "HDTIterator.h"

using namespace std;
using namespace boost::python;

static shared_ptr<HDTConnector> init_from_c_string(const string &val)
{
	return shared_ptr<HDTConnector>(new HDTConnector(val));
}

BOOST_PYTHON_MODULE(libhdtconnector)
{
	class_<HDTIterator, shared_ptr<HDTIterator> >("HDTIterator", init<IteratorTripleString *>())
		.def("has_next", &HDTIterator::has_next)
		.def("next", &HDTIterator::next)
	;
	register_ptr_to_python< shared_ptr<HDTIterator> >();
	
	class_<HDTConnector, shared_ptr<HDTConnector> >("HDTConnector", no_init)
		.def("__init__", make_constructor(&init_from_c_string))
		.def("search", &HDTConnector::search)
	;
}
