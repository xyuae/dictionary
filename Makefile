#
# Makefile
#
# Computer Science 50
# Problem Set 5
#


# compiler to use
# specifies that make should use clang for compiling
CC = clang

# flags to pass compiler
# specifies that clang should use some flags, most of which 
# should look familiar.
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# name for executable
EXE = speller

# space-separated list of header files
HDRS = dictionary.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
# that will collectively implement speller
SRCS = speller.c dictionary.c

# automatically generated list of object files
# the value of which is identical to that of SRCS
# except that each file's extension is not .c but .o
OBJS = $(SRCS:.c=.o)


# default target
# using the variables defined above that tells make how to 
# compile speller
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
# specifies that our .o fiels all depend on dictionary.h and Makefile
# so taht changes to either introduce recompilation of the former
# when you run make
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
