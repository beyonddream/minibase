#include <sys/open.h>
#include <sys/fstat.h>
#include <sys/mmap.h>
#include <sys/close.h>

#include <string.h>
#include <format.h>
#include <fail.h>

#include "date.h"

static char zonebase[] = "/usr/share/zoneinfo";

/* Zone name abbreviation: 10:00 PDT when tzdata only has US/Pacific.

   There are two cases with different treatment: zones that have
   a fixed UTC offset (e.g. EST, always at UTC-4) and zones that
   have DST or other variations (e.g. ET, which may be -4 or -5).

   https://en.wikipedia.org/wiki/List_of_time_zone_abbreviations */

#define ZNML 6

struct zoneabbr {
	char name[ZNML];
	short offset;
} fixedzones[] = {
#define UTC(hh, mm) (0 hh*4 + mm/15)
	{ "GMT",  UTC( +0,00) }, /* Greenwich Mean Time */
	{ "UTC",  UTC( +0,00) }, /* Coordinated Universal Time */
	/* Europe */
	{ "WEST", UTC( +1,00) }, /* Western European Summer Time */
	{ "WET",  UTC( +0,00) }, /* Western European Time */
	{ "WIT",  UTC( +7,00) }, /* Western Indonesian Time */
	{ "WST",  UTC( +8,00) }, /* Western Standard Time */
	{ "CEST", UTC( +2,00) }, /* Central European Summer Time */
	{ "CET",  UTC( +1,00) }, /* Central European Time */
	{ "EEST", UTC( +3,00) }, /* Eastern European Summer Time */
	{ "EET",  UTC( +2,00) }, /* Eastern European Time */
	{ "MET",  UTC( +1,00) }, /* Middle European Time = CET */
	{ "MEST", UTC( +2,00) }, /* Middle European Summer Time = CEST */
	/* North America */
	{ "ADT",  UTC( -3,00) },  /* Atlantic Daylight Time */
	{ "AST",  UTC( -4,00) },  /* Atlantic Standard Time */
	{ "AKDT", UTC( -8,00) },  /* Alaska Daylight Time */
	{ "AKST", UTC( -9,00) },  /* Alaska Standard Time */
	{ "CDT",  UTC( -5,00) },  /* Central Daylight Time */
	{ "CST",  UTC( -6,00) },  /* Central Standard Time */
	{ "EDT",  UTC( -4,00) },  /* Eastern Daylight Time */
	{ "EST",  UTC( -5,00) },  /* Eastern Standard Time */
	{ "PDT",  UTC( -7,00) },  /* Pacific Daylight Time */
	{ "PST",  UTC( -8,00) },  /* Pacific Standard Time */
	{ "MDT",  UTC( -6,00) },  /* Mountain Daylight Time */
	{ "MST",  UTC( -7,00) },  /* Mountain Standard Time */
	{ "HADT", UTC( -9,00) },  /* Hawaii-Aleutian Daylight Time */
	{ "HAST", UTC(-10,00) },  /* Hawaii-Aleutian Standard Time */
	/* Australia, NZ & Pacific */
	{ "ACDT", UTC(+10,30) }, /* Australian Central Daylight Savings Time */
	{ "ACST", UTC( +9,30) }, /* Australian Central Standard Time */
	{ "AEDT", UTC(+11,00) }, /* Australian Eastern Daylight Savings Time */
	{ "AEST", UTC(+10,00) }, /* Australian Eastern Standard Time */
	{ "AWST", UTC( +8,00) }, /* Australian Western Standard Time */
	{ "NZDT", UTC(+13,00) }, /* New Zealand Daylight Time */
	{ "NZST", UTC(+12,00) }, /* New Zealand Standard Time */
	/* Asia */
	{ "ICT",  UTC( +7,00) }, /* Indochina Time */
	{ "CT",   UTC( +8,00) }, /* China time */
	{ "AST",  UTC( +3,00) }, /* Arabia Standard Time */
	{ "KST",  UTC( +9,00) }, /* Korea Standard Time */
	{ "HKT",  UTC( +8,00) }, /* Hong Kong Time */
	{ "JST",  UTC( +9,00) }, /* Japan Standard Time */
	{ "SGT",  UTC( +8,00) }, /* Singapore Time */
	{ "THA",  UTC( +7,00) }, /* Thailand Standard Time */
	{ "SST",  UTC( +8,00) }, /* Singapore Standard Time */
	{ "TRT",  UTC( +3,00) }, /* Turkey Time */
	/* South America */
	{ "ART",  UTC( -3,00) }, /* Argentina Time */
	{ "AMST", UTC( -3,00) }, /* Amazon Summer Time */
	{ "AMT",  UTC( -4,00) }, /* Amazon Time */
	{ "BRST", UTC( -2,00) }, /* Brasilia Summer Time */
	{ "BRT",  UTC( -3,00) }, /* Brasilia Time */
	{ "PET",  UTC( -5,00) }, /* Peru Time */
	{ "ART",  UTC( -3,00) }, /* Argentina Time */
	{ "UYST", UTC( -2,00) }, /* Uruguay Summer Time */
	{ "UYT",  UTC( -3,00) }, /* Uruguay Standard Time */
	{ "GFT",  UTC( -3,00) }, /* French Guiana Time */
	{ "COST", UTC( -4,00) }, /* Colombia Summer Time */
	{ "COT",  UTC( -5,00) }, /* Colombia Time */
	{ "VET",  UTC( -4,00) }, /* Venezuelan Standard Time */
	/* Africa */
	{ "WAST", UTC( +2,00) }, /* West Africa Summer Time */
	{ "WAT",  UTC( +1,00) }, /* West Africa Time */
	{ "CAT",  UTC( +2,00) }, /* Central Africa Time */
	{ "SAST", UTC( +2,00) }, /* South African Standard Time */
#undef UTC
	{ "", 0 }
};

void maybe_utc_zone(struct zonefile* zf, const char* zone)
{
	struct zoneabbr* p;

	if(strlen(zone) >= ZNML)
		return;

	for(p = fixedzones; p->name[0]; p++)
		if(!strncmp(p->name, zone, 8))
			break;

	if(!p->name[0])
		return;

	zf->offset = p->offset*15*60;
	zf->fixed = 1;
}

void link_zone_data(struct zonefile* dst, struct zonefile* src)
{
	dst->name = src->name;
	dst->data = src->data;
	dst->len = src->len;
}

static void open_zone_file(struct zonefile* zf, const char* name)
{
	long fd = xchk(sysopen(name, O_RDONLY), "open", name);

	struct stat st;
	xchk(sysfstat(fd, &st), "stat", name);

	if(st.st_size >= 0xFFFFFFFF)
		fail("zone file too large:", name, 0);

	int prot = PROT_READ;
	int flags = MAP_SHARED;
	long addr = sysmmap(NULL, st.st_size, prot, flags, fd, 0);

	if(MMAPERROR(addr))
		fail("mmap", name, addr);

	zf->name = name;
	zf->data = (void*)addr;
	zf->len = st.st_size;

	sysclose(fd);
}

void open_named_zone(struct zonefile* zf, const char* zone)
{
	int baselen = strlen(zonebase);
	int zonelen = strlen(zone);
	int len = baselen + 1 + zonelen + 2;

	char buf[len];
	char* end = buf + sizeof(buf) - 1;
	char* p = buf;

	p = fmtstrn(p, end, zonebase, baselen);
	p = fmtstrn(p, end, "/", 1);
	p = fmtstrn(p, end, zone, zonelen);
	*p = '\0';

	/* TODO: move path out of here, and keep it in zf->name */

	open_zone_file(zf, buf);
}

void open_default_zone(struct zonefile* zf)
{
	open_zone_file(zf, "/etc/localtime");
}
