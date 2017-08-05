#include "llogm.h"
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

log_t* llogFd=NULL;
static char llogName[64];
static pthread_t llogmTid;
static int stopCmd=0;
static int runFlag=0;
static int llogNum=1;

static void *llogManage(void *arg)
{
    runFlag=1;    
    struct stat fileStat;
    memset(&fileStat,0x00,sizeof(struct stat));
    while(0==stopCmd){
        if(0==stat(llogName,&fileStat)){            
            if(fileStat.st_size>LOG_MAX_SZIE){
                printf("[%s-%d]:%s too large ,recreate times:%d\n",__func__,__LINE__,llogName,llogNum);
                sem_wait(&llogFd->sem);
                close(llogFd->fd);
                remove(llogName);
                llogFd->fd=open(llogName,O_WRONLY|O_CREAT|O_NOCTTY|O_TRUNC,0666);
                if(-1==llogFd->fd){
                    fprintf(stderr, "[%s-%d]:LOG: Opening log file %s: %s",__func__,__LINE__, llogName, strerror(errno));
                    log_close(llogFd);
                    break;
                }
                llogNum++;                
                sem_post(&llogFd->sem);
                LLOGI(LOG_FILTER_DEFAULT,"***************llogNum:%d***************",llogNum);
            }
        }
        usleep(LOG_MANAGE_PERIOD);
    }    
    if(NULL!=llogFd){
        log_close(llogFd);
        llogFd=NULL;
    }
    printf("[%s-%d]:llogManage exit,llogName:%s\n",__func__,__LINE__,llogName);
    llogNum=0;
    runFlag=0;
}

log_t *llogmStart(const char *fname,int flags,LogManageType type)
{
    memset(llogName,0,sizeof(llogName));
    strcpy(llogName,fname);
    llogFd=log_open(llogName,flags);
    if(NULL==llogFd){
        return llogFd;
    }    
    LLOGI(LOG_FILTER_DEFAULT,"***************llogNum:%d***************",llogNum);
    int ret=0;
    switch(type){
        case LogManageType_SIZE:
            ret=pthread_create(&llogmTid,NULL,llogManage,NULL);
            break;
    }
    if(ret){
        log_close(llogFd);
        llogFd=NULL;
        return llogFd;
    }    
    return llogFd;
}

void llogmStop()
{
    stopCmd=1;    
}

int isllogmRunning()
{
    return runFlag;
}

void llogmJoin()
{
    pthread_join(llogmTid,NULL);
}
