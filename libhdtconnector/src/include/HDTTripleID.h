#ifndef HDTTRIPLEID_H
#define HDTTRIPLEID_H

#include <HDTManager.hpp>
#include <memory>

using namespace std;
using namespace hdt;

class HDTTripleID
{
private:
	unsigned int subject;
	unsigned int predicate;
	unsigned int object;

public:
  HDTTripleID(TripleID *triple);
  virtual ~HDTTripleID();

  unsigned int get_subject() const;
  unsigned int get_predicate() const;
  unsigned int get_object() const;
};

#endif
