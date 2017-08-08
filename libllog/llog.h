#ifndef __LLOG_H
#define __LLOG_H

#include <stdio.h>
#include <semaphore.h>

#define LOGLINE_MAX 1024
#define LOG_FILTER_FILE "/tmp/logfilter"
#define LOG_SHOW_FLAG "/tmp/showlog"
#define LOG_NO_FLAG "/tmp/nolog"
#define LOG_FILTER_DEFAULT "Default"
#define LOG_FILTER_SIZE 64 //TAG MAX SIZE
#define LOG_NAME_MAXSIZE 64

#define DEBUG 1
#define INFO  2
#define WARN  3
#define ERROR 4
#define FATAL 5

#define LOG_TRUNC   1<<0 //trunc log file
#define LOG_NODATE  1<<1
#define LOG_NOLF    1<<2 //not turn to new line automatically
#define LOG_NOLVL   1<<3 //no level
#define LOG_DEBUG   1<<4 //enable debug
//#define LOG_STDERR  1<<5

typedef struct logs{
	int fd;
	sem_t sem;
	int flags;
        char name[LOG_NAME_MAXSIZE];
}log_t;

#ifdef __cplusplus
extern "C"{
#endif
int lprintf(log_t *log, unsigned int level, const char *tag, const char *fmt, ...);
log_t *log_open(char *fname, int flags);
void log_close(log_t *log);
void error_log(char* s,char *filename,int row_num);
#ifdef __cplusplus
}
#endif

#endif
