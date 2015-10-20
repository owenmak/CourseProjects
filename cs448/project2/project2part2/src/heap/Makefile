JDKPATH = /usr
LIBPATH = ../../lib/heapAssign.jar
#CS448 Note - With the previous line you will use the library provided for part 2.
#This is good to start with this part of the project(or for testing) but the
#final goal of this project is to use what you have developed in the first part
#instead of the library. Make the necessary modifications in this file for your
#final version

CLASSPATH = $(JDKPATH)/lib/classes.zip:.:..:$(LIBPATH)
BINPATH = $(JDKPATH)/bin
JAVAC = $(JDKPATH)/bin/javac -classpath $(CLASSPATH)
JAVA  = $(JDKPATH)/bin/java  -classpath $(CLASSPATH)

PROGS = together

all: $(PROGS)

hf:Heapfile.java
	$(JAVAC) Heapfile.java

hp:HFPage.java
	$(JAVAC) HFPage.java

tuple:Tuple.java
	$(JAVAC) Tuple.java

Scan:Scan.java
	$(JAVAC) Scan.java

together:*.java
	$(JAVAC) *.java

xx:
	jar tf $(LIBPATH)

clean:
	\rm -f *~ \#* core 
