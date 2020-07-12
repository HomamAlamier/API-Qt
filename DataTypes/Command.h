#ifndef COMMAND_H
#define COMMAND_H

#include <QCoreApplication>

namespace DataTypes {
    enum class CommandType
    {
        Ping              =  0x1,
        GetVersion        =  0x10,
        CreateUser        =  0x11,
        LoginUser         =  0x110,
        GetUserInfo       =  0x111,
        ChangeUserPrivacy =  0x1110,
        Message           =  0x1111
    };
    class Command
    {
    private:
        CommandType ctype;
        QByteArray* data;
        int datalen;
    public:
        Command(CommandType commandtype);
        Command(CommandType commandtype, QByteArray* data);
        QByteArray Serialize();
        QString ToString();
        QByteArray* Data();
        CommandType CommandType();
        void StdOut();
        static Command Parse(QByteArray* data);
    };
}

#endif // COMMAND_H
