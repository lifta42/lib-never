# cps-library/src/Makefile
# 2017.10.21 by liftA42.

modules = function testcase
objects = $(modules:%=%.o)
library = libcps.a

test_sources = $(wildcard *_test.cpp)
test_targets = $(test_sources:%.cpp=%)

CXXFLAGS += -std=c++14

all: $(library) $(test_targets)

$(library): $(objects)
	ar -rs $@ $^

$(objects): %.o:%.h


$(test_targets): $(library)


clean:
	rm $(library) $(objects) $(test_targets)
.PHONY: clean
