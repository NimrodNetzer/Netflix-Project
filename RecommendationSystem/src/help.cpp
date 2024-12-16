#include "help.h"

// Constructor that takes a reference to an IMenu object and initializes m_menu
Help::Help(IMenu& menu) : m_menu(menu) {}

// Method to execute the 'help' command and display available commands to the user
void Help::execute(std::string) {
    // Displaying the available commands for the user
    m_menu.displayMessage("add [userid] [movieid1] [movieid2]..."); // Command to add movie recommendations
    m_menu.displayMessage("recommend [userid] [movieid]");           // Command to get a movie recommendation for a user
    m_menu.displayMessage("help");                                   // Command to display help (this one itself)
}
