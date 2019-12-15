#pragma once

// C++17

#include <algorithm>    // std::find
#include <string>       // std::string

namespace bf {

    namespace argparse {

        /* Functions related to parsing launch arguments */

        // Returns the given argument value as a std::string based on the option flag
        std::string get_cmd_option(char** begin, char** end, const std::string& option) {
            auto itr = std::find(begin, end, option);
            if (itr != end && ++itr != end) {
                return *itr;
            }
            return std::string{};
        }

        // Checks if the arguments contain a given option flag
        bool cmd_option_exists(char** begin, char** end, const std::string& option) {
            return std::find(begin, end, option) != end;
        }

    }

}
