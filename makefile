
SRCS = main.cpp

OBJS = $(SRCS:.cpp =.o)

TARGET = boost_ex 

CC = g++

CXXFLAGS = std=c++0x -g -Wall

all: $(TARGET)

$(TARGET): 	$(OBJS) # This line will compile to .o every .cpp which need to be (which have been modified)
			$(CC) -o $(TARGET) $(OBJS) # Linking (no need to CXXFLAGS here, it's used when compiling on previous line

main.o : 	$(SRCS)/main.cpp
			$(CC) $(CXXFLAGS) -c -o $@ $^

.PHONY : clean
clean :
	rm $(TARGET) $(OBJ)