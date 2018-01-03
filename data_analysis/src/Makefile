CC = g++
CCSW = -O3 -Wno-deprecated-declarations

data_analysis: main.o
	$(CC) -o data_analysis main.o ${CCSW}

main.o: main.cpp main.h

.cpp.o:
	$(CC) ${CCSW} -c $<

clean:
	echo cleaning up; /bin/rm -f core *.o data_analysis

all:	data_analysis
