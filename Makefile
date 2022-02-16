CC = gcc
OBJCSS = server3.c
OBJCS = client3.c

CFLAGS = -g -Wall
#setup for system
nLIBS = 

all: server3 client3

server3: $(OBJCSS)
	$(CC) $(CFLAGS) -o $@ $(OBJCSS) $(LIBS)
client3: $(OBJCS)
	$(CC) $(CFLAGS) -o $@ $(OBJCS) $(LIBS)

clean:
	rm server3 client3