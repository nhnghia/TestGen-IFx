CC = g++
CFLAGS = -Wall -O3 -DABSTRACT -fno-stack-protector -Wno-write-strings -Wno-deprecated -Wno-parentheses -Wno-missing-field-initializers -Wno-unused-parameter -Wno-uninitialized

.SUFFIXES: .o .C .h

all: getSignalRoute
	
getSignalRoute: getSignalRoute.o
	$(CC) -g getSignalRoute.o -o getSignalRoute -L$(IF)/bin/`${IF}/com/arch` -lmodel
	
getSignalRoute.o :
	${CC} -g -c -o getSignalRoute.o $(CFLAGS) -I${IF}/src/model  getSignalRoute.C

#install:
#	mv if2dot ~/bin/

clean:
	-rm -f *~ *.o getSignalRoute
