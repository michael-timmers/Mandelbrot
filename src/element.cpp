#include <algorithm>

#include "headers.hpp"
#include "element.hpp"

Element::Element() {
    this->z_x = 0, this->z_y = 0;
    this->mag = 0;
    this->n = 0;
    this->period = 0;
}

void Element::step(double c_x, double c_y) {
    // z=z^2+c
    double newZ_x = (this->z_x * this->z_x - this->z_y * this->z_y) + c_x;
    this->z_y = (2 * this->z_x * this->z_y) + c_y;
    this->z_x = newZ_x;

    this->mag = std::sqrt(this->z_x * this->z_x + this->z_y * this->z_y);

    this->n++;
    this->findPatterns();
    this->history[this->n] = this->mag;
}

void Element::findPatterns() {
    this->period = this->n - std::distance(this->history, std::find(this->history, this->history + this->n, this->mag));
}