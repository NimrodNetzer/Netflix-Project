#ifndef IMENU_H
#define IMENU_H

#include <string>
#include <vector>

// Abstract base class for menu interface
class IMenu {
public:
    virtual ~IMenu() = default;

    // Pure virtual functions to be implemented by derived classes
    virtual int nextCommand() = 0;
    virtual void displayError(const std::string& message) = 0;
    virtual const std::string& getLastInput() const = 0;
    virtual void displayMessage(const std::string& message) = 0;
    virtual void displayMovieList(const std::vector<int>& movies) = 0;
};

#endif // IMENU_H
