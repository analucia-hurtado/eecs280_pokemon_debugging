# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

Pokemon_tests.exe: Pokemon_tests.cpp Pokemon.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Trainer_tests.exe: Trainer_tests.cpp Trainer.cpp Pokemon.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

main.exe: main.cpp Trainer.cpp Pokemon.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.SUFFIXES:

.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump