CXXFLAGS += $(shell python-config --cflags) -fPIC -I../include

LDFLAGS += $(shell python-config --ldflags)
LDFLAGS += -lboost_python39 -shared

HEADERS = $(wildcard ../include/*.hpp)
stdcon.o: stdcon.cpp $(filter-out %tuple_arg.hpp %optional_arg.hpp,$(HEADERS))
stdcon17.o: stdcon17.cpp $(filter %tuple_arg.hpp %optional_arg.hpp,$(HEADERS))
stdcon17.o: CXXFLAGS += -std=c++17

stdcon.so: stdcon.o stdcon17.o
	$(CXX) $(LDFLAGS) $^ -o $@

test: stdcon.so test.py
	python test.py

