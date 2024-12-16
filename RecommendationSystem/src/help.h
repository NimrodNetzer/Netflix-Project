#ifndef HELP_H
#define HELP_H

#include "ICommand.h"  // Include the ICommand interface for command functionality
#include "IMenu.h"     // Include the IMenu interface for menu interaction

// The Help class inherits from ICommand and provides functionality for the 'help' command
class Help : public ICommand {
public:
    // Constructor that accepts a reference to an IMenu instance
    explicit Help(IMenu& menu);

    // Override the execute method from ICommand to display help information
    void execute(std::string s) override;

private:
    IMenu& m_menu; // Reference to an IMenu instance, used for displaying messages
};

#endif // HELP_H
