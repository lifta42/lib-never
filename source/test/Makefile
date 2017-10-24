sources = $(wildcard *.cpp)
target = test_exec.out

test: $(target)
	./$(target)

$(target): $(sources) ../$(library) ../$(library_test)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@
clean:
	-$(RM) $(target)

.PHONY: test clean
