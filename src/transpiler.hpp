#pragma once

// C++17

#include <string>

#include "parser.hpp"

namespace bf {
    namespace io {
        // Generates C code equivalent to the given Brainfuck program
        std::string generate_c(std::string bf_code);
    }
}