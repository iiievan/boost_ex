CC     	 = g++
CFLAGS   = -g -Wall #-O2
CPPFLAGS = -c -std=c++0x
LIBS   	 = -pthread -lboost_system

EXEC     = server
SOURCES  = server.cpp
OBJECTS  = $(SOURCES:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJECTS) 
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) $(DFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)