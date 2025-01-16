#ifndef DELETE_H
#define DELETE_H

#include <string>
#include "../Interfaces/ICommand.h"
#include "../Menus/IMenu.h"

class Delete : public ICommand {
public:
    explicit Delete(IMenu& menu);
    void execute(std::string s) override;

private:
    void validateString(const std::string& s);  // Declare validateString here
    IMenu& m_menu;  // Reference to the IMenu instance for user interface interaction
};

#endif // DELETE_H
