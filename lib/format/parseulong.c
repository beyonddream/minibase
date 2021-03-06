#include <format.h>

char* parseulong(char* buf, unsigned long* np)
{
	unsigned long n = 0;
	int d;
	char* p;

	for(p = buf; *p; p++)
		if(*p >= '0' && (d = *p - '0') < 10)
			n = n*10 + d;
		else
			break;

	if(p == buf)
		return NULL;

	*np = n;
	return p;
}
