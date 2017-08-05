#include "llog.h"
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <malloc.h>

static char* last_char_is(const char *s, int c)
{
    char *sret;
    if(!s){
        return NULL;
    }
    sret=(char *)s+strlen(s)-1;
    if(sret>=s&&*sret==c){
        return sret;
    }
    else{
        return NULL;
    }
}

static void chomp(char *s)
{
    char *lc=last_char_is(s,'\n');
    if(lc){
        *lc=0;
    }
}

int lprintf(log_t *log, unsigned int level, char *fmt, ...)
{
    int fd;
    int rc;
    va_list ap;
    time_t now;
    char date[32] = {0};
    static char line[LOGLINE_MAX];
    int cnt;
    static char *levels[6] = { "[(bad)] ", "[debug] ", "[info]  ", "[warn]  ", "[error] ", "[fatal] " };
    if(!log){
        return -1;
    }    
    if(!(log->flags&LOG_DEBUG)&&level==DEBUG){
        return 0;
    }
    fd = log->fd;    
    if(!(log->flags&LOG_NODATE)){
        now = time(NULL);
        strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S ", localtime(&now));
    }

//    char threadnum[64];
//    if(!(log->flags & LOG_NOTID)){
//        sprintf(threadnum, "(TID:%lu) ", pthread_self());
//    }
//    cnt = snprintf(line, sizeof(line), "%s%s%s: ", log->flags & LOG_NODATE ? "": date,
//                   log->flags & LOG_NOLVL ? "" : (level > FATAL ? levels[0]: levels[level]),log->flags & LOG_NOTID ? "" : threadnum);

    cnt = snprintf(line, sizeof(line), "%s%s: ", log->flags & LOG_NODATE ? "": date,
                   log->flags & LOG_NOLVL ? "" : (level > FATAL ? levels[0]: levels[level]));
    va_start(ap, fmt);    
    vsnprintf(line + cnt, sizeof(line) - cnt, fmt, ap);
    va_end(ap);    
    line[sizeof(line)-1]='\0';
    if(!(log->flags&LOG_NOLF)){
        chomp(line);
        strcpy(line+strlen(line),"\n");
    }
    sem_wait(&log->sem);
    rc=write(fd, line, strlen(line));
    sem_post(&log->sem);

    if(!access(LOG_DISABLE_FILE,0)){    
        printf("%s",line);
    }

    if(!rc){
        errno = 0;
    }
    return rc;
}

log_t *log_open(char *fname, int flags)
{
    log_t *log=malloc(sizeof(log_t));
    if(!log){
        fprintf(stderr, "LOG: Unable to malloc()");
        goto log_open_a;
    }
    log->flags=flags;
    if(!strcmp(fname, "-")){
        log->fd = 2;
    }
    else{
        log->fd=open(fname,O_WRONLY|O_CREAT|O_NOCTTY|(flags&LOG_TRUNC?O_TRUNC:O_APPEND),0666);
    }
    if(log->fd==-1){
        fprintf(stderr, "LOG: Opening logfile %s: %s", fname, strerror(errno));
        goto log_open_b;
    }
    write(log->fd,"\n",1);
    if(sem_init(&log->sem,0,1)==-1){
        fprintf(stderr, "LOG: Could not initialize log semaphore.");
        goto log_open_c;
    }
    return log;

    log_open_c: close(log->fd);
    log_open_b: free(log);
    log_open_a: return NULL;
}

void log_close(log_t *log)
{
    sem_wait(&log->sem);
    sem_destroy(&log->sem);
    close(log->fd);
    free(log);
    return;
}