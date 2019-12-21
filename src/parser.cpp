
// C++17

#include <fstream>   // std::ifstream
#include <iostream>  // std::{wcout, endl}
#include <sstream>   // std::stringstream
#include <string>    // std::string

#include "interpreter.hpp"  // bf::{transform_unicode, InterpreterSession, op::OPERATORS}
#include "parser.hpp"       // void

namespace bf {

    namespace io {

        std::string remove_comments(std::string text) {
            std::string result{};

            // Removes all but operator characters
            for (auto chr : text) {
                if (bf::op::OPERATORS.count(chr)) {
                    result += chr;
                }
            }

            // Removes the preceding empty loop comment, if any
            if (result.at(0) == '[') {
                int depth {1};
                for (size_t idx{1}; idx < result.length(); ++idx) {
                    if (result.at(idx) == '[') {
                        ++depth;
                    }
                    else if (result.at(idx) == ']') {
                        --depth;
                        if (depth == 0) {
                            result = result.substr(++idx);
                            break;
                        }
                    }
                }
            }

            return result;
        }

        std::string shorten(std::string text) {

            text = bf::io::remove_comments(text);

            std::string result{};
            size_t count{};

            for (size_t i{}; i < text.length(); ++i) {
                char current {text.at(i)};

                if (current == '+' || current == '-' || current == '<' || current == '>') {
                    ++count;
                }
                else {
                    result += current;
                    continue;
                }

                if (i == text.length()-1 || text.at(i + 1) != current) {
                    result += (current + std::to_string(count));
                    count = 0;
                }
            }

            return result;
        }

        std::string read_file(std::string filepath) {

            std::ifstream file(filepath);
            std::stringstream buffer;

            buffer << file.rdbuf();
            file.close();

            return remove_comments(buffer.str());
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

        void print_output(InterpreterSession session_output, std::string output_file) {

            std::string output;

            output.append("\n\nTape:\n[");
            for (unsigned int cell : session_output.tape) {
                output.append(std::to_string(cell) + ", ");
            }
            output.append("]\n\n");

            output.append("Output:\n");
            for (auto num : session_output.printed_chars) {
                output.append(std::string(1, num));
            }
            output.append("\n");

            std::ofstream file(output_file);
            file << output;
            file.close();
        }
    }
}
