WARNINGS = -Wall -Wextra -Wno-sign-compare -Wno-unused-variable 
FULLWARN = -Wall -Wextra -Wpedantic
STD = -std=c++14
OPTIMIZE = -O3
DEBUG = 

CPP_FILES = $(wildcard src/*.cpp)
CPP_FILES +=$(wildcard src/targets/*.cpp)
CPP_FILES +=$(wildcard src/lexers/*.cpp)
CPP_FILES +=$(wildcard src/parsers/*.cpp)
OBJ_FILES = $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))

EXTANT = 

CXX=clang++

all: bfcc

win64: CXX = x86_64-w64-mingw32-g++
win64: STD += -static
win64: EXTANT = .exe
win64: prep bfcc
	rm -f bin/*.o

debug: DEBUG = -g -D DEBUG
debug: OPTIMIZE = -O0
debug: bfcc

profile: DEBUG = -pg
profile: bfcc

warn: WARNINGS = $(FULLWARN)
warn: bfcc

bfcc: $(OBJ_FILES)
	@echo Linking $@$(EXTANT)
	@$(CXX) $(STD) $(DEBUG) $(OPTIMIZE) -o $@$(EXTANT) $^

bin/%.o: src/%.cpp
	@mkdir -p bin/
	@echo $(CXX) $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c -o $@ $<

bin/%.o: src/lexers/%.cpp
	@mkdir -p bin/
	@echo $(CXX) $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c -o $@ $<

bin/%.o: src/targets/%.cpp
	@mkdir -p bin/
	@echo $(CXX) $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c -o $@ $<

bin/%.o: src/parsers/%.cpp
	@mkdir -p bin/
	@echo $(CXX) $<
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c -o $@ $<

prep:
	-rm -f bin/*.o

clean: prep
	-rm -f bfcc*
