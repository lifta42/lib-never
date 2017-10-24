# cps-library/example/Makefile
# 2017.10.23 by liftA42.

sources = $(wildcard *.cpp)
targets = $(sources:%.cpp=%)

library := ../$(source_dir)/$(library)
library_test := ../$(source_dir)/$(library_test)

CXXFLAGS += -I../$(source_dir)

all: $(targets)

$(targets): $(library)

01_testing: $(library_test)

clean:
	$(RM) $(targets)
.PHONY: clean
