#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


namespace bf {
    struct InterpreterSession {
        std::unordered_map<int, unsigned int> tape;
        std::vector<unsigned int> printed_chars;
    };
    wchar_t transform_unicode(unsigned int c);
    InterpreterSession interpreter(std::string code);
}