TARGET=dwasm
CXX=clang++
CXX?=clang++
CXX_FLAGS=-std=c++11
CXX_EXTRA?=
CXX_FLAGS+=$(CXX_EXTRA)
LD_FLAGS=
EXTRA_LD_FLAGS?=
LD_FLAGS+=$(EXTRA_LD_FLAGS)
ADD_SANITIZERS_CC= -g -fsanitize=address -fno-omit-frame-pointer
ADD_SANITIZERS_LD= -g -fsanitize=address
MEM_SANITIZERS_CC= -g -fsanitize=memory -fno-omit-frame-pointer
MEM_SANITIZERS_LD= -g -fsanitize=memory
UB_SANITIZERS_CC= -g  -fsanitize=undefined -fno-omit-frame-pointer
UB_SANITIZERS_LD= -g  -fsanitize=undefined
BUILD_MODE?=COV_NO_CLANG_1Z

SRCS=$(wildcard *.cpp)

.DEFAULT:all

.PHONY:all clean help

all:$(TARGET)

depend:.depend

.depend:$(SRCS)
	rm -rf .depend
	$(CXX) -MM $(CXX_FLAGS) $^ > ./.depend

-include ./.depend

.cpp.o:
	$(CXX) $(CXX_FLAGS) -c $< -o $@ 

$(TARGET): $(TARGET).o
	$(CXX) $^ $(LD_FLAGS) -o $@

clean:
	rm -f *.o *~ $(TARGET)
	rm .depend

help:
	@echo "all is the default target"
	@echo "there is clean."
