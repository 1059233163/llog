#include "llog.h"

extern log_t* llogFd;

#define LOG_MAX_SZIE 1024*1024
#define LOG_MANAGE_PERIOD 100000

#define LLOGD(tag,fmt,arg...) lprintf(llogFd,DEBUG,"(%s):"fmt,tag,##arg);
#define LLOGI(tag,fmt,arg...) lprintf(llogFd,INFO ,"(%s):"fmt,tag,##arg);
#define LLOGW(tag,fmt,arg...) lprintf(llogFd,WARN ,"(%s):"fmt,tag,##arg);
#define LLOGE(tag,fmt,arg...) lprintf(llogFd,ERROR,"(%s):"fmt,tag,##arg);
#define LLOGF(tag,fmt,arg...) lprintf(llogFd,FATAL,"(%s):"fmt,tag,##arg);

typedef enum{
    LogManageType_SIZE,
}LogManageType;

log_t *llogmStart(const char *fname,int flags,LogManageType type);
void llogmStop();
int isllogmRunning();
void llogmJoin();
