# cps-library/src/Makefile
# 2017.10.21 by liftA42.

modules = control function
objects = $(modules:%=%.o)
library = libcps.a

_test_execuables = $(modules:%=%_test)
_test_sources = $(_test_execuables:%=%.cpp)

CXXFLAGS += -std=c++14

all: $(library) testcases

$(library): $(objects)
	ar -rs $@ $^

control.o: function.h

testcases:

clean:
	rm $(library) $(objects)
.PHONY: clean
