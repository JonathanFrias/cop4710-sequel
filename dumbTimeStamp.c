// dumbTimeStamp.c for wSQL

// This creates a timestamp from the system time. Looking at time.h for a better alternative

// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// defines
#define     BUFSIZE    200

// structs
struct timeval tv;

// prototypes


int main (void) {
	// declarations
	struct timeval tv;
	int time;
	int new_time;
	int hours;
	int minutes;
	int day;
	int month;
	int year;	

	gettimeofday(&tv, NULL);
	time = tv.tv_sec; 		// get time in seconds since 1970
		//01/01/1970  //11/01/2015  // 5 hour b/w eastern and UTC
	new_time = time - 1446336000 - 18000; // seconds since Nov 1 15
					      // -18000 for UTC 
	day = (new_time / 86400) + 1;		// set day of the month
	month = 11;	// b/c time starts in Nov
			 // secs/year
	year = 1970 + (time/31557600);
	if (day > 30) { // dumb
		day %= 30; // wrap the day
		month++; // next month
	}
	if (month > 12) {
		month %= 12; // wrap the month
		year++; // next year
	}   
	new_time %= 86400;			// seconds in current day
	hours = ((new_time / 3600) % 24);	// get the current hour
	minutes = (new_time / 60) % 60;	// get the current minute

	printf("date (%02d/%02d/%4d):%02d:%02d\n", month, day, year, hours, minutes);
	
    	return 0;
} // end main()
