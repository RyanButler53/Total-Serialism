#ifndef FUZZ_TEST_HPP_INCLUDED
#define FUZZ_TEST_HPP_INCLUDED

#include "serialismGenerator.hpp"
#include "threadPool.hpp"

/**
 * @brief Launches threads to execute numTests fuzz tests
 * Note that each thread calls a lilypond process
 * @param numTests Number of tests
 * @param maxConcurrent Max number of threads to use. 
 */
void launch(size_t numTests, size_t maxConcurrent);

/**
 * @brief Evaluates if the test passed by checking if the lilypond
 * error log is empty. 
 * 
 * @param numTests Number of tests to check. 
 */
void evaluate(size_t numTests);

/**
 * @brief Function executed by each thread
 * 
 * @param seed 
 */
void threadFunc(int seed);

#endif