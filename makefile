CC     	 = g++
CFLAGS   = -g -Wall #-O2
CPPFLAGS = -c -std=c++0x
LIBS   	 = -pthread -lboost_system

# Where the header are (no need to modify this)
INCLUDE = src
CLI_INCLUDE = src/client
SRV_INCLUDE = src/server

EXEC     = boost_app
#SUBDIRS  = $(wildcard */)
SUBDIRS  = $(wildcard src/ src/client/ src/server)
SOURCES  = $(wildcard $(addsuffix *.cpp,$(SUBDIRS)))
OBJECTS  = $(patsubst %.cpp,%.o,$(SOURCES))

$(EXEC): $(OBJECTS) 
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) $(DFLAGS) $(CPPFLAGS) -I $(INCLUDE) -I $(CLI_INCLUDE) -I $(SRV_INCLUDE) $< -o $@

.PHONY : clean
clean:
	rm -f $(EXEC) $(OBJECTS)