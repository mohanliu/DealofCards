CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lc++
SOURCES=main.cpp DeckOfCards.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=output

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) *~