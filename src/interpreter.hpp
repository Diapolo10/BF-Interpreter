#pragma once

// C++17

#include <iostream> // std::{cin, wcin, cerr, wcerr, cout, wcout}
#include <set>      // std::set
#include <string>   // std::string
#include <utility>  // std::pair
#include <vector>   // std::vector

namespace bf {

    /* Type declarations */

    // Cells are 8-bit unsigned integers (0-255) on the tape
    typedef uint8_t Cell;

    // Stack is a collection that keeps track of
    // the cells they use for loop conditions and
    // loop entry points (indexes on the code string)
    typedef std::vector<std::pair<int, int>> Stack;

    // Tape is a vector of cells used as memory
    typedef std::vector<bf::Cell> Tape;


    // A struct that keeps track of the interpreter's inner state
    struct InterpreterSession {
        bf::Tape tape {0};          // The memory of the Turing machine
        bf::Tape printed_chars {};  // All values that were set to be printed
        std::vector<int> depth {0}; // Current instruction depth
        bf::Stack stack {};         // Keeps track of loop entry points
        std::size_t head {};        // A 'pointer' to the current memory location
        std::size_t idx {};         // Current instruction index
        wchar_t input{};            // A buffer for user input
        bool skip {false};          // Ignore next instructions
        int skip_until_depth {};    // Ignore until specific depth reached
    };

    /* Functions */

    // Takes a cell from the tape, and returns
    // the respective Unicode character
    wchar_t transform_unicode(Cell c);

    // The main interpreter function, returns the final
    // functioning state of the entire Turing machine
    InterpreterSession interpreter(std::string code);

    namespace op {

        /* A sub-namespace used for operators */

        // A collection of the supported standard operators
        const std::set<unsigned char> OPERATORS { '+', '-', '>', '<', '[', ']', '.', ',' };

        // Move tape pointer right
        void move_right(bf::InterpreterSession& self);

        // Move tape pointer left
        void move_left(bf::InterpreterSession& self);

        // Increment cell at current pointer position,
        // will intentionally overflow at max value
        void increment(bf::InterpreterSession& self);

        // Decrement cell at current pointer position,
        // will intentionally overflow at min value
        void decrement(bf::InterpreterSession& self);

        // Enter a loop and check if the loop condition is true
        // by reading the current cell on the tape (0 is false),
        // if not, skip until the end of the loop
        void enter_loop(bf::InterpreterSession& self);

        // Return to the matching loop entry, or go to
        // next operation and end skipping if skipping ends here
        bool exit_loop(bf::InterpreterSession& self);

        // Mark the current cell value to be printed
        void print_cell(bf::InterpreterSession& self);

        // Store an input character into the current cell
        void take_input(bf::InterpreterSession& self);
    }
}