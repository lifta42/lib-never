# cps-library/example/Makefile
# 2017.10.23 by liftA42.

sources = $(wildcard *.cpp)
targets = $(sources:%.cpp=%)

library = ../source/libnever.a
library_test = ../source/libnever_test.a

CXXFLAGS += -std=c++14 -I../source

all: $(targets)

$(targets): $(library)

01_testing: $(library_test)

clean:
	-rm $(targets)
.PHONY: clean
