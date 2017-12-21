#ifndef CONVERT_PROGRESS_H
#define CONVERT_PROGRESS_H

#include <HDTManager.hpp>
#include <iostream>

using namespace hdt;
using namespace std;

class ConvertProgress : public ProgressListener {
private:
	bool notify;
public:
	ConvertProgress(bool);
	void notifyProgress(float level, float level2, const char *section);
};

#endif
