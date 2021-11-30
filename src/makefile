CC = g++
CFLAGS = -std=c++11 -Ofast
HEADERS = headers.h parser.h floorplan_core.h
SOURCE = main.cpp parser.cpp floorplan_core.cpp
OBJECTS = main.o parser.o floorplan_core.o
TARGET = ../bin/hw3
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
main.o : $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -c main.cpp
parser.o : $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -c parser.cpp
floorplan_core.o : $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -c floorplan_core.cpp	
clean :
	rm $(TARGET) $(OBJECTS)