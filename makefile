WARNINGS = -Wall -Wextra -Wno-sign-compare -Wno-unused-variable -Wno-switch
STD = -std=c++1y
OPTIMIZE = -O3

CPP_FILES = $(wildcard src/*.cpp)
CPP_FILES +=$(wildcard src/codegen/*.cpp)
CPP_FILES +=$(wildcard src/lexers/*.cpp)
OBJ_FILES = $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))

CXX=g++-5

all: bfcc

debug: OPTIMIZE = -Og -g -D DEBUG
debug: bfcc

bfcc: $(OBJ_FILES)
	@echo Linking $@
	@$(CXX) $(STD) -o $@ $^

bin/%.o: src/%.cpp
	@mkdir -p bin/
	@echo CXX $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) -c -o $@ $<

bin/%.o: src/lexers/%.cpp
	@mkdir -p bin/
	@echo CXX $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) -c -o $@ $<

bin/%.o: src/codegen/%.cpp
	@mkdir -p bin/
	@echo CXX $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) -c -o $@ $<

clean:
	rm bin/*.o
	rm bfcc
