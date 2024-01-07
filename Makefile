include gmtt.mk

CXX := g++
CC  := gcc
INCLUDE := -Iinclude/
STD     := -std=c++17
FLAGS   := -O3 -g -Wall -Wextra -Werror $(INCLUDE)

srcdir := src
src    := $(call wildcard-rec,$(srcdir)/**.cpp)
obj    := $(src:%.cpp=%.o)

libdir 	:= include
libsrc 	:= $(call wildcard-rec,$(libdir)/**.c)
libobj 	:= $(libsrc:%.c=lib/%.o)

testdir  := test
testsrc := $(call wildcard-rec,$(testdir)/**.cpp)
testobj := $(testsrc:%.cpp=test/%.o)


bin := bin
OUT := 6502.exe
OUT_TEST := test.exe


run: build
	./$(OUT) $(args)

build: $(obj)
	windres resource.rc -o $(bin)/resource.o
	$(CXX) $(STD) $(FLAGS) $(wildcard $(bin)/*.o $(bin)/lib/*.o) -o $(OUT)

libs: $(libobj)

test: $(testobj)
	$(CXX) $(STD) $(FLAGS) -DGTEST_HAS_PTHREAD=1 $(wildcard $(bin)/test/*.o) $(wildcard $(bin)/lib/*.o) libs/libgtest.a -Llibs -lgtest -lpthread -o $(OUT_TEST)
	./$(OUT_TEST) $(args)
.PHONY: build all libs test clean run

%.o: %.cpp
	-@mkdir -p $(bin)/
	$(CXX) $(STD) $(FLAGS) -c $< -o $(bin)/$(@F)

lib/%.o: %.c
	-@mkdir -p $(bin)/lib/
	$(CC) --std=c17 $(FLAGS) -c $< -o $(bin)/lib/$(@F)

test/%.o: %.cpp
	-@mkdir -p $(bin)/test/
	$(CXX) $(STD) $(FLAGS) -c $< -o $(bin)/test/$(@F)


clean:
	-@rm -r $(bin)/
	-@rm $(OUT)
