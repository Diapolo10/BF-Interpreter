#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


namespace bf {
    wchar_t transform_unicode(unsigned int c);
    std::unordered_map<int, unsigned int> interpreter(string code);
}