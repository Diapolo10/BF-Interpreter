#pragma once

// C++17

#include <iostream> // std::{cin, wcin, cerr, wcerr, cout, wcout}
#include <string>   // std::string
#include <utility>  // std::pair
#include <vector>   // std::vector


namespace bf {

    typedef uint8_t Cell;
    typedef std::vector<std::pair<int, int>> Stack; // std::pair<Head, Idx>
    typedef std::vector<bf::Cell> Tape;


    struct InterpreterSession {
        bf::Tape tape {0};          // The memory of the Turing machine
        bf::Tape printed_chars {};  // All values that were set to be printed
        std::vector<int> depth {0}; // Current instruction depth
        bf::Stack stack {};         // Keeps track of loop entry points
        std::string input {};       // A buffer for user input
        std::size_t head {};        // A 'pointer' to the current memory location
        std::size_t idx {};         // Current instruction index
        bool skip {false};          // Ignore next instructions
        int skip_until_depth {};    // Ignore until specific depth reached
    };
    wchar_t transform_unicode(Cell c);
    InterpreterSession interpreter(std::string code);

    namespace op {
        void move_right(bf::InterpreterSession& self);
        void move_left(bf::InterpreterSession& self);
        void increment(bf::InterpreterSession& self);
        void decrement(bf::InterpreterSession& self);
        void enter_loop(bf::InterpreterSession& self);
        bool exit_loop(bf::InterpreterSession& self);
        void print_cell(bf::InterpreterSession& self);
        void take_input(bf::InterpreterSession& self);
    }
}