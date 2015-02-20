#ifndef HDTUTILITIES
#define HDTUTILITIES

#include <boost/python.hpp>
#include <vector>
#include <set>

using namespace std;
namespace py = boost::python;

string
replaceAll(string subject, const string& search, const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

#endif
