#pragma once

#include <chrono>

namespace timer {
void start();
void stop();
std::chrono::nanoseconds result();

}  // namespace timer