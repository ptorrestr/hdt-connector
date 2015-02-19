#ifndef CONVERT_PROGRESS_H
#define CONVERT_PROGRESS_H

#include <HDTManager.hpp>
#include <iostream>

using namespace hdt;
using namespace std;

class ConvertProgress : public ProgressListener {
private:
public:
	virtual ~ConvertProgress() { }
	void notifyProgress(float level, const char *section);
};

#endif
