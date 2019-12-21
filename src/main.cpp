
// C++17

#include <iostream> // std::{cin, cout, cerr, wcin, wcout, wcerr}
#include <string>   // std::string
#include <locale>   // std::locale

#include "interpreter.hpp"  // bf::interpreter
#include "parser.hpp"       // bf::{read_file, print_output}
#include "transpiler.hpp"   // bf::io::generate_c
#include "util.hpp"         // bf::argparse::{get_cmd_option, cmd_option_exists}

int main(int argc, char* argv[]) {

    // This sets the "global" locale to the default locale. 
    (void)std::locale::global(std::locale(""));

    // The various standard io streams were initialized before main started,
    // so they are all configured with the default global locale, std::locale("C").
    // If we want them to behave in a locale-aware manner, including using the
    // hopefully correct encoding for output, we need to "imbue" each iostream
    // with the default locale.
    auto current_locale = std::locale();

    (void)std::cin.imbue(current_locale);
    (void)std::cout.imbue(current_locale);
    (void)std::cerr.imbue(current_locale);
    (void)std::wcin.imbue(current_locale);
    (void)std::wcout.imbue(current_locale);
    (void)std::wcerr.imbue(current_locale);

    // Default options
    std::string input_file {"test_scripts/hello_world.bf"};
    std::string output_file {};
    std::string mode {"interpreter"};

    // Parse arguments passed from the command line, if any

    // Input file path
    if (bf::argparse::cmd_option_exists(argv, argv + argc, "-f")) {
        input_file = bf::argparse::get_cmd_option(argv, argv + argc, "-f");
    }

    // Output file path
    if (bf::argparse::cmd_option_exists(argv, argv + argc, "-o")) {
        output_file = bf::argparse::get_cmd_option(argv, argv + argc, "-o");
    }

    // Mode
    if (bf::argparse::cmd_option_exists(argv, argv + argc, "-m")) {
        mode = bf::argparse::get_cmd_option(argv, argv + argc, "-m");
    }

    std::string brainfuck = bf::io::read_file(input_file);

    if (mode == "transpiler") {
        std::cout << bf::io::generate_c(brainfuck) << std::endl;
    }


    auto result = bf::interpreter(brainfuck);

    // If an output file was declared, write the output to it, including the tape
    if (output_file == "") {
        bf::io::print_output(result);
    }
    else {
        bf::io::print_output(result, output_file);
    }

    return 0;
}
