SRC_DIR  := src
CLI_DIR  := src/client
SRV_DIR  := src/server
INCLUDES := -I$(SRC_DIR) -I$(CLI_DIR) -I$(SRV_DIR)

CC     	 := g++
CFLAGS   := -g -Wall #-O2
CPPFLAGS := -c -std=c++0x $(INCLUDES) 
LIBS   	 := -pthread -lboost_system

EXEC_NAME  := boost_app

SUBDIRS  := $(wildcard $(SRC_DIR) $(CLI_DIR) $(SRV_DIR))
SOURCES  := $(wildcard $(addsuffix /*.cpp,$(SUBDIRS)))
OBJECTS  := $(patsubst %.cpp,%.o,$(SOURCES))

$(EXEC_NAME): $(OBJECTS) 
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $(EXEC_NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(DFLAGS) $(CPPFLAGS) $< -o $@

.PHONY : clean
clean:
	rm -f $(EXEC_NAME) $(OBJECTS)