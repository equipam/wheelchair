CC = gcc
GG = g++
CFLAGS = -Wall -O -g
TARGET = ./app

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o:%.cpp
	$(GG) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$(TARGET):$(OBJS)
	$(GG) $(OBJS) -o $(TARGET) -Wl,-rpath=./ -L./ -lHPS3DSDK_aarch64_1-8-5 -lJetsonGPIO -lpthread
	chmod a+x $(TARGET)

clean:
	rm -rf *.o $(TARGET)
