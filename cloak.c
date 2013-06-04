/*
 * cloak.c
 * Ce module permet d'atribuer une vhost simple
 * Exemple "@internet"
 * Codé par GHOSTnew
 */


#include "config.h"
#include "struct.h"
#include "common.h"
#include "sys.h"
#include "numeric.h"
#include "msg.h"
#include "channel.h"
#include <time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <io.h>
#endif
#include <fcntl.h>
#include "h.h"
#ifdef _WIN32
#include "version.h"
#endif

static char cloak_checksum[64];

#undef KEY1
#undef KEY2
#undef KEY3
#define KEY1 cloak_key1
#define KEY2 cloak_key2
#define KEY3 cloak_key3

DLLFUNC char *hidehost(char *host);
DLLFUNC char *cloakcsum();

static inline unsigned int downsample(char *i);

Callback *cloak = NULL, *cloak_csum = NULL;

ModuleHeader MOD_HEADER(cloak)
  = {
  "cloak",
  "v1.0",
  "Simply Cloak by GHOSTnew",
  "3.2-b8-1",
  NULL
  };
DLLFUNC int MOD_TEST(cloak)(ModuleInfo *modinfo)
{
	cloak = CallbackAddPCharEx(modinfo->handle, CALLBACKTYPE_CLOAK, hidehost);
	if (!cloak)
	{
		config_error("cloak: Error while trying to install cloaking callback!");
		return MOD_FAILED;
	}
	cloak_csum = CallbackAddPCharEx(modinfo->handle, CALLBACKTYPE_CLOAKKEYCSUM, cloakcsum);
	if (!cloak_csum)
	{
		config_error("cloak: Error while trying to install cloaking checksum callback!");
		return MOD_FAILED;
	}
	return MOD_SUCCESS;
}

DLLFUNC int MOD_INIT(cloak)(ModuleInfo *modinfo)
{
	MARK_AS_OFFICIAL_MODULE(modinfo);
	return MOD_SUCCESS;
}

DLLFUNC int MOD_LOAD(cloak)(int module_load)
{
	return MOD_SUCCESS;
}

DLLFUNC int MOD_UNLOAD(cloak)(int module_unload)
{
	return MOD_SUCCESS;
}
/*
static int check_badrandomness(char *key)
{
char gotlowcase=0, gotupcase=0, gotdigit=0;
char *p;
	for (p=key; *p; p++)
		if (islower(*p))
			gotlowcase = 1;
		else if (isupper(*p))
			gotupcase = 1;
		else if (isdigit(*p))
			gotdigit = 1;

	if (gotlowcase && gotupcase && gotdigit)
		return 0;
	return 1;
}*/

DLLFUNC char *hidehost(char *host)
{
        //char *p;
        static char result[512];
        ircsprintf(result, "internet");
	return result;
}

DLLFUNC char *cloakcsum()
{
	return cloak_checksum;
}
