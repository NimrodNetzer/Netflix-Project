//
// Created by orlib on 02/12/2024.
//

#ifndef MY_TEST_ICOMMAND_H
#define MY_TEST_ICOMMAND_H


#include <string>

class ICommand {
public:
    virtual void execute(std::string s) = 0;
};


#endif //MY_TEST_ICOMMAND_H
