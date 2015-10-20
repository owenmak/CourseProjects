
# Define what compiler to use and the flags.
# This is the way you define and assign variables
# in a Makefile
CC=gcc
CXX=g++
CCFLAGS= -g

# A rule in Makefile has the form:
#
# target: dependencies
#	command
#
# where "target" and "dependencies" are files (most of the time).
# These means that if "target" does not exist or the modification 
# date of the dependencies are older than the modification time of
# "target" then "command" is executed.
#
# For example, the rule 
#
# mystring.o : mystring.c
#	$(CC) -c $(CXXFLAGS) mystring.c
#
# means that if mystring.o does not exist, or if mystring.c is older
# than mystring.o, then execute "$(CC) -c $(CXXFLAGS) mystring.c".
#
# The goal of make is to execute the minimum set of commands that
# are necessary to build the target files.
#
# Usually, the first target in a Makefile is called "all". 
# The dependencies of "all" are the files that we want to build.
#

all: test_mystring test_list test_mysort test Stack.o Queue.o

# Compile mystring.o if necessary
mystring.o : mystring.c
	$(CC) -std=c99 -c $(CCFLAGS) mystring.c

# Compile test_mystring.o if necessary
test_mystring.o : test_mystring.c
	$(CC) -std=c99 -c $(CCFLAGS) test_mystring.c

# Build test_mystring if necessary
test_mystring: mystring.o test_mystring.o
	$(CC) -std=c99 -o test_mystring mystring.o test_mystring.o

# Build test_list
List.o: List.cc
	$(CXX) -c $(CCFLAGS) List.cc

test_list.o: test_list.cc
	$(CXX) -c $(CCFLAGS) test_list.cc

test_list: test_list.o List.o
	$(CXX) -o test_list test_list.o List.o

# Build test_mysort
mysort.o : mysort.cc
	$(CXX) -c $(CCFALGS) mysort.cc

test_mysort.o: test_mysort.cc
	$(CXX) -c $(CCFALGS) test_mysort.cc

test_mysort: test_mysort.o mysort.o
	$(CXX) -o test_mysort test_mysort.o mysort.o

# Build Stack
Stack.o : Stack.cc
	$(CXX) -c $(CCFLAGS) Stack.cc
# Build Queue
Queue.o : Queue.cc
	$(CXX) -c $(CCFLAGS) Queue.cc
#
# Add the rules to build test_mysort here
#

test:
	rm -f test_results
	test_mystring && \
		(echo "test_mystring OK" >> test_results) || \
		(echo "test_mystring Failed" >> test_results) && \
	test_list && \
		(echo "test_list     OK" >> test_results) || \
		(echo "test_list     Failed" >> test_results) && \
	test_mysort && \
		(echo "test_mysort   OK" >> test_results) || \
		(echo "test_mysort   Failed" >> test_results) && \
	echo && \
	echo ------ Test Results ----- && \
	cat test_results 

clean:
	rm -f core *.o test_mystring test_list test_mysort test_results

