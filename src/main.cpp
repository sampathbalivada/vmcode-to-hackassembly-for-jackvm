#include <iostream>
#include "parser.h"
#include "code_generator.h"

int main(int argc, char **argv)
{
    std::cout << "VM Translator for Jack Language!" << std::endl;
    Parser parser = Parser(argv[1]);
    CodeGenerator code_generator = CodeGenerator(argv[1]);
    while (parser.hasMoreCommands()) {
        parser.advance();
        code_generator.generate(parser.commandType(), parser.currentCommand(), parser.arg1(), parser.arg2());
    }
    return 0;
}