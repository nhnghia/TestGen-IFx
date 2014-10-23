CC = g++
AR = ar
CFLAGS = -Wall -O3 -DABSTRACT -std=c++11 -fno-stack-protector -Wno-write-strings -Wno-deprecated -Wno-parentheses -Wno-missing-field-initializers -Wno-unused-parameter -Wno-overloaded-virtual -g

.SUFFIXES: .o .cpp .h

SRC_1 = CallTrace.cpp Event.cpp Exhaustive.cpp Explorator.cpp HitOrJump.cpp TestCase.cpp TestPurpose.cpp Tool.cpp RandomExplorator.cpp
SRC_2 = state_list.C state_queue.C state_stack.C 	

OBJS = $(SRC_1:.cpp=.o) $(SRC_2:.C=.o)

all: $(OBJS)
	${CC} -c -o main.o $(CFLAGS) -I${IF}/src/simulator -I${IF}/src/simulator-t -I${XERCESLIB}/../include  main.C
	
$(OBJS): %.o : %.h

.cpp.o:
	${CC} $(CFLAGS) -I${IF}/src/simulator -I${IF}/src/simulator-t -I${XERCESLIB}/../include  -c $<

.C.o:
	${CC} $(CFLAGS) -I${IF}/src/simulator -I${XERCESLIB}/../include  -c $<
  
clean:
	rm -f $(OBJS)

tp: all
	${CC} -c -o Explorator.o $(CFLAGS) -I${IF}/src/simulator -I${XERCESLIB}/../include Explorator.cpp

install:
	cp $(OBJS) main.o $(TestGenIFx)/lib/