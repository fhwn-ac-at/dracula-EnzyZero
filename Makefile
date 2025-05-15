CC = clang++
CXXFLAGS += -Wall -Wextra -Werror --std=c++23 -ggdb

pfusch: pfusch.cpp

clean:
	rm -f pfusch *.o

.PHONY: clean
