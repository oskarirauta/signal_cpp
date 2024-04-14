SIGNAL_DIR?=./signal
INCLUDES += -I./$(SIGNAL_DIR)/include

SIGNAL_OBJS:= \
	objs/signal.o

objs/signal.o: $(SIGNAL_DIR)/src/signal.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
