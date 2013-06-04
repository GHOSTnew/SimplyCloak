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

DLLFUNC char *hidehost(char *host);
DLLFUNC char *cloakcsum();

static inline unsigned int downsample(char *i);

Callback *cloak = NULL, *cloak_csum = NULL;

ModuleHeader MOD_HEADER(cloak)
  = {
  "cloak",
  "v1.0.1",
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


DLLFUNC char *hidehost(char *host)
{
        static char result[512];
        ircsprintf(result, "internet");
	return result;
}

DLLFUNC char *cloakcsum()
{
	return cloak_checksum;
}
