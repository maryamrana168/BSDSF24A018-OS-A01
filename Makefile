CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = bin/client_static

OBJDIR = obj
LIBDIR = lib

LIB = $(LIBDIR)/libmyutils.a

MAIN_OBJ = $(OBJDIR)/main.o
LIB_OBJS = $(OBJDIR)/mystrfunctions.o $(OBJDIR)/myfilefunctions.o

all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJ) -L$(LIBDIR) -lmyutils

$(LIB): $(LIB_OBJS)
	ar rcs $(LIB) $(LIB_OBJS)

$(OBJDIR)/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o $(OBJDIR)/main.o

$(OBJDIR)/mystrfunctions.o: src/mystrfunctions.c
	$(CC) $(CFLAGS) -c src/mystrfunctions.c -o $(OBJDIR)/mystrfunctions.o

$(OBJDIR)/myfilefunctions.o: src/myfilefunctions.c
	$(CC) $(CFLAGS) -c src/myfilefunctions.c -o $(OBJDIR)/myfilefunctions.o

clean:
	rm -f $(OBJDIR)/*.o $(LIB) $(TARGET)


