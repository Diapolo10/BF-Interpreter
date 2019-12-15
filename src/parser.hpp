#pragma once

#include <fstream>
#include <set>
#include <sstream>
#include <string>

#include "interpreter.hpp"

namespace bf {

    const std::set<unsigned char> OPERATORS{ '+', '-', '>', '<', '[', ']', '.', ',' };

    namespace io {

        std::string remove_comments(std::string text);

        void print_output(InterpreterSession session_output);

        /* Reads a file as text and returns its contents as an std::string object */
        std::string read_file(std::string filepath);
    }
}
