//
// Created by orlib on 02/12/2024.
//

#ifndef MY_TEST_ICOMMAND_H
#define MY_TEST_ICOMMAND_H

#include <string>  // For handling string data

// The ICommand interface defines the contract for all command classes.
// Any class that implements ICommand must provide an implementation for the execute method.
class ICommand {
public:
    // Pure virtual function that all derived classes must implement.
    // This function executes the command with the given arguments.
    virtual void execute(std::string s) = 0;
};

#endif // MY_TEST_ICOMMAND_H
