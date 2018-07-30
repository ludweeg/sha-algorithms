CC=g++

CFLAGS=-c -Wall -std=c++11 
LDFLAGS=
SOURCES=$(shell find . -name '*.cpp')
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sha

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Linking
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	@echo Compiling
	$(CC) $(CFLAGS) $< -o $@

clean:
	shred -u -n 35 $(OBJECTS) $(EXECUTABLE)

