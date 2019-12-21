#include <string>

#include "parser.hpp"
#include "transpiler.hpp"

namespace bf {
    namespace io {

        std::string generate_c(std::string bf_code) {

            auto code = bf::io::shorten(bf_code);
            const int MAX_ARRAY_SIZE = 10'000;
            int count{};
            int depth{};
            int indentation_level{};

            std::string result {
                "#include <stdio.h>\n"
                "#include <stdlib.h>\n"
                "\n"
                "const int MAX_ARRAY_SIZE = "
            };

            result.append(std::to_string(MAX_ARRAY_SIZE));

            result.append(
                ";\n"
                "\n"
                "int main(void) {\n\n"
                "    char tape[MAX_ARRAY_SIZE];\n"
                "    tape[0] = 0;\n"
                "    char *ptr = tape;\n"
                "    \n"
                "    // The BF program starts here:\n"
            );

            for (size_t op{}; op < code.length(); ++op) {
                auto current = code.at(op);
                count = 0;

                if (current == '+' || current == '-' || current == '<' || current == '>') {
                    char digit {};
                    std::string digits {};
                    
                    // Gets the compacted operator count regardless of how many digits it has
                    for (size_t idx{op+1}; idx < code.length(); ++idx) {
                        digit = code.at(idx);
                        if ('0' <= digit && digit <= '9') {
                            digits.append(std::to_string(digit-'0')); // The "-'0'" is needed to get the real digit value
                        }
                        else {
                            count = std::stoi(digits);
                            op += digits.length(); // Corrects the next operator to continue from the last digit
                            break;
                        }
                    }

                }
                else if (current == ']') {
                    --depth;
                }

                // Adds correct indentation level
                indentation_level = 4*(depth+1);
                result.append(std::string("    ", indentation_level));

                switch (current) {
                    case '+':
                        // *ptr += count;
                        result.append("*ptr += ");
                        result.append(std::to_string(count));
                        result.append(";\n");
                        break;
                    case '-':
                        // *ptr -= count;
                        result.append("*ptr -= ");
                        result.append(std::to_string(count));
                        result.append(";\n");
                        break;
                    case '>':
                        // ptr += count;
                        result.append("ptr += ");
                        result.append(std::to_string(count));
                        result.append(";\n");
                        break;
                    case '<':
                        // ptr -= count;
                        result.append("ptr -= ");
                        result.append(std::to_string(count));
                        result.append(";\n");
                        break;
                    case '[':
                        // while (*ptr) {
                        result.append("while (*ptr) {\n");
                        ++depth;
                        break;
                    case ']':
                        // }
                        result.append("}\n");
                        break;
                    case '.':
                        // putchar(*ptr);
                        result.append("putchar(*ptr);\n");
                        break;
                    case ',':
                        // *ptr = getchar();
                        result.append("*ptr = getchar();\n");
                        break;
                    default:
                        // To increase error tolerance
                        break;
                }
            }

            result.append(
                "    \n"
                "    return 0;\n"
                "}\n"
            );

            return result;
        }
    }
}