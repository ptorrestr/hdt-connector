#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <memory>
#include "HDTConnector.h"
#include "HDTIterator.h"
#include "HDTIteratorTripleID.h"
#include "NumpyScalarConverter.h"

// http://docs.scipy.org/doc/numpy/reference/c-api.array.html#importing-the-api
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL printnum_cpp_module_PyArray_API

using namespace std;
using namespace boost::python;
namespace np = boost::python::numpy;

static shared_ptr<HDTConnector> init_from_c_string(const string &val)
{
	// By default, the notification messages are not displayed
	return make_shared<HDTConnector>(val, false);
}

static shared_ptr<HDTConnector> init_from_c_string_notify(const string &val, bool notify)
{
	return make_shared<HDTConnector>(val, notify);
}

// Overload search_id function in order to allow calls with 3-4 parameters
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(search_id_overload, HDTConnector::search_id, 3, 4)

// For functions with similar name, we need to wrap them in a pointer
// and give that pointer to python
shared_ptr<HDTIteratorTripleID> (HDTConnector::*search_id_1)
	(const wstring& uri1, const wstring& uri2, const wstring& uri3, bool ext) = &HDTConnector::search_id;
shared_ptr<HDTIteratorTripleID> (HDTConnector::*search_id_2)
	(unsigned int id1, unsigned int id2, unsigned int id3, bool ext) = &HDTConnector::search_id;

// For our iterators, __iter__ method needs to pass the same object
// so, it basically does nothing.
inline object pass_through(object const& o) { return o; }

BOOST_PYTHON_MODULE(libhdtconnector)
{
	// http://docs.scipy.org/doc/numpy/reference/c-api.array.html#importing-the-api
	import_array();
	//boost::python::to_python_converter<unsigned int, NumpyScalarConverter<unsigned int>>();
	// Register conversion for all scalar types.
	NumpyScalarConverter<signed char>();
	NumpyScalarConverter<short>();
	NumpyScalarConverter<int>();
	NumpyScalarConverter<long>();
	NumpyScalarConverter<long long>();
	NumpyScalarConverter<unsigned char>();
	NumpyScalarConverter<unsigned short>();
	NumpyScalarConverter<unsigned int>();
	NumpyScalarConverter<unsigned long>();
	NumpyScalarConverter<unsigned long long>();
	NumpyScalarConverter<float>();
	NumpyScalarConverter<double>();

	enum_<TripleComponentRole>("triple_role")
		.value("subject", SUBJECT)
		.value("predicate", PREDICATE)
		.value("object", OBJECT)
		;

	class_<HDTIterator, shared_ptr<HDTIterator> >("HDTIterator", no_init)
		.def("__iter__", pass_through) // inline function
		.def("__next__", &HDTIterator::next)
		;
	class_<HDTIteratorTripleID, shared_ptr<HDTIteratorTripleID> >("HDTIteratorTripleID", no_init)
		.def("__iter__", pass_through) // inline function
		.def("__next__", &HDTIteratorTripleID::next)
		;

	class_<HDTConnector, shared_ptr<HDTConnector> >("HDTConnector", no_init)
		.def("__init__", make_constructor(&init_from_c_string))
		.def("__init__", make_constructor(&init_from_c_string_notify))
		.def("search", &HDTConnector::search)
		.def("search_id", search_id_1, search_id_overload((
					boost::python::arg("uri1"),
					boost::python::arg("uri2"),
					boost::python::arg("uri3"),
					boost::python::arg("ext") = false
					))) //Note that this is a pointer to a function
		.def("search_id", search_id_2, search_id_overload((
					boost::python::arg("id1"),
					boost::python::arg("id2"),
					boost::python::arg("id3"),
					boost::python::arg("ext") = false
					))) //Note that this is a pointer to a function
		.def("id_to_uri", &HDTConnector::id_to_uri)
		.def("uri_to_id", &HDTConnector::uri_to_id)
		.def("is_shared", &HDTConnector::is_shared)
		.def("is_literal", &HDTConnector::is_literal)
		;
}
