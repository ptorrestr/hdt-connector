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
	vector<wstring> elements;
	// TODO: Linux allow unicode string. Find a new way to transform this in other system.
	string subject = ts -> getSubject();
	string predicate = ts -> getPredicate();
	string object = ts -> getObject();
	elements.push_back( wstring(subject.begin(), subject.end()) );
	elements.push_back( wstring(predicate.begin(), predicate.end()) );
	elements.push_back( wstring(object.begin(), object.end()) );

	return std_vector_to_py_list(elements);
}
