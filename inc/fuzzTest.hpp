#ifndef FUZZ_TEST_HPP_INCLUDED
#define FUZZ_TEST_HPP_INCLUDED

#include "serialismGenerator.hpp"

void launch(size_t numTests, size_t maxConcurrent);
void evaluate(size_t numTests);

#endif