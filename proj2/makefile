# EXE = $${PWD\#\#*/}
TEST = $(patsubst %.cpp, %, $(wildcard *[t]est*.cpp nested.cpp *old*) Graph.cpp )
EXE = $(strip $(patsubst %.cpp, %, $(filter-out $(TEST:=.cpp),$(wildcard p[0-9]*.cpp) $(wildcard ?river.cpp))))

GDBFLAGS = -O2 -ggdb
CXXFLAGS = -Og -ggdb
# CXXFLAGS = -Wall -g
# SOURCES = $(filter-out $(patsubst %, %.cpp,$(EXE)),$(wildcard *.cpp))
# SOURCES = $(wildcard *.cpp)
SOURCES = $(filter-out $(EXE:=.cpp) $(TEST:=.cpp),$(wildcard *.cpp))
SOURCES2 = $(SOURCES:.cpp=)
OBJS = $(SOURCES:.cpp=.o)
DEPS = $(wildcard *.h)

initalize: $(OBJS)

test: $(TEST)

all: $(EXE) run

build: $(EXE)

c: clean all

echo:
	echo TEST: $(TEST)
	echo EXE: $(EXE)
	echo SOURCES: $(SOURCES)
	echo SOURCES2: $(SOURCES2)
	echo OBJS: $(OBJS)
	echo DEPS: $(DEPS)
	
include .depend


# Grader.o: Grader.cpp Grader.h BaselineGraph.h Graph.h
# GraphTest1_old.o: GraphTest1_old.cpp Graph.h
# Graph.o: Graph.cpp Graph.h
# test1bg.o: test1bg.cpp BaselineGraph.h
# BaselineGraph.o: BaselineGraph.cpp BaselineGraph.h
# Int341.o: Int341.cpp Int341.h
# GraphTest1.o: GraphTest1.cpp Graph.h
# driver.o: driver.cpp Grader.h Graph.h

# %.o: %.h

	
	#-e 's/\(cpp\|h\)\($\|\s\)/o\2/g')
	# )
$(EXE): %: %.o $(OBJS)
		# $(CXX) $(CXXFLAGS) -o $(shell grep -i $@ .depend | sed -e 's/\.o://g' -e 's/\(cpp\|h\)\(\s\|$$\)/o\2/g')
		$(CXX) $(CXXFLAGS) -o $@ $< $(OBJS)
	
$(TEST): %: %.o
	$(CXX) $(CXXFLAGS) $(filter-out $<,$(OBJS:.o=.cpp)) $< -o $@
	# ./$@
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< 
	

%: %.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(filter-out $<,$(OBJS:.o=.cpp)) $< -o $%

clean:
	rm -f $(EXE) $(TEST) $(OBJS) $(wildcard *.stackdump) $(wildcard *.exe)
	# rm *.o*
	# rm *~ 

run(%): %.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(filter-out $<,$(OBJS:.o=.cpp)) $< -o $%
	./$% < input.txt > output.txt
	
gdb(%): %.cpp $(OBJS) 
	$(CXX) $(CXXFLAGS) $(filter-out $<,$(OBJS:.o=.cpp)) $< -o $%
	./$@.bat $% 	

gdb2(%): %.cpp $(OBJS) 
	$(CXX) $(GDBFLAGS) $(filter-out $<,$(OBJS:.o=.cpp)) $< -o $%
	./gdb.bat $% 	

diff(%): %.txt run(%)
	diff $< output.txt
	# type diff.txt
	
run:
	./$(EXE)


	
depend: .depend


.depend: $(wildcard *.cpp)
	rm -f ./.depend
	$(CC) $(CXXFLAGS) -MM $^ > ./.depend;
	


