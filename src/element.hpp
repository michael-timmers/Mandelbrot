#pragma once

#include "headers.hpp"

class Element {
   public:
    double z_x;
    double z_y;
    double mag;
    int n;
    double history[SEARCH_LIMIT];
    int period;

    Element();

    void step(double c_x, double c_y);

   private:
    void findPatterns();
};