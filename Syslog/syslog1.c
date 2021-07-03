#include<stdio.h>
#include <syslog.h>

int main()
{
	setlogmask (LOG_UPTO (LOG_NOTICE));

	openlog ("syslogfile1", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	syslog (LOG_NOTICE, "syslog1 started");
	syslog (LOG_ERR, "Syslog1 first log");

	closelog ();
	return 0;
}
