# cps-library/Makefile
# 2017.10.23 by liftA42.

project = never

source_dir = source
example_dir = example

library = lib$(project).a
library_test = lib$(project)_test.a

CXXFLAGS += -std=c++14 -O2

export project source_dir example_dir library library_test CXXFLAGS

all:
	$(MAKE) -C $(source_dir)

example:
	$(MAKE) -C $(example_dir)

test:
	$(MAKE) -C $(source_dir) test

clean:
	$(MAKE) -C $(source_dir) clean
	$(MAKE) -C $(example_dir) clean

.PHONY: all example clean test
