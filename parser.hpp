#pragma once

#include <fstream>
#include <sstream>
#include <string>

namespace bf {
    namespace io {

        std::string remove_comments(std::string text);

        void print_tape(std::unordered_map<int, unsigned int> tape);

        void print_output(bf::InterpreterSession session_output);

        /* Reads a file as text and returns its contents as an std::string object */
        std::string read_file(std::string filepath);
    }
}
