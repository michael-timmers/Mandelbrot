#pragma once
#include <complex>

#include "headers.hpp"
#include <complex>

class Element {
   public:
    std::complex<double> z;
    double mag;
    int n;
    double history[SEARCH_LIMIT];
    int period;

    Element();

    void step(std::complex<double> c);

   private:
    void findPatterns();
};