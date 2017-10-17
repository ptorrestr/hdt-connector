#ifndef HDTITERATORTRIPLEID_H
#define HDTITERATORTRIPLEID_H

#include <HDTManager.hpp>
#include "HDTTripleID.h"

using namespace std;
using namespace hdt;

class HDTIteratorTripleID
{
private:
  IteratorTripleID *iter = NULL;

public:
  HDTIteratorTripleID(IteratorTripleID *iter);
  virtual ~HDTIteratorTripleID();

  bool has_next() const;
  shared_ptr<HDTTripleID> next();
};

#endif
