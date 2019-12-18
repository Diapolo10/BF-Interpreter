
// C++17

#include <exception>    // std::exception
#include <iostream>     // std::{cin, wcin, cerr, wcerr, cout, wcout}
#include <string>       // std::string
#include <utility>      // std::pair
#include <vector>       // std::vector

#include "interpreter.hpp"  // bf::{Cell, Stack, InterpreterSession}

/* 
 * Useful debug messages, can be toggled
 * on or off by uncommenting/commenting
 * the next line
 */

// #define DEBUG_MODE
#ifdef DEBUG_MODE
#  define DEBUG_LEVEL 1

  // Debugging levels:
  // 1: Most important messages
  // 2: All messages

#  define DEBUG(x) do {std::wcerr << x << std::endl;} while (false)
#  if DEBUG_LEVEL == 2
#    define FULL_DEBUG(x) do {std::wcerr << x << std::endl;} while (false)
#  else
#    define FULL_DEBUG(x) do {} while (false)
#  endif
#else
#  define DEBUG(x) do {} while (false)
#  define FULL_DEBUG(x) do {} while (false)
#endif

using std::string;
using std::vector;

namespace bf {

    wchar_t transform_unicode(Cell c) {
        return wchar_t(c);
    }

    InterpreterSession interpreter(string code) {

        InterpreterSession self {};
        InterpreterSession previous_self {};

        std::cout << "Code to be executed: " << code << "\n" <<std::endl;

        try {

            for (self.idx; self.idx < code.length(); ++self.idx) {

                previous_self = self;
                --previous_self.idx;

                auto instruction {code.at(self.idx)};

                if (self.skip && self.skip_until_depth != self.depth.back()) {
                    FULL_DEBUG("Skipping continues");
                    if (instruction == ']' || instruction == '[') {
                
                    }
                    else {
                        continue;
                    }
                }

                switch (instruction) {
            
                    case '>':
                        op::move_right(self);
                        break;

                    case '<':
                        op::move_left(self);
                        break;

                    case '[':
                        op::enter_loop(self);
                        break;
            
                    case ']':
                        if (op::exit_loop(self)) {
                            continue;
                        }
                        break;
            
                    case '+':
                        op::increment(self);
                        break;
            
                    case '-':
                        op::decrement(self);
                        break;
            
                    case '.':
                        op::print_cell(self);
                        break;
            
                    case ',':
                        op::take_input(self);
                        break;
            
                    default:
                        /* Comment or unsupported language extension */
                        FULL_DEBUG("Unrecognised operator '" << instruction << "'");
                        continue;
                }
            }
        }

        catch (std::exception e) {
            std::wcerr << "An exception has occurred: " << e.what() << "\n\nReturning the last working state before the throw";
            return previous_self;
        }
        return self;
    }

    namespace op {

        void move_right(InterpreterSession& self) {
            ++self.head;
            if (self.head >= self.tape.size()) {
                self.tape.push_back(0);
                FULL_DEBUG("Increased tape size to " << self.tape.size());
            }
            FULL_DEBUG("Moved head right");
        }

        void move_left(InterpreterSession& self) {
            --self.head;
            FULL_DEBUG("Moved head left");
        }

        void increment(InterpreterSession& self) {
            ++self.tape.at(self.head);
            DEBUG("Incremented slot " << self.head << " to " << self.tape.at(self.head));
        }

        void decrement(InterpreterSession& self) {
            --self.tape.at(self.head);
            DEBUG("Decremented slot " << self.head << " to " << self.tape.at(self.head));
        }

        void enter_loop(InterpreterSession& self) {
            DEBUG("Entered loop at depth " << self.depth.back());

            self.stack.push_back(std::pair{ self.head, self.idx });

            if (self.tape.at(self.head) == 0) {
                DEBUG("Skipping loop");
                if (!self.skip) {
                    self.skip = true;
                    self.skip_until_depth = self.depth.back();
                }
            }
            else {
                DEBUG("Stored loop entry point");
            }
            self.depth.push_back(self.depth.back() + 1);
        }

        bool exit_loop(InterpreterSession& self) {
            DEBUG("Reached end of loop at depth " << self.depth.back() - 1);

            if (self.skip && (self.tape.at(self.stack.back().first) == 0)) {

                self.depth.pop_back();

                if (self.skip_until_depth == self.depth.back()) {
                    self.skip = false;
                    DEBUG("Stopped skipping");
                }

                self.stack.pop_back();
                return true;
            }
            else if (self.tape.at(self.stack.back().first) == 0 || self.tape.at(self.head) == 0) {
                self.depth.pop_back();
                self.stack.pop_back();
                DEBUG("Exiting loop");
                return true;
            }
            else {
                self.idx = self.stack.back().second;
            }
            DEBUG("Head now in position " << self.head << " containing value " << self.tape.at(self.head));
            return false;
        }

        void print_cell(InterpreterSession& self) {
            #ifndef DEBUG_MODE
            std::wcout << transform_unicode(self.tape.at(self.head));
            #else
            DEBUG(transform_unicode(self.tape.at(self.head)));
            #endif
            self.printed_chars.push_back(self.tape.at(self.head));
        }

        void take_input(InterpreterSession& self) {
            DEBUG("Taking input from user");
            DEBUG("Input taken: [" << self.input << "]");

            if (!std::wcin) {
                std::wcout << "Input: ";
                std::wcin.get(self.input);
            }
            else {
                std::wcin.get(self.input);
            }

            if (self.input == L'\0' || self.input == L'\n') {
                DEBUG("Input is empty");
                self.tape.at(self.head) = -1;
            }
            else {
                self.tape.at(self.head) = Cell(self.input);
                DEBUG("Cell is " << (int)self.tape.at(self.head));
            }

        }

    }

}
