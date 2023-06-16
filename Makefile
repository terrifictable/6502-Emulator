CXX 	 	:= g++
CXXFLAGS 	:= -std=c++20 -g -Wall -Wextra -Werror
GTESTFLAGS  := 


OUT := bin/main.exe

SRC := $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp,bin/%.o,$(SRC))

all: $(OBJ)
	@mkdir -p $(dir $(OUT))
	$(CXX) $(CXXFLAGS) -o $(OUT) $(OBJ)
	./$(OUT)

bin/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -r $(dir $(OUT))

