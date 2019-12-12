#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <vector>

#define DEBUG_MODE
#ifdef DEBUG_MODE
#  define DEBUG_LEVEL 1

  // Debugging levels:
  // 1: Most important messages
  // 2: All messages

#  define DEBUG(x) do {std::wcerr << x << std::endl;} while (false)
#  if DEBUG_LEVEL == 2
#    define FULL_DEBUG(x) do {x} while (false)
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

    struct InterpreterSession {
        unordered_map<int, unsigned int> tape;
        vector<unsigned int> printed_chars;
    };

    wchar_t transform_unicode(unsigned int c) {
        return wchar_t(c);
    }

    InterpreterSession interpreter(string code) {
    
        unordered_map<int, unsigned int> tape {
            {0, 0} // By default, the tape only has the starting cell that defaults to zero.
        };
        int head {0};            // Current cell
        int depth {0};           // Current instruction depth
        bool skip {false};       // Ignore next instructions
        int skip_until_depth {}; // Ignore until depth reached
        vector<std::pair<int, int>> loop_entry_points{};
        vector<unsigned int> printed_chars{};

        for (unsigned int idx {}; idx < code.length(); ++idx) {

            auto instruction {code.at(idx)};

            if (skip && skip_until_depth != depth) {
                if (instruction == ']' || instruction == '[') {
                
                }
                else {
                    continue;
                }
            }

            switch (instruction) {
            
                case '>':
                    ++head;
                    FULL_DEBUG("Moved head right");
                    break;

                case '<':
                    --head;
                    FULL_DEBUG("Moved head left");
                    break;

                case '[':
                    DEBUG("Entered loop at depth " << depth);
                    
                    if (tape.at(head) == 0) {
                        DEBUG("Skipping loop");
                        if (!skip) {
                            skip = true;
                            skip_until_depth = depth;
                        }
                    }
                    else {
                        loop_entry_points.push_back(std::pair{depth, head});
                        DEBUG("Stored loop entry point");
                    }
                    ++depth;
                    break;
            
                case ']':
                    --depth;
                    DEBUG("Reached end of loop at depth " << depth);

                    if (skip && skip_until_depth == depth) {

                        skip = false;
                        skip_until_depth = 0;
                        DEBUG("Stopped skipping");
                        continue;
                    }
                    else {
                        for (auto [dpth, idx] : loop_entry_points) {
                            if (dpth == depth) {
                                head = idx;
                                DEBUG("Moved head to " << head);
                            }
                        }
                    }
                    break;
            
                case '+':
                    try {
                        ++tape.at(head);
                        DEBUG("Incremented slot " << head << " to " << tape.at(head));
                    }
                    catch (std::out_of_range) {
                        tape[head] = 1;
                        DEBUG("Created new slot at " << head << " set to 1");
                    }
                    break;
            
                case '-':
                    try {
                        --tape.at(head);
                        DEBUG("Decremented slot " << head << " to " << tape.at(head));
                    }
                    catch (std::out_of_range) {
                        tape[head] = -1; // Rolls back to maximum value
                        #pragma warning(suppress: 26454)
                        DEBUG("Created new slot at " << head << " set to " << (0U - 1));
                    }
                    break;
            
                case '.':
                    DEBUG(transform_unicode(tape.at(head)));
                    printed_chars.push_back(tape.at(head));
                    break;
            
                case ',':
                    DEBUG("Taking input from user");
                    std::wcin >> tape.at(head);
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
