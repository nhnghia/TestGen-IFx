
  CC = g++
  LIB = $(TestGenIFx)/lib
  CFLAGS = -W -Wall -O3 -DABSTRACT -fno-stack-protector -Wno-missing-field-initializers -Wno-unused-parameter -Wno-unused-variable -Wno-parentheses -Wno-deprecated -Wno-tautological-compare -Wno-overloaded-virtual -g 
  
.SUFFIXES: 
.SUFFIXES: .exe .x .g .y .so .o .C .h .m4 .if

.o.g:
	$(CC) -o $*.g $*.o ${LIB}/state_list.o ${LIB}/state_queue.o ${LIB}/state_stack.o ${LIB}/Event.o ${LIB}/TestCase.o ${LIB}/main.o ${LIB}/Exhaustive.o ${LIB}/RandomExplorator.o ${LIB}/Tool.o ${LIB}/CallTrace.o ${LIB}/Explorator.o ${LIB}/HitOrJump.o  -L${IF}/bin/`${IF}/com/arch` -L$(XERCESLIB) -lsimulator -lmodel -lexplorator -lxerces-c -lstdc++.6

.o.x:
	$(CC) -o $*.x $*.o -L${IF}/bin/`${IF}/com/arch` -lexplorator -lsimulator

.o.y:
	$(CC) -o $*.y $*.o -L${IF}/bin/`${IF}/com/arch` -levaluator -lsimulator

.o.so:
	$(CC) -shared -o $*.so $*.o -L${IF}/bin/`${IF}/com/arch` -lexplorator -lsimulator

.o.exe:
	$(CC) -o $*.exe $*.o -L${IF}/bin/`${IF}/com/arch` -lexplorator -lsimulator

.C.o:
#Nghia
	echo "void IfObserverInstance::printXML(std::ostream& buf) const {}" >> $*.C ;
	echo "void IfInstance::printXML(std::ostream& buf) const {}" >> $*.C ;
	echo "void IfMessage::printXML(std::ostream& buf) const {}" >> $*.C ; 
#end Nghia

	$(CC) -c -o $*.o $(CFLAGS) -I${IF}/src/simulator -I$(IF)/src/simulator-t  $*.C
	
.m4.C:
	m4 -I$(IF)/src/code -D_CTYPE_=h $*.m4 > $*.h
	m4 -I$(IF)/src/code -D_CTYPE_=C $*.m4 > $*.C

.if.m4:
	${IF}/bin/`${IF}/com/arch`/if2m4 $(TIME) $*.if

clean:
	-rm -f *~ $*.exe $*.g $*.x $*.y $*.so $*.o $*.h $*.C $*.m4 >> /dev/null
	-rm -f *~ *.exe *.g *.x *.y *.so *.o *.h *.C *.m4 output.* *.txt output.*.* message.xml *.value *.sequence *.suite >> /dev/null


