#include <stdio.h>
#include "llogm.h"
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

#define PRT(tag,fmt,arg...) printf("%s-"fmt,tag,##arg)

#define TAG "MYLOG"
#define TAG_1 "MYLOG_1"
#define TAG_2 "MYLOG_2"
#define TAG_3 "MYLOG_3"
#define TAG_4 "~MYLOG_4"

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
    llogmStart("./mylog.txt",0,LogManageType_SIZE);
    llogmSetDefaultTag(argv[0]);    
    int num=0;
    while(0==abortSignal){
        LLOGD(TAG,"testdata:%d\n",1234);
        LLOGI(TAG,"testdata:%d\n",1234);
        LLOGW(TAG,"testdata:%d\n",1234);
        LLOGE(TAG,"testdata:%d\n",1234);
        LLOGF(TAG,"testdata:%d\n",1234);

        LLOGD(TAG_1,"testdata:%d\n",1234);
        LLOGI(TAG_1,"testdata:%d\n",1234);
        LLOGW(TAG_1,"testdata:%d\n",1234);
        LLOGE(TAG_1,"testdata:%d\n",1234);
        LLOGF(TAG_1,"testdata:%d\n",1234);

        LLOGD(TAG_2,"testdata:%d\n",1234);
        LLOGI(TAG_2,"testdata:%d\n",1234);
        LLOGW(TAG_2,"testdata:%d\n",1234);
        LLOGE(TAG_2,"testdata:%d\n",1234);
        LLOGF(TAG_2,"testdata:%d\n",1234);

        LLOGD(TAG_3,"testdata:%d\n",1234);
        LLOGI(TAG_3,"testdata:%d\n",1234);
        LLOGW(TAG_3,"testdata:%d\n",1234);
        LLOGE(TAG_3,"testdata:%d\n",1234);
        LLOGF(TAG_3,"testdata:%d\n",1234);

        LLOGD(TAG_4,"testdata:%d\n",1234);
        LLOGI(TAG_4,"testdata:%d\n",1234);
        LLOGW(TAG_4,"testdata:%d\n",1234);
        LLOGE(TAG_4,"testdata:%d\n",1234);
        LLOGF(TAG_4,"testdata:%d\n",1234);

        LLOGD(NULL,"testdata:%d\n",1234);
        LLOGI(NULL,"testdata:%d\n",1234);
        LLOGW(NULL,"testdata:%d\n",1234);
        LLOGE(NULL,"testdata:%d\n",1234);
        LLOGF(NULL,"testdata:%d\n",1234);
        num++;
        LLOGI(TAG,"num=%d",num);
        usleep(1000);
    }
    llogmJoin();
    PRT(TAG,"main thread exit\n");
    return 0;
}
