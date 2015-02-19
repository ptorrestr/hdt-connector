#include <ConvertProgress.h>

void
ConvertProgress::notifyProgress(float level, const char *section)
{
	cout << section << ": " << level << " %";
	cout << "\r " << section << ": " << level << " % \r";
	cout.flush();
}
