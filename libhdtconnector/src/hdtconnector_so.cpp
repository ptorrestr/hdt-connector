#include <boost/python.hpp>
#include <HDTConnector.h>
#include <HDTIterator.h>

using namespace boost::python;

static boost::shared_ptr<HDTConnector> makeClass(const string &val)
{
	return boost::shared_ptr<HDTConnector>(new HDTConnector(val));
}

BOOST_PYTHON_MODULE(libhdtconnector)
{
	class_<HDTIterator, boost::shared_ptr<HDTIterator> >("HDTIterator", init<IteratorTripleString *>())
		.def("has_next", &HDTIterator::has_next)
		.def("next", &HDTIterator::next)
	;
	register_ptr_to_python< boost::shared_ptr<HDTIterator> >();
	
	class_<HDTConnector, boost::shared_ptr<HDTConnector> >("HDTConnector", init<string>())
		.def("__init__", make_constructor(makeClass))
		.def("search", &HDTConnector::search)
	;
}
