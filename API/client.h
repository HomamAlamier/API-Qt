#ifndef CLIENT_H
#define CLIENT_H

#include <DataTypes/Command.h>
#include <DataTypes/user.h>
#include <DataTypes/message.h>
#include <std/logger.hpp>
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
    class MessageReceiveEventArgs : public EventArgs {
    public:
        std::Prop<DataTypes::Message*> Message;
        MessageReceiveEventArgs(DataTypes::Message* u) { Message.set(u); }
    };
    #define MAINPORT 4444
    typedef void (*EventHandler)(void*, EventArgs*);


    class Client
    {
    private:
        QSslSocket* socket;
        const char* ip;
        QThread* readThread;
        std::Logger* log;
    public:
        std::Prop<EventHandler> OnConnect;
        std::Prop<EventHandler> OnCreateUser;
        std::Prop<EventHandler> OnUserInfoReceive;
        std::Prop<EventHandler> OnMessageReceive;
        std::Prop<DataTypes::User*> CurrentUser;
        Client(const char* ip);
        void Connect();
        void CreateUser(DataTypes::User& usr);
        void GetUserInfo(QString tag);
        void SendMessage(DataTypes::Message& msg);
        void READ();
    };
}

#endif // CLIENT_H
