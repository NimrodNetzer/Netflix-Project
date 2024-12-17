#ifndef MY_TEST_PATCH_H
#define MY_TEST_PATCH_H

#include <string>
#include "Interfaces/ICommand.h"

class patch : public ICommand {
public:
    patch();

    // Execute function now includes the socket for client communication
    void execute(std::string s, int clientSocket) override;

    // Input validation method
    void validateString(std::string s);
};

#endif // MY_TEST_PATCH_H
