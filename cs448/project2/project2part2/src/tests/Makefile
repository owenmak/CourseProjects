JDKPATH = /usr
LIBPATH = ../../lib/heapAssign.jar
#CS448 Note - With the previous line you will use the library provided for part 2.
#This is good to start with this part of the project but the
#final goal of this project is to use what you have developed in the first part
#instead of the library. Make the necessary modifications in this file for your
#final version

CLASSPATH = $(JDKPATH)/lib/classes.zip:.:..:$(LIBPATH):../heap
BINPATH = $(JDKPATH)/bin
JAVAC = $(JDKPATH)/bin/javac -classpath $(CLASSPATH)
JAVA  = $(JDKPATH)/bin/java  -classpath $(CLASSPATH)

PROGS = hftest

all: $(PROGS)

# test buffer manager

BMTest:BMTest.java
	$(JAVAC) TestDriver.java BMTest.java

bmtest: BMTest
	$(JAVA) tests.BMTest

# test disk manager

DBTest:DBTest.java
	$(JAVAC) TestDriver.java DBTest.java

dbtest: DBTest
	$(JAVA) tests.DBTest

# test heapfile 

HFTest:HFTest.java
	$(JAVAC) TestDriver.java HFTest.java

hftest: HFTest
	$(JAVA) tests.HFTest

# test btree

BTTest:BTTest.java
	$(JAVAC) TestDriver.java BTTest.java

bttest: BTTest
	$(JAVA) tests.BTTest

# test index

IndexTest:IndexTest.java
	$(JAVAC) TestDriver.java IndexTest.java

indextest: IndexTest
	$(JAVA) tests.IndexTest

# test join

JoinTest:JoinTest.java
	$(JAVAC) TestDriver.java JoinTest.java

jointest: JoinTest
	$(JAVA) tests.JoinTest

# test sort

SortTest:SortTest.java
	$(JAVAC) TestDriver.java SortTest.java

sorttest: SortTest
	$(JAVA) tests.SortTest



xx:
	jar tf $(LIBPATH)

clean:
	\rm -f *.class *~ \#* core TRACE
