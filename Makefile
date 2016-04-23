IDIR = ./include
CC = gcc
CXX = g++
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS = -I $(IDIR) -std=c++11
LD_FLAGS =

out : $(OBJ_FILES) 
	$(CXX) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CXX) $(CC_FLAGS) -c -o $@ $<