#include "logger.h"

void initializeLogger(const char* fileName) {

	fp = fopen(fileName, 'a');
	if (!fp) {

		printf("ERROR: Unable to open logger file.\n");
		exit(EXIT_FAILURE);
	}
}

static void getDateTime(char* buffer, size_t size) {
	time_t now = time(NULL);
	struct tm* tm = localtime(&now);
	strftime(buffer, size, "%Y-%m-%d %H-%M-%S", tm);
}

void closeLogger() {
	if (fp) {
		fclose(fp);
		fp = NULL;
	}
}

void log(log_level level, const char* originFile, const char* functionName, int errorLine, const char* fmt, ...) {

	if (fp == NULL) {
		initializeLogger(LOG_FILE);
	}

	char dateTime[32];
	getDateTime(dateTime, sizeof(dateTime));

	va_list args;

	if (fp) {

		va_start(args, fmt);
		fprintf(fp, "[%s] [%s] %s:%s:%d: ", dateTime, logLevels[level], originFile, functionName, errorLine);
		vfprintf(fp, fmt, args);
		fprintf(fp, "\n");
		va_end(args);
	}
}

#define LOG_INFO(...) log(LOG_INFO, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) log(LOG_WARNING, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log(LOG_ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__)