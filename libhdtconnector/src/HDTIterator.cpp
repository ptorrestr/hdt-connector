#include <HDTIterator.h>

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

shared_ptr<HDTTriple>
HDTIterator::next()
{
	if ( iter->hasNext() ) //Iterator has next element
	{
		return make_shared<HDTTriple>( iter -> next());
	}
	return nullptr;
}
