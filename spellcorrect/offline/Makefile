INC_DIR:= ./inc
SRC_DIR:= ./src
SRCS:= $(wildcard ./src/*.cc)
OBJS:=$(patsubst %.cc,%.o,$(SRCS))

CXX:= g++
CXXFLAGS:= -w -g $(addprefix -I,$(INC_DIR))
EXE:=./bin/main

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)
clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
