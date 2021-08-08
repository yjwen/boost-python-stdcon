CXXFLAGS += $(shell python-config --cflags) -fPIC -I../include

LDFLAGS += $(shell python-config --ldflags)
LDFLAGS += -lboost_python39 -shared
stdcon.o: stdcon.cpp
stdcon.so: stdcon.o
	$(CXX) $(LDFLAGS) $^ -o $@
test: stdcon.so test.py
	python test.py
