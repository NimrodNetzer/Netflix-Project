#include "help.h"

Help::Help(IMenu& menu) : m_menu(menu) {}

void Help::execute(std::string) {
    m_menu.displayMessage("add [userid] [movieid1] [movieid2]...");
    m_menu.displayMessage("recommend [userid] [movieid]");
    m_menu.displayMessage("help");
}
