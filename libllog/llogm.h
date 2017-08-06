/*
*author:zhaghw
*date:2017-08-06
*usages:
*1.Log does not print on terminal by default,create "/tmp/showlog" if you want to do.
*2.Log does not print on terminal by default,create "/tmp/showlog" if you want to do.
*3.Log will not output if you create "/tmp/nolog".
*    eg 1:/tmp/logfilter
*    MYLOG MYLOG_1 ~MYLOG_2
*    eg 2:/tmp/logfilter
*    MYLOG
*    MYLOG_1
*    ~MYLOG_2
*3.Log does not output if TAG started by '~' and is not exist in "/tmp/logfilter".
*/
#ifndef __LLOGM_H
#define __LLOGM_H

#include "llog.h"

extern log_t* llogFd;
extern char defaultTag[LOG_FILTER_SIZE];

#define LOG_MAX_SZIE 1024*1024
#define LOG_MANAGE_PERIOD 100000

#define LLOGD(tag,fmt,arg...) lprintf(llogFd,DEBUG,tag==NULL?defaultTag:tag,"[%s-%d]: "fmt,__func__,__LINE__,##arg);
#define LLOGI(tag,fmt,arg...) lprintf(llogFd,INFO ,tag==NULL?defaultTag:tag,"[%s-%d]: "fmt,__func__,__LINE__,##arg);
#define LLOGW(tag,fmt,arg...) lprintf(llogFd,WARN ,tag==NULL?defaultTag:tag,"[%s-%d]: "fmt,__func__,__LINE__,##arg);
#define LLOGE(tag,fmt,arg...) lprintf(llogFd,ERROR,tag==NULL?defaultTag:tag,"[%s-%d]: "fmt,__func__,__LINE__,##arg);
#define LLOGF(tag,fmt,arg...) lprintf(llogFd,FATAL,tag==NULL?defaultTag:tag,"[%s-%d]: "fmt,__func__,__LINE__,##arg);

typedef enum{
    LogManageType_SIZE,
}LogManageType;

#ifdef __cplusplus
extern "C"{
#endif

log_t *llogmStart(const char *fname,int flags,LogManageType type);
void llogmSetDefaultTag(const char *tag);
void llogmStop();
int isllogmRunning();
void llogmJoin();

#ifdef __cplusplus
}
#endif

#endif
