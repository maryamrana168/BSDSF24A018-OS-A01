
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



### 7. Position-Independent Code (-fPIC) 

Position-Independent Code (PIC) is machine code that can execute correctly regardless of the memory address where it is loaded. The -fPIC compiler option tells GCC to generate position-independent code.

Shared libraries such as libmyutils.so can be loaded at different memory addresses by different programs. Therefore, their code cannot depend on fixed memory addresses. Using -fPIC allows the same shared-library code to be loaded and used by multiple programs without requiring the library to be modified for a particular memory location.

In this task, -fPIC was used when compiling the library source files:

gcc -Wall -Wextra -Iinclude -fPIC -c src/mystrfunctions.c
gcc -Wall -Wextra -Iinclude -fPIC -c src/myfilefunctions.c

The resulting position-independent code was then used to create lib/libmyutils.so.

### 8. Difference in file size between your static and dynamic clients

The static and dynamic clients may have different file sizes because of how the library code is included.

With static linking, the required library object code is copied into the executable during the linking process. Therefore, the executable contains its own copies of functions such as mystrlen, mystrcpy, mystrcat, mygrep, and wordCount.

With dynamic linking, the library code not copied into the executable. Instead, client_dynamic contains references to the functions and a dependency on libmyutils.so. The shared library is loaded separately by the dynamic loader when the program runs.

In this task, the measured sizes were approximately:

client_static   17K
client_dynamic  17K

Although the two executables were similar in size in this particular build, their contents and linking mechanisms are different. client_static contains the library's required code, while client_dynamic refers to libmyutils.so, which contains the actual implementations.

This difference is therefore not always visible as a large difference in the executable's file size, especially for a small library like libmyutils. The important distinction is where the library code resides and when it is loaded.

## 9. LD_LIBRARY_PATH environment variable  


LD_LIBRARY_PATH is an environment variable that specifies additional directories where the Linux dynamic loader should search for shared libraries.

When we initially ran:

./bin/client_dynamic

the program produced:

error while loading shared libraries: libmyutils.so:
cannot open shared object file: No such file or directory

This happened because libmyutils.so was located in the project's lib/ directory, which was not in the dynamic loader's default library search paths.

We therefore used:

export LD_LIBRARY_PATH=$PWD/lib

After setting this variable, the program successfully located and loaded libmyutils.so:

./bin/client_dynamic

The ldd command also confirmed the library being loaded from the project's lib directory:

libmyutils.so => /home/maryamrana/BSDSF24A018-OS-A01/lib/libmyutils.so

This demonstrates that the dynamic loader is responsible for locating and loading the required shared libraries at program startup/runtime. The executable itself does not contain the shared library's implementation. If the required library cannot be found in the loader's search paths, the program cannot start.


### 10. Man Pages

Man pages are the standard Linux documentation system for commands,
programs, and library functions. They allow users to access documentation
directly from the terminal using the `man` command.

For this project, man pages were created in the `man/man3/` directory
for all six utility functions:

- mystrlen
- mystrcpy
- mystrncpy
- mystrcat
- wordCount
- mygrep

Each man page uses groff formatting directives such as `.TH`, `.SH NAME`,
`.SH SYNOPSIS`, `.SH DESCRIPTION`, and `.SH AUTHOR`.

For example, a page can be previewed before installation using:

man -l man/man3/mystrlen.3

After installation, it can be accessed using:

man mystrlen


### 11. Makefile Install Target 
 
The `install` target installs the executable and man pages into standard 
system directories. 
 
The Makefile defines: 
 
PREFIX = /usr/local 
BINDIR = $(PREFIX)/bin 
MANDIR = $(PREFIX)/share/man/man3 
 
The install target creates the required directories and copies the files: 
 
install: all 
	install -d $(BINDIR) 
	install -m 755 bin/client $(BINDIR)/client 
	instal### 10. Makefile Install Target

The Makefile contains an `install` target that installs the executable
and man pages into standard Linux directories.

The installation directories are:

    PREFIX = /usr/local
    BINDIR = $(PREFIX)/bin
    MANDIR = $(PREFIX)/share/man/man3

The install target creates these directories and installs the files with
appropriate permissions.

The installation is performed using:

    sudo make install

The executable is installed as:

    /usr/local/bin/client

The man pages are installed under:

    /usr/local/share/man/man3/

After installation, the program can be run from any directory using:

    client

and the documentation can be accessed using:

    man mystrlen

This demonstrates how a Makefile can automate installation of both an
executable and its associated Linux documentation.
