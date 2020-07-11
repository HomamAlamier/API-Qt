#ifndef CLIENT_H
#define CLIENT_H

#include "Command.h"
#include "user.h"
#include <QtNetwork>
#include <thread>

namespace API
{
    class EventArgs {};
    class CreateUserEventArgs : public EventArgs {
    public:
        std::Prop<DataTypes::CreateUserError> Error;
        CreateUserEventArgs(DataTypes::CreateUserError err) { Error.set(err); }
    };
    class UserInfoReceiveEventArgs : public EventArgs {
    public:
        std::Prop<DataTypes::User*> UserData;
        UserInfoReceiveEventArgs(DataTypes::User* u) { UserData.set(u); }
    };
    #define MAINPORT 4444
    typedef void (*EventHandler)(void*, EventArgs*);


    class Client
    {
    private:
        QSslSocket* socket;
        const char* ip;
        QThread* readThread;
    public:
        std::Prop<EventHandler> OnConnect;
        std::Prop<EventHandler> OnCreateUser;
        std::Prop<EventHandler> OnUserInfoReceive;
        std::Prop<DataTypes::User*> CurrentUser;
        Client(const char* ip);
        void Connect();
        void CreateUser(DataTypes::User* usr);
        void READ();
    };
}

#endif // CLIENT_H
