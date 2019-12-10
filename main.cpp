#include <iostream>
#include <locale>

// #include "interpreter.hpp"

int main(int argc, char** argv) {

    // From https://stackoverflow.com/a/23466097

    // std::locale()   is the "global" locale
    // std::locale("") is the locale configured through the locale system
    // At startup, the global locale is set to std::locale("C"), so we need
    // to change that if we want locale-aware functions to use the configured
    // locale.
    // This sets the global" locale to the default locale. 
    auto _ = std::locale::global(std::locale(""));

    // The various standard io streams were initialized before main started,
    // so they are all configured with the default global locale, std::locale("C").
    // If we want them to behave in a locale-aware manner, including using the
    // hopefully correct encoding for output, we need to "imbue" each iostream
    // with the default locale.
    auto current_locale = std::locale();

    (void)std::cin.imbue(current_locale);
    auto foo = std::cout.imbue(current_locale);
    std::cerr.imbue(current_locale);
    std::wcin.imbue(current_locale);
    std::wcout.imbue(current_locale);
    std::wcerr.imbue(current_locale);

    // You can't write a wchar_t to cout, because cout only accepts char. wcout, on the
    // other hand, accepts both wchar_t and char; it will "widen" char. So it's
    // convenient to use wcout:

    std::wcout << wchar_t(225) << std::endl;
    std::wcout << wchar_t(960) << std::endl;
    return 0;
}
