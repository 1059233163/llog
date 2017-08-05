#include <stdio.h>
#include "llogm.h"
#include <signal.h>
#include <pthread.h>

#define PRT(tag,fmt,arg...) printf("%s-"fmt,tag,##arg)

#define TAG "MYLOG"

int abortSignal=0;

void termSignalHandler(int sig)
{
    PRT(TAG,"termSignalHandler\n");
    llogmStop();
    abortSignal=1;
}

int main(int argc,char **argv)
{
    signal(SIGINT,termSignalHandler);
    PRT(TAG,"main thread start\n");
    llogmStart("mylog.txt",0);
    int num=0;
    while(0==abortSignal){
        LLOGD(TAG,"testdata:%d\n",1234);
        LLOGI(TAG,"testdata:%d\n",1234);
        LLOGW(TAG,"testdata:%d\n",1234);
        LLOGE(TAG,"testdata:%d\n",1234);
        LLOGF(TAG,"testdata:%d\n",1234);
        num++;
        LLOGI(TAG,"num=%d",num);
        usleep(1000);
    }
    llogmJoin();
    PRT(TAG,"main thread exit\n");
    return 0;
}
