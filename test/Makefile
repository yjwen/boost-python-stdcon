CXXFLAGS += $(shell python-config --cflags) -fPIC -I../include

LDFLAGS += $(shell python-config --ldflags)
LDFLAGS += -lboost_python39 -shared

HEADERS = $(wildcard ../include/*.hpp)
stdcon.o: stdcon.cpp $(filter-out %tuple_arg.hpp,$(HEADERS))
tuple.o: tuple.cpp $(filter %tuple_arg.hpp,$(HEADERS))
tuple.o: CXXFLAGS += -std=c++17

stdcon.so: stdcon.o tuple.o
	$(CXX) $(LDFLAGS) $^ -o $@

test: stdcon.so test.py
	python test.py

