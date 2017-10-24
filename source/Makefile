# cps-library/src/Makefile
# 2017.10.21 by liftA42.

modules = function
objects = $(modules:%=%.o)
sources = $(modules:%=%.cpp)

modules_test = testcase testcase_start
objects_test = $(modules_test:%=%.o)
sources_test = $(modules_test:%=%.cpp)

test_targets = testcase_test testcase_start_test
test_dir = test

dependence = $(sources:.cpp=.d) $(sources_test:.cpp=.d)

all: $(library) $(library_test)

# https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html#Automatic-Prerequisites
%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) -f $@.$$$$

-include $(dependence)

$(test_targets): $(library) $(library_test)

$(library): $(objects)
	$(AR) -r -c $@ $^

$(library_test): $(objects_test)
	$(AR) -r -c $@ $^

test: $(test_targets)
	$(SHELL) testcase_test.sh && \
	$(SHELL) testcase_start_test.sh && \
	$(MAKE) -C $(test_dir) test

clean:
	$(RM) $(library) $(objects) $(objects_test) $(test_targets) \
		$(dependence)
	$(MAKE) -C $(test_dir) clean

.PHONY: all test clean depend
