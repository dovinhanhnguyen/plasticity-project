CC = g++
CCSW = -O3 -Wno-deprecated-declarations

script: script.o data_handling.o
	$(CC) -o script script.o data_handling.o ${CCSW}

velocity_profile: velocity_profile.o data_handling.o
	$(CC) -o velocity_profile velocity_profile.o data_handling.o ${CCSW}

plasticity: plasticity.o
	$(CC) -o plasticity plasticity.o ${CCSW}

script.o: script.cpp data_handling.cpp script.h data_handling.h

velocity_profile.o: velocity_profile.cpp data_handling.cpp velocity_profile.h data_handling.h

plasticity.o: plasticity.cpp plasticity.h

.cpp.o:
	$(CC) ${CCSW} -c $<

clean:
	echo cleaning up; /bin/rm -f core *.o script velocity_profile plasticity

all:	script velocity_profile plasticity
