PROGRAM=beczatom

CXX = g++
CFLAGS = -std=c++17 -Wall -pedantic -Wextra -g -Wno-long-long -O0 -ggdb
SRC = $(wildcard src/source/*.cpp)
HEADERS = $(wildcard src/headers/*.h)
OBJS = $(patsubst src/source/%.cpp, objs/%.o, $(SRC))

.PHONY: all
all: objs $(PROGRAM) doc

run: compile
	./$(PROGRAM)

compile: objs $(PROGRAM)

doc: $(HEADERS) src/constants.h
	doxygen Doxyfile

$(PROGRAM): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^

objs/%.o: src/source/%.cpp
	$(CXX) $(CFLAGS) -MMD -c -o $@ $<

objs:
	mkdir -p objs

.PHONY: clean
clean:
	rm -rf $(PROGRAM) objs/ doc/ 2>/dev/null

-include objs/*.d