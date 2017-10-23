# cps-library/src/Makefile
# 2017.10.21 by liftA42.

project = never

modules = function
objects = $(modules:%=%.o)
library = lib$(project).a

modules_test = testcase testcase_start
objects_test = $(modules_test:%=%.o)
library_test = lib$(project)_test.a

test_targets = testcase_test testcase_start_test

CXXFLAGS += -std=c++14

all: $(library)($(objects)) $(library_test)($(objects_test)) $(test_targets)

$(objects) $(objects_test): %.o:%.h

$(test_targets): $(library) $(library_test)

clean:
	-rm $(library) $(library) $(objects) $(objects_test) $(test_targets)
.PHONY: clean
