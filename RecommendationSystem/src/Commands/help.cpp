#include "../Commands/help.h"

// Constructor that takes a reference to an IMenu object and initializes m_menu
Help::Help(IMenu& menu) : m_menu(menu) {}

// Method to execute the 'help' command and display available commands to the user
void Help::execute(std::string) {

    std:: string ret = "add [userid] [movieid1] [movieid2]...\nrecommend [userid] [movieid]\nhelp";
    m_menu.displayMessage(ret);
    // Displaying the available commands for the user

}
