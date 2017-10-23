# cps-library/Makefile
# 2017.10.23 by liftA42.

project = never

source_dir = source
example_dir = example

library = lib$(project).a
library_test = lib$(project)_test.a

export project source_dir example_dir library library_test

all:
	make -C $(source_dir)

example:
	make -C $(example_dir)

clean:
	make -C $(source_dir) clean
	make -C $(example_dir) clean

.PHONY: all example clean
