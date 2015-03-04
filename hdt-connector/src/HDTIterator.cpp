#include <HDTIterator.h>

// Transform std::vector into python list
template<class T>
boost::python::list
std_vector_to_py_list(const std::vector<T>& v)
{
	typename std::vector<T>::const_iterator iter;
	boost::python::list l;
	for (iter = v.begin(); iter!= v.end(); ++iter) {
		l.append(*iter);
	}
	return l;
}

// Function to transform std::set into python list
template<class T>
boost::python::list
std_set_to_py_list(const std::set<T>& v)
{
	std::vector<T> u(v.begin(), v.end());
	return std_vector_to_py_list(u);
}


HDTIterator::HDTIterator(IteratorTripleString *iter) : iter(iter)
{
}

HDTIterator::~HDTIterator()
{
	if ( iter )
	{
		delete iter;
		iter = NULL;
	}
}

bool
HDTIterator::has_next()
{
	if ( !iter )
	{
		cout << "iter is null" << endl;
		return false;
	}
	return iter -> hasNext();
}

boost::python::list
HDTIterator::next()
{
	TripleString *ts = iter -> next();
	vector<boost::python::object> elements;
	// TODO: check for python3.
	string subject = ts -> getSubject();
	string predicate = ts -> getPredicate();
	string object = ts -> getObject();
	PyObject *py_subject =PyUnicode_FromString(subject.c_str() );
	PyObject *py_predicate = PyUnicode_FromString(predicate.c_str() );
	PyObject *py_object = PyUnicode_FromString(object.c_str() );
        boost::python::object o1(boost::python::handle<>((PyObject*)py_subject));
	boost::python::object o2(boost::python::handle<>((PyObject*)py_predicate));
	boost::python::object o3(boost::python::handle<>((PyObject*)py_object));
	boost::python::list py_list;
	py_list.append(o1);
	py_list.append(o2);
	py_list.append(o3);

	return py_list;
}
