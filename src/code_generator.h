#include <iostream>
#include "parser.h"

class CodeGenerator
{
public:
    CodeGenerator(std::string input_file_name);

private:
    std::string input_file_name;
    std::string output_file_name;
};

CodeGenerator::CodeGenerator(std::string input_file_name)
{
    // store the input file name in the object
    this->input_file_name = input_file_name;

    // calculate the length of input file name
    int length_of_input_file_name = this->input_file_name.length();

    // check for the .vm extension
    std::string input_file_extension = this->input_file_name.substr(length_of_input_file_name - 3, length_of_input_file_name - 2);

    if (input_file_extension == ".vm")
    {
        // replace .vm with .asm and store the file name in the object
        this->output_file_name = this->input_file_name.substr(0, length_of_input_file_name - 3) + ".asm";
    }
    else
    {
        throw std::invalid_argument("Please rename the file to have a .vm extension");
    }

    std::cout << "Code Generator initailized for file: " << this->output_file_name << std::endl;

    // this->output_file_name =
}