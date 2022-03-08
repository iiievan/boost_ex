CC     	 = g++
CFLAGS   = -g -Wall #-O2
CPPFLAGS = -c -std=c++0x
LIBS   	 = -pthread -lboost_system

# Where the header are (no need to modify this)
INCLUDE = src

EXEC     = boost_app
#SUBDIRS  = $(wildcard */)
SUBDIRS  = $(wildcard src/)
SOURCES  = $(wildcard $(addsuffix *.cpp,$(SUBDIRS)))
OBJECTS  = $(patsubst %.cpp,%.o,$(SOURCES))

$(EXEC): $(OBJECTS) 
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) $(DFLAGS) $(CPPFLAGS) -I $(INCLUDE) $< -o $@

.PHONY : clean
clean:
	rm -f $(EXEC) $(OBJECTS)