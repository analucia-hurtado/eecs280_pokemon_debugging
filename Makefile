# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Run a regression test
test: Pokemon_tests.exe Trainer_tests.exe main.exe

	./Pokemon_tests.exe
	./Trainer_tests.exe
	./main.exe ash.txt indigo_league.txt > main.out
	diff -qB main.out main.out.correct

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