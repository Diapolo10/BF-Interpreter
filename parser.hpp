#pragma once

#include <fstream>
#include <sstream>
#include <string>

namespace bf {
    namespace io {
        /* Reads a file as text and returns its contents as an std::string object */
        std::string read_file(std::string filepath);
    }
}
