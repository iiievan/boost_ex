SRC_DIR    := src
CLI_DIR    := src/client
SRV_DIR    := src/server
BIN_DIR    := bin
OBJ_DIR    := obj
EXEC_NAME  := boost_app

SUBDIRS    := $(wildcard $(SRC_DIR) $(CLI_DIR) $(SRV_DIR))
INCLUDES   := $(addprefix -I,$(SUBDIRS))
SOURCES    := $(wildcard $(addsuffix /*.cpp,$(SUBDIRS)))

CXX    	   := g++
STD        := -std=c++11
CXXFLAGS   := -g $(STD) -Wall -ldl -pedantic #-O2
CPPFLAGS   := -c $(STD) $(INCLUDES) 
LIBS   	   := -lboost_filesystem -lboost_system -pthread
OBJECTS    := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXEC_FILES := $(EXEC_NAME:%=$(BIN_DIR)/%)

all:$(EXEC_FILES)

debug: $(EXEC_FILES)

$(EXEC_FILES): buildrepo $(OBJECTS) 
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LIBS) -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

.PHONY : clean debug
clean:
	rm -Rf $(BIN_DIR) $(OBJ_DIR)

buildrepo:
	@$(call make-repo)

# Create obj directory structure and bin
define make-repo
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	for dir in $(SUBDIRS); \
	do \
		mkdir -p $(OBJ_DIR)/$$dir; \
	done
endef