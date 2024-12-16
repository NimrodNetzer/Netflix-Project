#ifndef HELP_H
#define HELP_H

#include "ICommand.h"
#include "IMenu.h"

class Help : public ICommand {
public:
    explicit Help(IMenu& menu); // Constructor accepting IMenu

    void execute(std::string s) override;

private:
    IMenu& m_menu; // Reference to an IMenu instance
};

#endif // HELP_H
