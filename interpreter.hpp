#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


namespace bf {

    typedef uint8_t Cell;
    // std::pair<Head, Idx>
    typedef std::vector<std::pair<int, int>> Stack;


    struct InterpreterSession {
        std::vector<bf::Cell> tape;
        std::vector<bf::Cell> printed_chars;
    };
    wchar_t transform_unicode(Cell c);
    InterpreterSession interpreter(std::string code);
}