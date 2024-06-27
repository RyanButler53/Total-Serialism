CXXFLAGS = -std=c++2a -Wall -Wextra -pedantic -g
CXX = clang++

TARGET = totalSerialism
TESTS = analysisMatrix-test serialismGenerator-test

SRCDIR = src/

all: $(TARGET) $(TESTS)

tests: $(TESTS)

analysisMatrix-test: analysisMatrix.o analysisMatrix-test.o 
	$(CXX) -o analysisMatrix-test analysisMatrix.o analysisMatrix-test.o 

serialismGenerator-test: serialismGenerator-test.o serialismGenerator.o analysisMatrix.o
	$(CXX) -o $@ $^

analysisMatrix.o: $(SRCDIR)analysisMatrix.cpp $(SRCDIR)analysisMatrix.hpp $(SRCDIR)matrix.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)analysisMatrix.cpp
	
analysisMatrix-test.o: $(SRCDIR)analysisMatrix-test.cpp  $(SRCDIR)analysisMatrix.hpp $(SRCDIR)matrix.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)analysisMatrix-test.cpp
	
serialismGenerator.o: $(SRCDIR)serialismGenerator.cpp $(SRCDIR)serialismGenerator.hpp $(SRCDIR)analysisMatrix.hpp 
	$(CXX) $(CXXFLAGS) -c $< 

serialismGenerator-test.o: $(SRCDIR)serialismGenerator-test.cpp $(SRCDIR)serialismGenerator.hpp $(SRCDIR)analysisMatrix.hpp
	$(CXX) $(CXXFLAGS) -c $<

totalSerialism: totalSerialism.o analysisMatrix.o serialismGenerator.o
	$(CXX) -o $@ $^

totalSerialism.o: $(SRCDIR)totalSerialism.cpp $(SRCDIR)analysisMatrix.hpp $(SRCDIR)serialismGenerator.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean: 
	rm -rf *.o $(TARGET) $(TESTS)

