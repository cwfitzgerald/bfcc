WARNINGS = -Wall -Wextra -Wno-sign-compare -Wno-unused-variable -Wno-switch
STD = -std=c++14
OPTIMIZE = -O3
DEBUG = 

CPP_FILES = $(wildcard src/*.cpp)
CPP_FILES +=$(wildcard src/targets/*.cpp)
CPP_FILES +=$(wildcard src/lexers/*.cpp)
CPP_FILES +=$(wildcard src/parsers/*.cpp)
OBJ_FILES = $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))

CXX=g++

all: bfcc

debug: DEBUG = -g -D DEBUG
debug: OPTIMIZE = -O0
debug: bfcc

profile: DEBUG = -pg
profile: bfcc

bfcc: $(OBJ_FILES)
	@echo Linking $@
	@$(CXX) $(STD) $(DEBUG) -o $@ $^

bin/%.o: src/%.cpp
	@mkdir -p bin/
	@echo CXX $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c -o $@ $<

bin/%.o: src/lexers/%.cpp
	@mkdir -p bin/
	@echo CXX $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c -o $@ $<

bin/%.o: src/targets/%.cpp
	@mkdir -p bin/
	@echo CXX $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c -o $@ $<

bin/%.o: src/parsers/%.cpp
	@mkdir -p bin/
	@echo CXX $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c -o $@ $<

clean:
	rm bin/*.o
	rm bfcc
