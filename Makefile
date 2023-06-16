CXX 	 	:= g++

INCLUDES    := -Iinclude/ -Isrc/
LINKS		:= -Llibs/libgtest

CXXFLAGS 	:= -std=c++20 -g -Wall -Wextra -Werror $(INCLUDES) $(LINKS)
GTESTFLAGS  := 


OUT := bin/main.exe

SRC := $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp,bin/%.o,$(SRC))

all: build
	./$(OUT) $(args)

build: $(OBJ)
	@mkdir -p $(dir $(OUT))
	$(CXX) $(CXXFLAGS) -o $(OUT) $(OBJ)

bin/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -r $(dir $(OUT))

