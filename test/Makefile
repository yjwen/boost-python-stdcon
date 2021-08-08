CXXFLAGS += $(shell python-config --cflags) -fPIC -I../include

LDFLAGS += $(shell python-config --ldflags)
LDFLAGS += -lboost_python39 -shared
stdcon.o: stdcon.cpp ../include/vector_arg.hpp ../include/sequence_arg.hpp ../include/list_arg.hpp
stdcon.so: stdcon.o
	$(CXX) $(LDFLAGS) $^ -o $@
test: stdcon.so test.py
	python test.py
