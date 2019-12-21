#pragma once

// C++17

#include <string>    // std::string

#include "interpreter.hpp"  // bf::{transform_unicode, InterpreterSession, op::OPERATORS}

namespace bf {

    namespace io {

        /* Contains all input/output-related functions */

        // Clears the program of comments and whitespace, leaving only the operators
        std::string remove_comments(std::string text);

        // Attempts to shorten the program by replacing duplicate operators with an
        // operator and its count as a number.
        //
        // Example:
        // >++++[>++<-].
        // would 'shorten' to
        // >1+4[>1+2<1-1].
        //
        // This is mainly for optimisation, it may in fact increase file sizes in some cases
        std::string shorten(std::string text);

        // Goes through the InterpreterSession struct and either prints out the tape and
        // printed characters, or writes them to a file if the output file path was specified.
        void print_output(InterpreterSession session_output);
        void print_output(InterpreterSession session_output, std::string output_file);

        // Reads a file as text and returns its contents as an std::string object
        std::string read_file(std::string filepath);
    }
}
