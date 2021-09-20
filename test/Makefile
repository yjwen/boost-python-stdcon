CXXFLAGS += $(shell python-config --cflags) -fPIC -I../include

LDFLAGS += $(shell python-config --ldflags)
LDFLAGS += -lboost_python39 -shared

HEADERS = $(wildcard ../include/*.hpp)
C17-HEADER-FILES = tuple_arg.hpp optional_arg.hpp variant_arg.hpp
C17-HEADERS = $(C17-HEADER-FILES:%=../include/%)
RETURN-HEADERS = $(wildcard ../include/*return_value.hpp)
C11-HEADERS = $(filter-out $(C17-HEADERS) $(RETURN-HEADERS),$(HEADERS))
stdcon.o: stdcon.cpp $(C11-HEADERS)

stdcon17.o: stdcon17.cpp $(C17-HEADERS)
stdcon17.o: CXXFLAGS += -std=c++17

mixed.o: mixed.cpp ../include/vector_arg.hpp

combined.o: combined.cpp ../include/vector_arg.hpp ../include/pair_arg.hpp

return_value.o: return_value.cpp $(RETURN-HEADERS)
return_value.o: CXXFLAGS += -std=c++17

stdcon.so: stdcon.o stdcon17.o mixed.o combined.o return_value.o
	$(CXX) $(LDFLAGS) $^ -o $@

test: stdcon.so test.py
	python test.py
