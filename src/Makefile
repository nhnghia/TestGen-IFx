CC = g++
CFLAGS = -Wall -O3 -DABSTRACT -fno-stack-protector -Wno-write-strings -Wno-deprecated -Wno-parentheses -Wno-missing-field-initializers -Wno-unused-parameter -Wno-overloaded-virtual -g -rdynamic

.SUFFIXES: .o .C .h

.C.o:	
	${CC} -c -o $*.o $(CFLAGS) -I${IF}/src/simulator $*.C -lstdc++


all: 
	${CC} -c -o Bfs.o $(CFLAGS) -I${IF}/src/simulator Bfs.C
	${CC} -c -o Dfs.o $(CFLAGS) -I${IF}/src/simulator Dfs.C
	${CC} -c -o ManageOutputFiles.o $(CFLAGS) -I${IF}/src/simulator ManageOutputFiles.C
	${CC} -c -o mainExplorator.o $(CFLAGS) -I${IF}/src/simulator mainExplorator.C
	${CC} -c -o ManageStopConditions.o $(CFLAGS) -I${IF}/src/simulator ManageStopConditions.C
	${CC} -c -o state_list.o $(CFLAGS) -I${IF}/src/simulator state_list.C
	${CC} -c -o state_queue.o $(CFLAGS) -I${IF}/src/simulator state_queue.C
	${CC} -c -o state_stack.o $(CFLAGS) -I${IF}/src/simulator state_stack.C

tp: 
	${CC} -c -o ManageStopConditions.o $(CFLAGS) -I${IF}/src/simulator ManageStopConditions.C -lstdc++

install:
	$(shell mv *.o ../lib)

clean:
	-rm -f *~ *.o 
