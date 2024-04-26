# Calculator

### A Calculator program made with C++

This is a personal project to make my maths homework easier and for fun. This calculator can:

* Store Variables
* Calculate solutions
* Read variables and store them from a `.txt` file
* Compile on Windows, Linux && Mac (Maybe BSD?)

# Instructions:

## Prerequisites:
* You must have a C++ compiler, eg GNU C/C++ Compiler
* You can use an external Expression Parser eg. `ExprTk`.

## The guide:

**(1)** Clone the repo to a directory on you computer, eg.

```C:\Program Files (x86)\Microsoft\Temp```

```~/Downloads```

**(2)** Extract the zip so you are left with:

**You can remove everything but these**

**Minimum Things you NEED:**
```
calculator:
/
|
\--->src
|   \--->main.cpp
|
\--->muparser
    \---> (ALL MUPARSER HEADERS)
    |
    \---> (ALL MUPARSER CPP FILES)

```
<details>
<summary>**(2.5)** How to use another parser </summary>
 If you want to use another parser, you just need to change one function, the parseStringMap() function. For example, here is the same program using the `ExprTk` parser.

```c++
#include <string>
#include <map>
#include <cmath>
#include <iostream>
#include "exprtk.hpp"

double parseStringMap(const std::string& equation, const std::map<std::string, double>& variables) {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    try {
        symbol_table_t symbol_table;
        expression_t expression;
        parser_t parser;

        for (const auto& pair : variables) {
            symbol_table.add_variable(pair.first, pair.second);
        }

        expression.register_symbol_table(symbol_table);
        parser.compile(equation, expression);

        return expression.value();
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
        return NAN;
    }
}
```
</details>

**(3)** Now you can compile it (muParser)

 Do `g++ -std=c++17 -o main src/main.cpp muparser/muParser.cpp muparser/muParserBase.cpp muparser/muParserBytecode.cpp muparser/muParserCallback.cpp muparser/muParserError.cpp muparser/muParserTokenReader.cpp`
to include all the libraries

**(4)** Now run the binary.

***

## Usage:
### The program says all. No need for me to explain.
