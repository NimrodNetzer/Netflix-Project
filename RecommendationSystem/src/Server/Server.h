//
// Created by ido on 12/17/24.
//

#ifndef SERVER_H
#define SERVER_H

#include <map>
#include "Interfaces/ICommand.h"
#include "Menus/IMenu.h"
#include "Menus/SocketMenu.h"

#


class Server {
    public:
      void run();
      void handleClient(int client_sock);

private:
    std::map<std::string, ICommand*> initializeCommands(IMenu& menu);

};



#endif //SERVER_H
