#include <chrono>

using namespace std::chrono;

namespace timer {
time_point<high_resolution_clock, nanoseconds> first;
time_point<high_resolution_clock, nanoseconds> last;

void start() {
    first = high_resolution_clock::now();
}

void stop() {
    last = high_resolution_clock::now();
}

nanoseconds result() {
    return duration_cast<nanoseconds>(last - first);
}

}  // namespace timer