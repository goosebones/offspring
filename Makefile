#
# Created by gmakemake (Ubuntu Jul 25 2014) on Mon Nov 25 06:43:31 2019
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CFLAGS = -std=c99 -ggdb -Wall -Wextra -pedantic

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	arg_parse.c offspring.c queue.c tree_node.c trimit.c
PS_FILES =	
S_FILES =	
H_FILES =	arg_parse.h queue.h tree_node.h trimit.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	arg_parse.o queue.o tree_node.o trimit.o 

#
# Main targets
#

all:	offspring 

offspring:	offspring.o $(OBJFILES)
	$(CC) $(CFLAGS) -o offspring offspring.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

arg_parse.o:	arg_parse.h trimit.h
offspring.o:	arg_parse.h tree_node.h trimit.h
queue.o:	queue.h tree_node.h
tree_node.o:	queue.h tree_node.h
trimit.o:	trimit.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) offspring.o core

realclean:        clean
	-/bin/rm -f offspring 
