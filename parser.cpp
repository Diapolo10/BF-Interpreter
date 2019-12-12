#include <algorithm>     // std::sort
#include <fstream>       // std::ifstream
#include <tuple>         // std::tuple
#include <sstream>       // std::stringstream
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <utility>       // std::pair
#include <vector>        // std::vector

#include "interpreter.hpp" // bf::transform_unicode

namespace bf {
    namespace io {

        std::string read_file(std::string filepath) {

            std::ifstream file(filepath);
            std::stringstream buffer;

            buffer << file.rdbuf();
            file.close();

            return buffer.str();
        }

        void print_tape(std::unordered_map<int, unsigned int> tape) {
            std::vector<std::pair<int, unsigned int>> vec(tape.begin(), tape.end());
            std::sort(vec.begin(), vec.end());
            for (auto& [idx, num] : vec) {
                std::wcout << bf::transform_unicode(num);
            }
        }

        void print_output(bf::InterpreterSession session_output) {
            for (auto num : session_output.printed_chars) {
                std::wcout << bf::transform_unicode(num);
            }
        }
    }
}
