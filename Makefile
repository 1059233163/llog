#dirs
INC_DIR=-I./ -I./libllog
SRC=$(wildcard ./*.c) $(wildcard ./libllog/*.c)
SRCXX=$(wildcard ./*.cpp)
OBJS=$(SRC:%.c=%.o)
OBJD=$(SRC:%.c=%.d)
OBJSXX=$(SRCXX:%.cpp=%.o)	
#compile
CC = gcc
CPP= g++
LD = ld
AR = ar
CFLAGS=-Wall -lpthread
TARGET=llog

all:$(TARGET)
	@echo $(OBJS)

$(TARGET):$(OBJS) $(OBJSXX)
	$(CC) $(OBJS) $(OBJSXX) $(CFLAGS) $(LIBS) -o $@

$(OBJS):%.o:%.c
	$(CC) $(INC_DIR) -c $< -o $@

$(OBJSXX):%.o:%.cpp
	$(CPP) $(INC_DIR) -c $< -o $@

.PHONY:clean
clean:
	rm -f $(OBJS) $(OBJD) $(TARGET)

