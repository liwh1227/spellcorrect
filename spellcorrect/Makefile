INC_DIR:= ./inc/Reactor ./inc/thread_pool  ./inc/cache ./inc/timer ./inc
SRC_DIR:= ./src/Reactor ./src/thread_pool ./src/cache  ./src/timer  ./src
SRCS:=$(wildcard ./src/Reactor/*.cc) $(wildcard ./src/thread_pool/*.cc) $(wildcard ./src/*.cc) $(wildcard ./src/cache/*.cc) $(wildcard ./src/timer/*.cc) 
OBJS:= $(patsubst %.cc,%.o,$(SRCS))
LIBS:=-lpthread
INC_FILE:= $(addprefix -I,$(INC_DIR)) 
CXX:=g++
CXXFLAGS:= -w -g $(INC_FILE) $(LIBS)   
EXE:= ./bin/server.exe

$(EXE):$(OBJS)
	$(CXX) -o  $(EXE) $(OBJS) $(CXXFLAGS)
clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
