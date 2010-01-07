#include "../interface/TRootEvent.h"

ClassImp(TRootEvent)


char * TRootEvent::asciiCollisionTime() const
{
	unsigned long microseconds = (collisionTime_&0xffffffff);
	time_t firstTime(collisionTime_ >> 32);
	const struct tm *myLocalTime = localtime(&firstTime);
	static char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	static char result[26];
	sprintf( result
		,"%.2d-%.3s-%.2d %.2d:%.2d:%.2d.%.6d"
		,myLocalTime->tm_mday
		,months[myLocalTime->tm_mon]
		,(myLocalTime->tm_year)%100
		,myLocalTime->tm_hour
		,myLocalTime->tm_min
		,myLocalTime->tm_sec
		,int(microseconds)
	);
		return result;
}
