#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

enum commandType
{
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL
};

class Parser
{
public:
    // Constructor:
    // Open the input file and get it ready for parsing
    Parser(std::string file_location);

    // Methods
    // has_more_commands
    bool has_more_commands();
    // advance
    void advance();
    // command_type
    commandType command_type();
    // arg1
    std::string arg1();
    // arg2
    std::string arg2();

private:
    // store the file location
    std::string _file_location;
    // store the file reader
    std::ifstream _file_reader = std::ifstream();
    // current line
    int current_line;
    // store the command type
    commandType _command_type;
    // value of the first argument in the command
    std::string _arg1;
    // value of the second argument in the command
    std::string _arg2;
    // store the entire file as array of strings
    std::vector<std::string> vm_code;

    std::string trimfnc(std::string);
};

Parser::Parser(std::string file_location)
{
    std::cout << "Parser Created for file: " << file_location << std::endl;

    // initialize file reader
    this->_file_reader.open(file_location);

    // store all the lines in vm_code vector
    std::string line;

    while (std::getline(this->_file_reader, line))
    {
        vm_code.push_back(line);
    }

    // close the file
    this->_file_reader.close();
}

bool Parser::has_more_commands()
{
    return current_line < vm_code.size() - 1;
}

void Parser::advance()
{
    // check if the parser has more commands to parse
    // and move to the next line of command

    if (has_more_commands())
    {
        do
        {
            this->current_line++;

            // find and remove comments from the line
            size_t comments_pos = this->vm_code[this->current_line].find("//");
            if (comments_pos != std::string::npos)
            {
                this->vm_code[this->current_line] = this->vm_code[this->current_line].substr(0, comments_pos);
            }

            // remove spaces from the start and end
            this->vm_code[this->current_line] = trimfnc(this->vm_code[this->current_line]);

        } while (this->vm_code[this->current_line] == "");

        // Debug:
        // std::cout << this->vm_code[this->current_line] << "\n";

        // create a string stream to tokenize
        std::istringstream line_of_code(this->vm_code[this->current_line]);

        std::string command;

        line_of_code >> command >> this->_arg1 >> this->_arg2;

        // Debug:
        // std::cout << command << this->_arg1 << this->_arg2 << "\n";

        // determine the type of command
        commandType type;

        // C_ARITHMETIC,
        // C_PUSH,
        // C_POP,
        // C_LABEL,
        // C_GOTO,
        // C_IF,
        // C_FUNCTION,
        // C_RETURN,
        // C_CALL

        // TODO: [Week 2] Implement recognition for other types of commands

        if (command == "push")
        {
            type = C_PUSH;
        }
        else if (command == "pop")
        {
            type = C_POP;
        }
        else
        {
            type = C_ARITHMETIC;
        }

        this->_command_type = type;
    }
    else
    {
        return;
    }
}

commandType Parser::command_type()
{
    return this->_command_type;
}

std::string Parser::arg1()
{
    return this->_arg1;
}

std::string Parser::arg2()
{
    return this->_arg2;
}

std::string Parser::trimfnc(std::string str)
{
    const char *typeOfWhitespaces = " \t\n\r\f\v";
    str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
    str.erase(0, str.find_first_not_of(typeOfWhitespaces));
    return str;
}