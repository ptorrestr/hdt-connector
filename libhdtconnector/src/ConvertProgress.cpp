#include "ConvertProgress.h"

ConvertProgress::ConvertProgress(bool notify_) : notify(notify_)
{
}

void
ConvertProgress::notifyProgress(float level, float level2, const char *section)
{
	if ( notify ) 
	{
		cout << "\r " << section << ": " << level << " % \r";
		cout.flush();
	}
}
