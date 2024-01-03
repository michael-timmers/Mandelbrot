#pragma once

namespace utils {

// a console output
void intro();

// initialises all SDL and TTF variables
int init();

void run(bool runProfiling = false);

// destroys all variables from SDL and TTF
void kill();
}  // namespace utils