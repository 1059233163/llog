#include <stdio.h>
#include "llog.h"

#define PRT(tag,fmt,arg...) printf("%s-"fmt,tag,##arg)
#define LLOGD(tag,fmt,arg...) lprintf(ld,DEBUG,"(%s):"fmt,tag,##arg);
#define LLOGI(tag,fmt,arg...) lprintf(ld,INFO ,"(%s):"fmt,tag,##arg);
#define LLOGW(tag,fmt,arg...) lprintf(ld,WARN ,"(%s):"fmt,tag,##arg);
#define LLOGE(tag,fmt,arg...) lprintf(ld,ERROR,"(%s):"fmt,tag,##arg);
#define LLOGF(tag,fmt,arg...) lprintf(ld,FATAL,"(%s):"fmt,tag,##arg);

#define TAG "MYLOG"

int main(int argc,char **argv)
{
    PRT(TAG,"hello log: %s\n","hhhhello");
    log_t *ld=log_open("mylog.txt",0);
    LLOGD(TAG,"testdata:%d\n",1234);
    LLOGI(TAG,"testdata:%d\n",1234);
    LLOGW(TAG,"testdata:%d\n",1234);
    LLOGE(TAG,"testdata:%d\n",1234);
    LLOGF(TAG,"testdata:%d\n",1234);
    log_close(ld);
    return 0;
}
