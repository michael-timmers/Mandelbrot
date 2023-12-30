#include <complex>
#include <algorithm>

#include "headers.hpp"
#include "element.hpp"

Element::Element() {
    // z is by defualt 0+0i
    this->mag = 0;
    this->n = 0;
    this->period = 0;
}

void Element::step(std::complex<double> c) {
    this->z = std::pow(this->z, 2) + c;
    this->mag = std::abs(this->z);
    this->n++;
    this->findPatterns();
    this->history[this->n] = this->mag;
}

void Element::findPatterns() {
    this->period = this->n - std::distance(this->history, std::find(this->history, this->history + this->n, this->mag));
}