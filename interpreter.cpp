#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <vector>

#include "interpreter.hpp"
#include "parser.hpp"

#define DEBUG_MODE
#ifdef DEBUG_MODE
#  define DEBUG_LEVEL 2

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
using std::unordered_map;

namespace bf {

    wchar_t transform_unicode(Cell c) {
        return wchar_t(c);
    }

    InterpreterSession interpreter(string code) {
    
        vector<Cell> tape {
            0 // By default, the tape only has the starting cell that defaults to zero.
        };
        size_t head {0};         // Current cell
        vector<int> depth {0};   // Current instruction depth
        bool skip {false};       // Ignore next instructions
        int skip_until_depth {}; // Ignore until depth reached
        Stack stack {};
        vector<Cell> printed_chars {};

        code = bf::io::remove_comments(code);
        std::cout << "Code to be executed: " << code << std::endl;

        for (size_t idx {}; idx < code.length(); ++idx) {

            auto instruction {code.at(idx)};

            if (skip && skip_until_depth != depth.back()) {
                FULL_DEBUG("Skipping continues");
                if (instruction == ']' || instruction == '[') {
                
                }
                else {
                    continue;
                }
            }

            switch (instruction) {
            
                case '>':
                    ++head;
                    if (head >= tape.size()) {
                        tape.push_back(0);
                        FULL_DEBUG("Increased tape size to " << tape.size());
                    }
                    FULL_DEBUG("Moved head right");
                    break;

                case '<':
                    --head;
                    FULL_DEBUG("Moved head left");
                    break;

                case '[':
                    DEBUG("Entered loop at depth " << depth.back());
                    
                    stack.push_back(std::pair{ head, idx });

                    if (tape.at(head) == 0) {
                        DEBUG("Skipping loop");
                        if (!skip) {
                            skip = true;
                            skip_until_depth = depth.back();
                        }
                    }
                    else {
                        DEBUG("Stored loop entry point");
                    }
                    depth.push_back(depth.back()+1);
                    break;
            
                case ']':

                    DEBUG("Reached end of loop at depth " << depth.back()-1);

                    if (skip && (tape.at(stack.back().first) == 0)) {

                        depth.pop_back();

                        if (skip_until_depth == depth.back()) {
                            skip = false;
                            DEBUG("Stopped skipping");
                        }

                        stack.pop_back();
                        continue;
                    }
                    else {
                        idx = stack.back().second;
                    }
                    DEBUG("Head now in position " << head);
                    break;
            
                case '+':
                    ++tape.at(head);
                    DEBUG("Incremented slot " << head << " to " << tape.at(head));
                    break;
            
                case '-':
                    --tape.at(head);
                    DEBUG("Decremented slot " << head << " to " << tape.at(head));
                    break;
            
                case '.':
                    DEBUG(transform_unicode(tape.at(head)));
                    printed_chars.push_back(tape.at(head));
                    break;
            
                case ',':
                    DEBUG("Taking input from user");
                    std::cin >> tape.at(head);
                    break;
            
                default:
                    /* Comment or unsupported language extension */
                    FULL_DEBUG("Unrecognised operator");
                    continue;
            }
        }
        return InterpreterSession{tape, printed_chars};
    }

}
