

CC = g++
FLAGS = -Wall 
TARGET = curves
OBJECTS = main.o Curve.o

vpath %.cpp ./src
vpath %.h ./src

all : $(OBJECTS)
	$(CC) $(FLAGS) -o $(TARGET) $^


%.o : %.cpp
	$(CC) -c $(FLAGS) $< 

.PHONY: clean
clean : 
	rm $(TARGET) $(OBJECTS)
