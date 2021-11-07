#include <iostream>
#include "code_generator.h"

int main(int argc, char **argv)
{
    std::cout << "VM Translator for Jack Language!" << std::endl;
    Parser parser = Parser(argv[1]);
    CodeGenerator code_generator = CodeGenerator(argv[1]);
    while (parser.has_more_commands()) {
        parser.advance();
        std::cout << parser.command_type() << " " << parser.arg1() << " " << parser.arg2() << "\n";
    }
    return 0;
}