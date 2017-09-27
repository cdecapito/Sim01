CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Sim01 : Sim01.o metaData.o configData.o
	$(CC) $(LFLAGS) Sim01.o metaData.o configData.o -o Sim01

Sim01.o : Sim01.cpp metaData.cpp configData.cpp simFuncs.cpp
	$(CC) $(CFLAGS) Sim01.cpp 

metaData.o : metaData.cpp metaData.h
	$(CC) $(CFLAGS) metaData.cpp

configData.o: configData.cpp configData.h
	$(CC) $(CFLAGS) configData.cpp

clean: 
	\rm *.o Sim01