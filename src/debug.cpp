#include "debug.h"

void error(const char* message)
{
	cerr << timestamp() << message << endl;
}

void warning(const char* message)
{
	clog << timestamp() << message << endl;
}

string timestamp(const char format[6])
{
	char beginDelimiter = format[0],
		dateDelimiter = format[1],
		separator = format[2],
		timeDelimiter = format[3],
		endDelimiter = format[4];
	struct tm time;
	time_t now = system_clock::to_time_t(system_clock::now());
	localtime(&now, &time);
	string stamp = "", append;
	stamp += beginDelimiter;
	append = to_string(time.tm_mday);
	stamp += string(2 - append.length(), '0') + append + dateDelimiter;
	append = to_string(time.tm_mon + 1);
	stamp += string(2 - append.length(), '0') + append + dateDelimiter + to_string(time.tm_year - 100) + separator;
	append = to_string(time.tm_hour);
	stamp += string(2 - append.length(), '0') + append + timeDelimiter;
	append = to_string(time.tm_min);
	stamp += string(2 - append.length(), '0') + append + timeDelimiter;
	append = to_string(time.tm_sec);
	stamp += string(2 - append.length(), '0') + append + endDelimiter + separator;
	return stamp;
}
