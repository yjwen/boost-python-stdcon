CXXFLAGS += $(shell python-config --cflags) -fPIC -I../include

LDFLAGS += $(shell python-config --ldflags)
LDFLAGS += -lboost_python39 -shared

HEADERS = $(wildcard ../include/*.hpp)
C17-HEADER-FILES = tuple_arg.hpp optional_arg.hpp variant_arg.hpp
C17-HEADERS = $(C17-HEADER-FILES:%=../include/%)
C11-HEADERS = $(filter-out $(C17-HEADERS),$(HEADERS))
stdcon.o: stdcon.cpp $(C11-HEADERS)
stdcon17.o: stdcon17.cpp $(C17-HEADERS)
stdcon17.o: CXXFLAGS += -std=c++17

stdcon.so: stdcon.o stdcon17.o
	$(CXX) $(LDFLAGS) $^ -o $@

test: stdcon.so test.py
	python test.py
