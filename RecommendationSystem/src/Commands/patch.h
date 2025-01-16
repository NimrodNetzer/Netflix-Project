#ifndef PATCH_H
#define PATCH_H

#include <vector>
#include <string>
#include "Interfaces/ICommand.h"
#include "Menus/IMenu.h"

// 'recommend' class that implements the ICommand interface
class patch : public ICommand {
public:
    // Constructor that accepts a reference to an IMenu instance
    explicit patch(IMenu& menu);

    // Overridden execute method from ICommand interface
    // Takes a string 's' as input, processes it and provides recommendations
    void execute(std::string s) override;


private:
    IMenu& m_menu; // Reference to an IMenu instance, used for interacting with the user interface
};

#endif //RECOMMENDATIONSYSTEM_RECOMMEND_H
