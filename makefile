 #This makefile will compile a given program.
# An executable will be created with all appropriate files being compiled and linked.
# Additionally, preprocessor output files and dependencies will be generated.

SHELL = /bin/sh
SRCDIR = . 
CPPUNIT_HOME = /usr/include/cppunit
CPPUNIT_LIB =
BREAK= /usr/lib/
CC = gcc
CPP = g++
YACC = bison -y
CDEBUG = -g
COMPLIANCE_FLAGS = -O3
CFLAGS = $(COMPLIANCE_FLAGS) $(CDEBUG) -I. -I$(SRCDIR) -I$(CPPUNIT_HOME)
LDFLAGS = -g
# List your sources and objects here.
SOURCES = linkedlist.c
MAIN = 
OBJS = linkedlist.o
TESTCASEOBJS = 

# list the name of your output program here.
EXECUTABLE = testProgram

include $(OBJS:.o=.d)

all : $(OBJS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJS) $(MAIN)
	$(CC) -o $(EXECUTABLE)  $(OBJS) $(MAIN)


%.o : %.cpp #Defines how to translate a cpp file into an object file
	echo compiling $<
	echo $(CPP) $(CFLAGS) -c $<
	$(CPP) $(CFLAGS) -E $< > $<.preout
	$(CPP) $(CFLAGS) -S $<
	$(CPP) $(CFLAGS) -c $<
	echo done compiling $<

%.o : %.c #Defines how to translate a single c file into an object file.
	echo compiling $<
	echo $(CC) $(CFLAGS) -c $<
	$(CC) $(CFLAGS) -E $< > $<.preout
	$(CC) $(CFLAGS) -S $<
	$(CC) $(CFLAGS) -c $<
	echo done compiling $<


%.d : %.c #Defines how to generate the dependencies for the given files.  -M gcc option generates dependencies.
	@set -e; rm -f $@; \
	$(CC) $(COMPLIANCE_FLAGS ) -M $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

clean :   # Clean build in which everything is created from scratch.
	rm -f *.o
	rm -f *.d
	rm -f *.s
	rm -f *.preout
	rm -f $(EXECUTABLE)
	rm -f testCases
	rm -f testResults

