all: world

CXX?=g++
CXXFLAGS?=--std=c++23 -Wall -fPIC
LDFLAGS?=-L/lib -L/usr/lib

INCLUDES+= -I.
SIGNAL_DIR:=.

include common/Makefile.inc
include logger/Makefile.inc
include Makefile.inc

OBJS:= \
	objs/main.o

world: signal-test

objs/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

signal-test: $(COMMON_OBJS) $(LOGGER_OBJS) $(SIGNAL_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -L. $(LIBS) $^ -o $@;

.PHONY: clean
clean:
	rm -f objs/*.o signal-test
