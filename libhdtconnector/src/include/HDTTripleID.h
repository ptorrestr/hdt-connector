#ifndef HDTTRIPLEID_H
#define HDTTRIPLEID_H

#include <HDTManager.hpp>
#include <memory>

using namespace std;
using namespace hdt;

class HDTTripleID
{
private:
  TripleID *triple = NULL;

public:
  HDTTripleID(TripleID *triple);
  virtual ~HDTTripleID();

  unsigned int get_subject() const;
  unsigned int get_predicate() const;
  unsigned int get_object() const;
};

#endif
