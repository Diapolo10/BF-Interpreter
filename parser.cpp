#include <algorithm>     // std::sort
#include <fstream>       // std::ifstream
#include <tuple>         // std::tuple
#include <set>           // std::set
#include <sstream>       // std::stringstream
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <utility>       // std::pair
#include <vector>        // std::vector

#include "interpreter.hpp" // bf::transform_unicode, bf::InterpreterSession
#include "parser.hpp"

namespace bf {

    namespace io {

        std::string remove_comments(std::string text) {
            std::string result{};

            for (auto chr : text) {
                if (OPERATORS.count(chr)) {
                    result += chr;
                }
            }
            return result;
        }

        std::string read_file(std::string filepath) {

            std::ifstream file(filepath);
            std::stringstream buffer;

            buffer << file.rdbuf();
            file.close();

            return buffer.str();
        }

        void print_output(InterpreterSession session_output) {

            std::wcout << "\n\nTape:\n[";
            for (Cell cell : session_output.tape) {
                std::wcout << cell << ", ";
            }
            std::wcout << "]\n" << std::endl;

            std::wcout << "Output:\n";
            for (auto num : session_output.printed_chars) {
                std::wcout << bf::transform_unicode(num);
            }
            std::wcout << std::endl;
        }
    }
}
