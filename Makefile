CXXFLAGS = -std=c++2a -Wall -Wextra -pedantic -g
CXX = clang++

TARGET = totalSerialism
TESTS = analysisMatrix-test serialismGenerator-test

all: $(TARGET) $(TESTS)

tests: $(TESTS)

analysisMatrix-test: analysisMatrix.o analysisMatrix-test.o 
	$(CXX) -o analysisMatrix-test analysisMatrix.o analysisMatrix-test.o 

serialismGenerator-test: serialismGenerator-test.o serialismGenerator.o analysisMatrix.o
	$(CXX) -o $@ $^

analysisMatrix.o: analysisMatrix.cpp analysisMatrix.hpp
	$(CXX) $(CXXFLAGS) -c analysisMatrix.cpp
	
analysisMatrix-test.o: analysisMatrix-test.cpp  analysisMatrix.hpp matrix.hpp
	$(CXX) $(CXXFLAGS) -c analysisMatrix-test.cpp
	
serialismGenerator.o: serialismGenerator.cpp serialismGenerator.hpp analysisMatrix.hpp 
	$(CXX) $(CXXFLAGS) -c $< 

serialismGenerator-test.o: serialismGenerator-test.cpp serialismGenerator.hpp analysisMatrix.hpp
	$(CXX) $(CXXFLAGS) -c $<

totalSerialism: totalSerialism.o analysisMatrix.o serialismGenerator.o
	$(CXX) -o $@ $<

totalSerialism.o: totalSerialism.cpp analysisMatrix.hpp serialismGenerator.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean: 
	rm -rf *.o $(TARGET) $(TESTS)

