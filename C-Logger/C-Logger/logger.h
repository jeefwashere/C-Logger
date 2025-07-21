#ifndef logger.h
#define logger.h

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATE_TIME_LIMIT 11
#define LOG_LEVEL_LIMIT 2
#define LOG_FILE "log.txt"

static FILE* fp = NULL;

static const char* logLevels[] = { "INFO", "WARNING", "ERROR" };

typedef enum {
	LOG_INFO = 0,
	LOG_WARNING,
	LOG_ERROR
}log_level;

#endif // !"logger.h"
