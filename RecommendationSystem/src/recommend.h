#ifndef RECOMMENDATIONSYSTEM_RECOMMEND_H
#define RECOMMENDATIONSYSTEM_RECOMMEND_H

#include <vector>
#include <string>
#include "ICommand.h"
#include "IMenu.h"

// 'recommend' class that implements the ICommand interface
class recommend : public ICommand {
public:
    // Constructor that accepts a reference to an IMenu instance
    explicit recommend(IMenu& menu);

    // Overridden execute method from ICommand interface
    // Takes a string 's' as input, processes it and provides recommendations
    void execute(std::string s) override;

    // Method to validate the input string 's'
    // Ensures that the input follows the expected format
    void validateString(std::string s);

private:
    IMenu& m_menu; // Reference to an IMenu instance, used for interacting with the user interface
};

#endif //RECOMMENDATIONSYSTEM_RECOMMEND_H
