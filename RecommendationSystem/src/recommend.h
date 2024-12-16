#ifndef RECOMMENDATIONSYSTEM_RECOMMEND_H
#define RECOMMENDATIONSYSTEM_RECOMMEND_H

#include <vector>
#include <string>
#include "ICommand.h"
#include "IMenu.h"

class recommend : public ICommand {
public:
    explicit recommend(IMenu& menu); // Constructor accepting IMenu

    void execute(std::string s) override; // Overridden execute method

    void validateString(std::string s);

private:
    IMenu& m_menu; // Reference to an IMenu instance
};

#endif //RECOMMENDATIONSYSTEM_RECOMMEND_H
