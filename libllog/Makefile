#dirs
INC_DIR=-I./
SRC=$(wildcard ./*.c) 
OBJS=$(SRC:%.c=%.o)
#compile
CC = gcc
CPP= g++
LD = ld
AR = ar
CFLAGS=-Wall
LIBS=-lpthread
TARGET=libllog.so

all:$(TARGET)
	@echo $(OBJS)

$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(LIBS) -shared -o $@

$(OBJS):%.o:%.c
	$(CC) $(INC_DIR) $(CFLAGS) $< -fPIC -c -o $@

.PHONY:clean
clean:
	rm -f $(OBJS) $(TARGET)

