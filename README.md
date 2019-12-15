# BF-Interpreter
 
An interpreter for the Brainfuck programming language written in C++17

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

You need a C++ compiler compatible with C++17. The code may run on an earlier standard, but it was developed with C++17 in mind. Since the project only uses the standard library, there are no further prerequisites.

It will likely be easiest to use Visual Studio and the MSVC compiler, as that's what the project was developed with.

### Installing

The project should be ready to work as-is, the executable simply needs to be compiled. Download the source code as a ZIP file, unpack it and go to the unpacked directory. All of the source files can be found in the `src`-directory, so simply running a compatible compiler in that directory should be sufficient.

For instance, with the MSVC compiler outside of Visual Studio, you might do (assuming MSVC was on your system path):

```
cl /EHsc file1.cpp file2.cpp file3.cpp /link /out:program1.exe
```

The final program accepts two kinds of arguments, input files and output files. You can omit the output file, in which case the output will only go to the console window.

The program comes with some ready-made example Brainfuck programs in the `test_scripts`-directory. The program is also guaranteed to work with any Brainfuck outputted by [this online service](https://copy.sh/brainfuck/text.html).

```
BF_Interpreter.exe -i "test_scripts/hello_world.bf"
```

```
BF_Interpreter.exe -i "test_scripts/lorem_ipsum.bf" -o "lorem_ipsum.txt"
````

## Deployment

As of right now, no pre-compiled versions of the program are available. Should there be enough demand, I can start uploading pre-compiled versions of the program.

## Built With

* [Visual Studio 2019 Community Edition](https://visualstudio.microsoft.com/vs/) - The IDE used

## Authors

* **Lari Liuhamo** - *Design, development, project management* - [GitHub](https://github.com/Diapolo10)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Urban Müller, the creator of Brainfuck
