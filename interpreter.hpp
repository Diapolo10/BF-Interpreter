#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


namespace bf {
    struct InterpreterSession;
    wchar_t transform_unicode(unsigned int c);
    InterpreterSession interpreter(std::string code);
}