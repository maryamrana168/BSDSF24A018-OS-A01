CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
PICFLAGS = -fPIC

STATIC_TARGET = bin/client_static
DYNAMIC_TARGET = bin/client_dynamic

OBJDIR = obj
LIBDIR = lib

STATIC_LIB = $(LIBDIR)/libmyutils.a
DYNAMIC_LIB = $(LIBDIR)/libmyutils.so

MAIN_OBJ = $(OBJDIR)/main.o

LIB_OBJS = $(OBJDIR)/mystrfunctions.o $(OBJDIR)/myfilefunctions.o

all: $(STATIC_TARGET) $(DYNAMIC_TARGET)

$(STATIC_TARGET): $(MAIN_OBJ) $(STATIC_LIB)
	$(CC) $(CFLAGS) -o $(STATIC_TARGET) $(MAIN_OBJ) -L$(LIBDIR) -lmyutils

$(DYNAMIC_TARGET): $(MAIN_OBJ) $(DYNAMIC_LIB)
	$(CC) $(CFLAGS) -o $(DYNAMIC_TARGET) $(MAIN_OBJ) -L$(LIBDIR) -lmyutils

$(STATIC_LIB): $(LIB_OBJS)
	ar rcs $(STATIC_LIB) $(LIB_OBJS)

$(DYNAMIC_LIB): src/mystrfunctions.c src/myfilefunctions.c
	$(CC) $(CFLAGS) $(PICFLAGS) -shared src/mystrfunctions.c src/myfilefunctions.c -o $(DYNAMIC_LIB)

$(OBJDIR)/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o $(OBJDIR)/main.o

$(OBJDIR)/mystrfunctions.o: src/mystrfunctions.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c src/mystrfunctions.c -o $(OBJDIR)/mystrfunctions.o

$(OBJDIR)/myfilefunctions.o: src/myfilefunctions.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c src/myfilefunctions.c -o $(OBJDIR)/myfilefunctions.o

clean:
	rm -f $(OBJDIR)/*.o $(STATIC_LIB) $(DYNAMIC_LIB) $(STATIC_TARGET) $(DYNAMIC_TARGET)
