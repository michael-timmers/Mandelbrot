#pragma once

#include <memory>

#include "mandelbrot.hpp"

namespace eventHandler {
bool handleInput(const std::unique_ptr<Mandelbrot>& mandelbrot);
}