# cps-library/example/Makefile
# 2017.10.23 by liftA42.

sources = $(wildcard *.cpp)
targets = $(sources:%.cpp=%)

library = ../source/libnever.a

CXXFLAGS += -std=c++14 -I../source

all: $(targets)

$(targets): $(library)

clean:
	-rm $(targets)
.PHONY: clean
