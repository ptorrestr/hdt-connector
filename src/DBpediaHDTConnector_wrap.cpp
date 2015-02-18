#include <boost/python.hpp>
#include <DBpediaHDTConnector.h>

char const* greet()
{
   return "hello, world";
}

using namespace boost::python;

BOOST_PYTHON_MODULE(hdtconnector)
{
	/*
	class_<DBpediaHDTConnector>("DBpediaHDTConnector")
		//.def("get_iterator_over_all_concepts", &DBpediaHDTConnector::get_iterator_over_all_concepts)
	.def("is_redirect", &DBpediaHDTConnector::is_redirect)
	;
	*/
	def("greet", greet);
}
