#include <iostream>
#include <fstream>
#include <sstream>

class CodeGenerator
{
public:

    /* Constructor */

    /*  
    *   CodeGenerator
    *   Verifies if the input file has a .vm extension and throws an error if it doesn't.
    *   Stores the output file name for the output assembly code.
    */
    CodeGenerator(std::string);

    /* Methods */

    /*
    *   void generate
    *   generates the assembly code for the given VM command
    *   ignores arg1 and arg2 for commands that do not require them (Arithmetic)
    */
    void generate(COMMAND_TYPE, std::string, std::string, std::string);

private:
    std::string input_file_name;
    std::string output_file_name;
    std::ofstream output_file;
    int line_number;

    /* Methods */

    /*
    *   void writeArithmetic
    *   writes arithmetic command to output file 
    */

    void writeArithmetic(std::string);

    /*
    *   void writePushPop
    *   writes PUSH or POP command to output file 
    */

    void writePushPop(COMMAND_TYPE, std::string, std::string);

    /*
    *   void writeLineToOutputFile
    *   Writes a given string to the output file 
    */

    void writeLineToOutputFile(std::string);

    /*
    *   void getCurrentLineNumber
    *   returns the current line number of VM code being translated 
    */

    std::string getCurrentLineNumber();

    /*
    *   void writeStoreTopTwoElementsInDandM
    *   writes the assembly code for storing top 2 elements in the stack in D and M 
    */

    void writeStoreTopTwoElementsInDandM();

    /*
    *   void writeDtoTOS
    *   writes the assembly code for storing value in D to the Top Of Stack  
    */

    void writeDtoTOS();
};

CodeGenerator::CodeGenerator(std::string input_file_name)
{
    // store the input file name in the object
    this->input_file_name = input_file_name;

    // calculate the length of input file name
    int length_of_input_file_name = this->input_file_name.length();

    // get the last three characters of the input file name
    std::string input_file_extension = this->input_file_name.substr(length_of_input_file_name - 3, length_of_input_file_name - 2);

    if (input_file_extension == ".vm")
    {
        // replace .vm with .asm and store the output file name
        this->output_file_name = this->input_file_name.substr(0, length_of_input_file_name - 3) + ".asm";

        // open the output file for writing
        this->output_file = std::ofstream(this->output_file_name);
    }
    else
    {
        throw std::invalid_argument("Invalid File Extension: Please ensure the file has a .vm extension");
    }

    std::cout << "Code Generator initailized for file: " << this->output_file_name << std::endl;
}

void CodeGenerator::writeLineToOutputFile(std::string line)
{
    this->output_file << line << "\n";
}

std::string CodeGenerator::getCurrentLineNumber()
{
    std::stringstream out;
    out << this->line_number;
    return out.str();
}

void CodeGenerator::generate(COMMAND_TYPE type_of_command, std::string command, std::string arg1, std::string arg2)
{
    this->line_number++;
    switch (type_of_command)
    {
    case (C_ARITHMETIC):
        writeArithmetic(command);
        break;
    case C_PUSH:
    case C_POP:
        if (arg1 == "constant")
        {
            writePushPop(type_of_command, arg1, arg2);
        }
        else
        {
            writeLineToOutputFile("// NOT IMPLEMENTED ERROR: " + command + " " + arg1 + " " + arg2);
        }
        break;
    default:
        break;
    }
    // this->output_file << type_of_command << " " << arg1 << " " << arg2 << "\n";
    std::cout << type_of_command << " " << arg1 << " " << arg2 << "\n";
}

void CodeGenerator::writeArithmetic(std::string command)
{

    writeLineToOutputFile("// " + command);

    if (command == "add" || command == "sub")
    {
        std::string operation = (command == "add") ? "+" : "-";

        // writeStoreTopTwoElementsInDandM
        writeStoreTopTwoElementsInDandM();

        writeLineToOutputFile("D=M" + operation + "D");

        writeDtoTOS();
    }
    else if (command == "eq" || command == "lt" || command == "gt")
    {
        std::string jump_command;

        if (command == "eq")
        {
            jump_command = "JEQ";
        }
        else if (command == "lt")
        {
            jump_command = "JLT";
        }
        else if (command == "gt")
        {
            jump_command = "JGT";
        }

        writeStoreTopTwoElementsInDandM();
        writeLineToOutputFile("D=M-D\n@" + command + "_TRUE_" + getCurrentLineNumber() + "\nD;" + jump_command + "\n@" + command + "_END_" + getCurrentLineNumber() + "\nD=0;JMP\n(" + command + "_TRUE_" + getCurrentLineNumber() + ")\nD=-1\n(" + command + "_END_" + getCurrentLineNumber() + ")");
        writeDtoTOS();
    }
    else if (command == "and" || command == "or")
    {
        std::string logic_command = (command == "and") ? "&" : "|";

        writeStoreTopTwoElementsInDandM();
        writeLineToOutputFile("D=D" + logic_command + "M");
        writeDtoTOS();
    }
    else if (command == "not" || command == "neg")
    {
        std::string unary_operator = (command == "not") ? "!" : "-";

        writeLineToOutputFile("@SP\nA=M-1\nM=" + unary_operator + "M");
    }
    else
    {
        writeLineToOutputFile("// other operation: " + command);
    }
}

void CodeGenerator::writeStoreTopTwoElementsInDandM()
{
    writeLineToOutputFile("@SP");
    writeLineToOutputFile("A=M-1");
    writeLineToOutputFile("D=M");
    writeLineToOutputFile("@SP");
    writeLineToOutputFile("M=M-1");
    writeLineToOutputFile("@SP");
    writeLineToOutputFile("A=M-1");
}

void CodeGenerator::writeDtoTOS()
{
    writeLineToOutputFile("@SP");
    writeLineToOutputFile("A=M-1");
    writeLineToOutputFile("M=D");
}

void CodeGenerator::writePushPop(COMMAND_TYPE type_of_command, std::string memory, std::string value)
{
    switch (type_of_command)
    {
    case (C_PUSH):
        writeLineToOutputFile("// push " + memory + " " + value);
        if (memory == "constant")
        {
            writeLineToOutputFile("@" + value + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1");
        }
        else
        {
            writeLineToOutputFile("// other memory location");
        }
        break;
    case (C_POP):
        writeLineToOutputFile("// pop " + memory + " " + value);
    default:
        break;
    }
}