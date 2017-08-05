#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <semaphore.h>

#define LOGLINE_MAX 1024

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
#define LOG_STDERR  1<<5
//#define LOG_NOTID   1<<6 //No thread id
#define	LOG_FILE_PATH   "./%s.log"
#define LOG_DISABLE_FILE "/tmp/showlog"
#define LOG_MAX	4096000

typedef struct logs{
	int fd;
	sem_t sem;
	int flags;
}log_t;

int lprintf(log_t *log, unsigned int level, char *fmt, ...);
log_t *log_open(char *fname, int flags);
void log_close(log_t *log);
void error_log(char* s,char *filename,int row_num);
int CreatLogName(void);
void *LogManage(void *arg);
#endif
