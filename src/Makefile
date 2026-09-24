CC = gcc
CFLAGS = -Wall -Wextra -I../include

TARGET = ../bin/client

SOURCES = main.c mystrfunctions.c myfilefunctions.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: all
	$(TARGET)

clean:
	rm -f $(TARGET)



