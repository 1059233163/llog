#include <stdio.h>
#include "llog.h"

int main(int argc,char **argv)
{
    printf("hello log\n");
    log_t *ld=log_open("mylog.txt",0);
    lprintf(ld,DEBUG,"testdata:%d\n",1234);
    lprintf(ld,INFO,"testdata:%d\n",1234);
    lprintf(ld,WARN,"testdata:%d\n",1234);
    lprintf(ld,ERROR,"testdata:%d\n",1234);
    lprintf(ld,FATAL,"testdata:%d\n",1234);
    log_close(ld);
    return 0;
}
