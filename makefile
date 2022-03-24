SRC_DIR    := src
CLI_DIR    := src/client
SRV_DIR    := src/server
BIN_DIR    := bin
OBJ_DIR    := obj
EXEC_NAME  := boost_app

SUBDIRS    := $(wildcard $(SRC_DIR) $(CLI_DIR) $(SRV_DIR))
INCLUDES   := $(addprefix -I,$(SUBDIRS))
SOURCES    := $(wildcard $(addsuffix /*.cpp,$(SUBDIRS)))

CC     	   := g++
CFLAGS     := -g -Wall #-O2
CPPFLAGS   := -c -std=c++0x $(INCLUDES) 
LIBS   	   := -pthread -lboost_system -lboost_filesystem
OBJECTS    := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXEC_FILES := $(EXEC_NAME:%=$(BIN_DIR)/%)

all:$(EXEC_FILES)

debug: CFLAGS += -Wextra
debug: $(EXEC_FILES)

$(EXEC_FILES): buildrepo $(OBJECTS) 
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(DFLAGS) $(CPPFLAGS) $< -o $@

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