#ifndef MESSAGE_H
#define MESSAGE_H

#include <std/property.hpp>
#include <QCoreApplication>
#include <qdatetime.h>
#include <std/util.hpp>
#include <sstream>
namespace DataTypes {
    class Message
    {
    public:
        std::Prop<QString*> Content;
        std::Prop<uulong> MessageID;
        std::Prop<uulong> From;
        std::Prop<uulong> To;
        std::Prop<uulong> ReplayMessageID;
        std::Prop<QDateTime*> Time;
        Message();
        QByteArray Serialize();
        static Message* Parse(QByteArray* data);
        std::string StdOut();
    };
}

#endif // MESSAGE_H
