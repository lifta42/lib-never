# cps-library/src/Makefile
# 2017.10.21 by liftA42.

project = never

modules = function testcase testcase_start
objects = $(modules:%=%.o)
library = lib$(project).a

test_targets = testcase_test testcase_start_test

CXXFLAGS += -std=c++14

all: $(library) $(test_targets)

$(library): $(objects)
	ar -rs $@ $^

$(objects): %.o:%.h

$(test_targets): $(library)

clean:
	rm $(library) $(objects) $(test_targets)
.PHONY: clean
