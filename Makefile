#declare the variable
CXX = g++

CXXFLAGS = -c -Wall

all: project1

project1:   project1_functions.o project1_test.o project1_demo.o
	$(CXX) project1_functions.o project1_test.o project1_demo.o -o project1

project1_test.o: project1_test.cpp project1_functions.h
	$(CXX) $(CXXFLAGS) project1_test.cpp

project1_functions.o: project1_functions.cpp project1_functions.h
	$(CXX) $(CXXFLAGS) project1_functions.cpp

project1_demo.o: project1_demo.cpp project1_functions.h
	$(CXX) $(CXXFLAGS) project1_demo.cpp

clean:
	rm -rf *o project1 
