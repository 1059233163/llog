#dirs
INC_DIR=-I./ 
SRC=$(wildcard ./*.c) 
OBJS=$(SRC:%.c=%.o)
OBJD=$(SRC:%.c=%.d)
#compile
CC = gcc
LD = ld
AR = ar
CFLAGS=-Wall -lpthread
TARGET=llog

all:$(TARGET)
	@echo $(OBJS)

$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $@

$(OBJS):%.o:%.c
	$(CC) $(INC_DIR) -c $< -o $@

.PHONY:clean
clean:
	rm -rf $(OBJS) $(OBJD) 

