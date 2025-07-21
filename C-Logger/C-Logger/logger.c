/*

===============================================================================
					Welcome to Simple C Logger v1.0.0!

						Created by: Jeff Tieng
===============================================================================
*/

#include "logger.h"

/*
NAME:		initializeLogger

DESC:		Creates the logging file to be used

PARAMS:		const char* fileName :	File name parameter
*/
void initializeLogger(const char* fileName) {

	fp = fopen(fileName, 'a');
	if (!fp) {

		printf("ERROR: Unable to open logger file.\n");
		exit(EXIT_FAILURE);
	}
}

/*
NAME:		getDateTime

DESC:		Creates the timestamp used for logging info

PARAMS:		char* buffer :	Date time string array
			size_t size	 :	Size of the array being passed in
*/
static void getDateTime(char* buffer, size_t size) {
	time_t now = time(NULL);
	struct tm* tm = localtime(&now);
	strftime(buffer, size, "%Y-%m-%d %H-%M-%S", tm);
}

/*
NAME:		closeLogger

DESC:		Safely closes the logger file.
*/
void closeLogger() {
	if (fp) {
		fclose(fp);
		fp = NULL;
	}
}

/*
NAME:		log

DESC:		Used to write information onto the logging file. It comes with the date, level of importance, the file, the function, and the line where the log function is called.

PARAMS:		log_level level				:	Level of importance for logged info
			const char* originFile		:	The origin file from which the function is being called
			const char* functionName	:	The function where the log function is called
			int errorLine				:	The line of code where the log function is written
			const char* fmt				:	Used to format output for variadic arguments
*/
void log(log_level level, const char* originFile, const char* functionName, int errorLine, const char* fmt, ...) {

	if (fp == NULL) {
		initializeLogger(LOG_FILE); // Feel free to change the name constant to any file name.
	}

	char dateTime[32];
	getDateTime(dateTime, sizeof(dateTime));

	va_list args;

	if (fp) {
		va_start(args, fmt);

		if (level < 0 || level >= LOG_LEVEL_LIMIT) {
			fprintf(fp, "[%s] [UNKNOWN] %s:%s:%d: ", dateTime, originFile, functionName, errorLine);
		} 
		else {
			fprintf(fp, "[%s] [%s] %s:%s:%d: ", dateTime, logLevels[level], originFile, functionName, errorLine);
		}

		vfprintf(fp, fmt, args);
		fprintf(fp, "\n");
		va_end(args);
	}
}

#define LOG_INFO(...) log(LOG_INFO, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) log(LOG_WARNING, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log(LOG_ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__)