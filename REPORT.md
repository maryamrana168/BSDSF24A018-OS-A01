
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


