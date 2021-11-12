#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

enum COMMAND_TYPE
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
    /* Constructor */

    /*  
    *   Parser 
    *   Opens the input file and get it ready for parsing
    */

    Parser(std::string);

    /* Methods */

    /*
    *   bool hasMoreCommands()
    *   returns true if there are more lines to be parsed returns false otherwise
    */

    bool hasMoreCommands();

    /*
    *   void advance()
    *   moves the parser to next line if there are more lines 
    */

    void advance();

    /*
    *   COMMAND_TYPE commandType()
    *   returns the type of command for the current line
    */

    COMMAND_TYPE commandType();

    /*
    *   std::string currentCommand()
    *   returns the command in the current line 
    */
    std::string currentCommand();

    /*
    *   void arg1()
    *   returns the first argument for the command 
    */

    std::string arg1();

    /*
    *   void arg2()
    *   returns the second argument for the command
    */

    std::string arg2();

private:
    std::string _file_location;
    std::ifstream _file_reader = std::ifstream();
    
    /*  
    *   current line number in vm_code being parsed
    *   cannot use size_t as it is an unsigned type
    */
    int current_line = -1;
    
    COMMAND_TYPE _command_type;
    std::string _command;
    std::string _arg1;
    std::string _arg2;
    std::vector<std::string> vm_code;

    /* Methods */

    /*
    *   std::string trimfnc()
    *   returns a string after removing whitespaces and special characters '\t\n\r\f\v' from the start and end of the string
    */
    
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

bool Parser::hasMoreCommands()
{
    /* 
    *  cannot comapre size_t and int as size_t is unsigned and int is signed.
    *  typecasted size_t to int
    */

    return this->current_line < (int)vm_code.size() - 1;
}

void Parser::advance()
{
    /*
    *  check if the parser has more commands to parse
    *  and move to the next line of command
    */

    if (hasMoreCommands())
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

        // create a string stream to tokenize
        std::istringstream line_of_code(this->vm_code[this->current_line]);

        // extract tokens from stream
        // store tokens in _command, _arg1 and _arg2
        line_of_code >> this->_command >> this->_arg1 >> this->_arg2;

        // determine the type of command
        COMMAND_TYPE type;

        // TODO: [Week 2] Implement recognition for other types of commands

        if (this->_command == "push")
        {
            type = C_PUSH;
        }
        else if (this->_command == "pop")
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

COMMAND_TYPE Parser::commandType()
{
    return this->_command_type;
}

std::string Parser::currentCommand()
{
    return this->_command;
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