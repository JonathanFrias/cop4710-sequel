// timeStamp.c for wSQL

// This creates a timestamp from the system time. Looking at time.h for a better alternative
// timeStamp.c for wSQL

// includes
#include "nick.h"
#include <time.h>

// defines

// structs


// prototypes


char *timeStamp()
{
	time_t rawtime;
	struct tm *timeinfo;
	

	time(&rawtime); // gets the time_t
	timeinfo = gmtime(&rawtime); // assigns the struct tm to UTC
	
	timeinfo->tm_hour -= 5; // convert UTC to EST
	timeinfo->tm_hour %= 24;

        strftime(time_stamp, 80, "date (%m/%d/%Y)@ %R", timeinfo);
	printf("%s\n", time_stamp);

	return time_stamp;
} // end timeStamp()

