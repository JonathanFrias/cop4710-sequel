// timeStamp.c for wSQL

// This creates a timestamp from the system time. Looking at time.h for a better alternative

// includes
#include "nick.h"
#include <time.h>

// defines

// structs


// prototypes


char *timeStamp()
{
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(time_stamp, 26, "date (%m%d%Y) %r", &timeinfo);
	puts(time_stamp);

	return time_stamp;
} // end timeStamp()
