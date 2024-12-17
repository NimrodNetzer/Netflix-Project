//
// Created by ido on 12/17/24.
//

#ifndef SERVER_H
#define SERVER_H



class Server {
    public:
      void run();
      void handleClient(int client_sock);
};



#endif //SERVER_H
