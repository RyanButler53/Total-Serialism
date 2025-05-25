#ifndef FUZZ_TEST_HPP_INCLUDED
#define FUZZ_TEST_HPP_INCLUDED

#include "serialismGenerator.hpp"
#include "threadPool.hpp"

/**
 * @brief Launches threads to execute numTests fuzz tests
 * Note that each thread calls a lilypond process. 
 * Evaluates the test results
 * @param numTests Number of tests
 * @param maxConcurrent Max number of threads to use. 
 */
void fuzzTest(size_t numTests, size_t maxConcurrent);

/**
 * @brief Function executed by each thread
 * 
 * @param seed 
 */
bool threadFunc(int seed);

#endif