
#include "Data/DataManager.h"
#include <iostream>
#include <memory> // For smart pointers
#include "Menus/ConsoleMenu.h"
#include "Interfaces/ICommand.h"
#include "Commands/add.h"
#include "Core/app.h"
#include "Commands/help.h"
#include <map>
#include <vector>
#include "Interfaces/IPersistence.h"
#include "Data/FilePersistence.h"
#include "Commands/recommendAlgo.h"
#include "Commands/recommend.h"
#include "Commands/post.h"
#include "Commands/patch.h"
#include "Commands/Delete.h"
#include "Server/Server.h"


int main() {
    IPersistence* persistence = new FilePersistence("data");
    DataManager& data_manager = DataManager::getInstance();
    data_manager.setPersistenceStrategy(persistence);
    data_manager.load();
    Server server;
    server.run();
    delete persistence;
    return 0;
}


