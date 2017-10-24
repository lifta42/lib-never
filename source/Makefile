# cps-library/src/Makefile
# 2017.10.21 by liftA42.

modules = function
objects = $(modules:%=%.o)
sources = $(modules:%=%.cpp)

modules_test = testcase testcase_start
objects_test = $(modules_test:%=%.o)
sources_test = $(modules_test:%=%.cpp)

test_targets = testcase_test testcase_start_test

dependence = $(sources:.cpp=.d) $(sources_test:.cpp=.d)

all: $(library)($(objects)) $(library_test)($(objects_test)) \
	$(test_targets)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(dependence)

$(test_targets): $(library) $(library_test)

test:
	sh testcase_test.sh && \
	sh testcase_start_test.sh

clean:
	-rm $(library) $(objects) $(objects_test) $(test_targets) \
		$(dependence)

.PHONY: all test clean depend
