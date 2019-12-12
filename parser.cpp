#include <algorithm>
#include <fstream>
#include <tuple>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "interpreter.hpp"

typedef int Key;
typedef unsigned int Val;

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
            std::vector<std::pair<const Key, Val>> vec(tape.begin(), tape.end());
            std::sort(vec.begin(), vec.end());
            for (auto& [idx, num] : vec) {
                std::wcout << bf::transform_unicode(num);
            }
        }
    }
}
