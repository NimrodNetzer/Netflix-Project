#ifndef IMENU_H
#define IMENU_H

#include <string>

class IMenu {
public:
    virtual ~IMenu() = default;

    // Method to retrieve the next command ID or input from the user
    virtual int nextCommand() = 0;

    // Method to display error messages
    virtual void displayError(const std::string& message) = 0;

    // Method to get the last input from the user as a string
    virtual const std::string& getLastInput() const = 0;
};

#endif // IMENU_H
