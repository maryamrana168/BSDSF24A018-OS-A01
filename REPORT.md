
### 1. Makefile Linking Rule

The rule `$(TARGET): $(OBJECTS)` tells `make` that the final executable
`$(TARGET)` depends on all object files listed in `$(OBJECTS)`.

When the object files are ready, the linker combines them to create the
final executable.

This differs from a rule that links against a library because a library
contains precompiled code that is linked using options such as `-l<library>`
and `-L<directory>`. In this project, the executable is directly linked
from the project's own object files.

### 2. Git Tags

A Git tag is a name that points to a specific commit in the Git history.

Tags are useful for marking important versions of a project, such as
releases. For example, `v0.1.1-multifile` identifies the commit containing
the multi-file build version of the project.

A simple tag is just a reference to a commit. An annotated tag also stores
additional information such as the tagger, date, and a message.


### 3. GitHub Releases

A GitHub Release packages a particular version of a project and makes it
available to users along with release notes and downloadable files.

The release is associated with a Git tag, which identifies the exact
version of the source code.

Attaching the compiled `client` executable is significant because users
can download and run the compiled program without having to compile the
source code themselves.

### 4. Static Library Build
                                                                   
In Part 2, the Makefile directly compiled all the source files together to create the executable. The source files were compiled using a command similar to:

gcc -Wall -Wextra -Iinclude main.c mystrfunctions.c myfilefunctions.c -o ../bin/client



In Part 3, the Makefile was changed to use separate object files and a static library.

The important variables are:

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
TARGET = bin/client_static
OBJDIR = obj
LIBDIR = lib
LIB = $(LIBDIR)/libmyutils.a
MAIN_OBJ = $(OBJDIR)/main.o
LIB_OBJS = $(OBJDIR)/mystrfunctions.o $(OBJDIR)/myfilefunctions.o


The rules first compile each .c file into an .o object file. The utility object files are then combined into libmyutils.a using ar. Finally, main.o is linked with the static library using:

$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJ) -L$(LIBDIR) -lmyutils

Therefore, Part 3 separates compilation, library creation, and final linking, making the project more modular and scalable.


###  5. Purpose of ar and ranlib

The ar command is used to create and manage static libraries. In this project, the command:

ar rcs lib/libmyutils.a obj/mystrfunctions.o obj/myfilefunctions.o

creates the static library libmyutils.a and places the two utility object files inside it.

The options mean:

r — insert or replace object files in the archive.
c — create the archive if it does not already exist.
s — create/update the symbol index.

ranlib is traditionally used after creating a static library to generate or update the archive's symbol index. This index allows the linker to find required symbols efficiently.

Because we used:

ar rcs

the s option already creates the symbol index, so running ranlib separately is normally unnecessary.

###  6. Using nm to Understand Static Linking

You should see something similar to:

000000000000.... T mystrlen

The exact address may be different.

The T symbol indicates that mystrlen is defined in the executable's text/code section.

This shows that the function from the static library has been included in the final executable during static linking. The linker takes the required object code from libmyutils.a and places it into client_static.

Therefore, after static linking, functions such as mystrlen are part of the executable itself rather than requiring a separate library file at runtime.



