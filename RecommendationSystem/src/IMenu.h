#ifndef IMENU_H
#define IMENU_H

#include <string>

class IMenu {
public:
    virtual ~IMenu() = default;

    virtual int nextCommand() = 0;             // Get the next command ID
    virtual void displayError(const std::string& message) = 0; // Display error messages
};

#endif // IMENU_H
