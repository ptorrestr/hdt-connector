#include "ConvertProgress.h"

void
ConvertProgress::notifyProgress(float level, float level2, const char *section)
{
	cout << section << ": " << level << " %";
	cout << "\r " << section << ": " << level << " % \r";
	cout.flush();
}
