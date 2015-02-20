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
	vector<string> elements;
	elements.push_back( ts -> getSubject() );
	elements.push_back( ts -> getPredicate() );
	elements.push_back( ts -> getObject() );

	return std_vector_to_py_list(elements);
}
