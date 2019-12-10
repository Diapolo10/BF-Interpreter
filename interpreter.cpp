#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::vector;
using std::unordered_map;

namespace bf {

    wchar_t transform_unicode(unsigned int c) {
        return wchar_t(c);
    }

    unordered_map<int, unsigned int> interpreter(string code) {
    
        unordered_map<int, unsigned int> tape {
            (0, 0) // By default, the tape only has the starting cell that defaults to zero.
        };
        int head {0};            // Current cell
        int depth {0};           // Current instruction depth
        bool skip {false};       // Ignore next instructions
        int skip_until_depth {}; // Ignore until depth reached

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
                    break;

                case '<':
                    --head;
                    break;

                case '[':
                    if (tape.at(head) == 0) {
                        skip = true;
                        skip_until_depth = depth;
                    }
                    ++depth;
                    break;
            
                case ']':
                    --depth;
                    if (skip && skip_until_depth == depth) {
                        skip = false;
                        skip_until_depth = 0;
                        continue;
                    }
                    break;
            
                case '+':
                    try {
                        ++tape.at(head);
                    }
                    catch (std::out_of_range) {
                        tape[head] = 1;
                    }
                    break;
            
                case '-':
                    try {
                        --tape.at(head);
                    }
                    catch (std::out_of_range) {
                        tape[head] = -1; // Rolls back to maximum value
                    }
                    break;
            
                case '.':
                    std::cout << transform_unicode(tape.at(head));
                    break;
            
                case ',':
                    std::cin >> tape.at(head);
                    break;
            
                default:
                    /* Comment or unsupported language extension */
                    continue;
            }
        }
        return tape;
    }

}
