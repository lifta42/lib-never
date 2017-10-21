# cps-library/src/Makefile
# 2017.10.21 by liftA42.

modules = control function testcase
objects = $(modules:%=%.o)
library = libcps.a

test_sources = $(wildcard *_test.cpp)
test_targets = $(test_sources:%.cpp=%)

CXXFLAGS += -std=c++14

all: $(library) testcases

$(library): $(objects)
	ar -rs $@ $^

control.o: function.h

testcases: $(test_targets)

%_test: $(library)
%_test: LDLIBS += $(library)

clean:
	rm $(library) $(objects) $(test_targets)
.PHONY: clean
