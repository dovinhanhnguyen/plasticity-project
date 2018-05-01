CC = g++
CCSW = -O3 -Wno-deprecated-declarations

data_analysis: main.o experiment.o atom_radius.o
	$(CC) -o data_analysis main.o experiment.o atom_radius.o ${CCSW}

main.o: main.cpp main.h display.h atom_radius.h

experiment.o: experiment.cpp experiment.h

atom_radius.o: atom_radius.cpp atom_radius.h

.cpp.o:
	$(CC) ${CCSW} -c $<

clean:
	echo cleaning up; /bin/rm -f core *.o data_analysis

all:	data_analysis
