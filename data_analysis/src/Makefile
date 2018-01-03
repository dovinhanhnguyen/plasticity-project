CC = g++
CCSW = -O3 -Wno-deprecated-declarations

plasticity: plasticity.o
	$(CC) -o plasticity plasticity.o ${CCSW}

plasticity.o: plasticity.cpp plasticity.h

.cpp.o:
	$(CC) ${CCSW} -c $<

clean:
	echo cleaning up; /bin/rm -f core *.o plasticity

all:	plasticity
