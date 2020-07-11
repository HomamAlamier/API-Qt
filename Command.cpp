#include "Command.h"
#include <iostream>
namespace DataTypes {
QString CommandType_ToString(CommandType ctype);
    Command::Command(enum CommandType commandtype)
    {
        ctype = commandtype;
    }
    Command::Command(enum CommandType commandtype, QByteArray* data)
    {
        ctype = commandtype;
        this->data = data;
        datalen = data->size();
    }
    Command Command::Parse(QByteArray *data)
    {
        char tmp[4];
        int type = -1;
        memcpy_s(tmp, 4, data->data(), 4);
        memcpy_s(&type, 4 * sizeof(char), tmp, 4 * sizeof(char));
        std::cout << "Parsed Type: " << type << std::endl;
        int dl = -1;
        memcpy_s(tmp, 4, &data->data()[4], 4);
        memcpy_s(&dl, 4 * sizeof(char), tmp, 4 * sizeof(char));
        std::cout << "Parsed Length: " << dl << std::endl;
        DataTypes::CommandType ctype = (DataTypes::CommandType)type;
        int l = data->size() - 8;
        std::cout << "DATA LENGTH = " << l << std::endl;
        std::cout << "ALL LENGTH = " << data->size() << std::endl;
        char* bdata = new char[l];
        memcpy_s(bdata, l * sizeof(char), &data->data()[8], l * sizeof(char));
        QByteArray* qdata = new QByteArray(bdata, l * sizeof (char));
        return Command(ctype, qdata);
    }
    QString Command::ToString()
    {
        QString str;
        str += "CommandType: ";
        str += CommandType_ToString(ctype);
        str += "\n";
        str += "DataLength: ";
        str += datalen;
        str += "\n";
        return str;
    }
    void Command::StdOut()
    {
        std::cout << "\tCommandType: " << CommandType_ToString(ctype).toStdString() << std::endl << "<br>DataLength: " << std::to_string(datalen) << std::endl;
    }
    QByteArray Command::Serialize()
    {
        QByteArray array;
        int itmp = (int)ctype;
        char btmp[4];
        memcpy_s(btmp, 4 * sizeof(char), &itmp, 4 * sizeof(char));
        for(int i = 0; i < 4; ++i)
            array.push_back(btmp[i]);
        itmp = data->size();
        memcpy_s(btmp, 4 * sizeof(char), &itmp, 4 * sizeof(char));
        for(int i = 0; i < 4; ++i)
        {
            array.push_back(btmp[i]);
        }
        for(int i = 0; i < data->size(); ++i)
            array.push_back(data->data()[i]);
        std::cout << "Serilaize Return: " << array.size() << std::endl;
        return array;
    }
    QByteArray* Command::Data()
    {
        return data;
    }
    CommandType Command::CommandType()
    {
        return ctype;
    }
    QString CommandType_ToString(CommandType ctype)
    {
        switch (ctype) {
            case CommandType::Ping:
                return QString("Ping");
            break;
            case CommandType::Message:
                return QString("Message");
            break;
            case CommandType::LoginUser:
                return QString("LoginUser");
            break;
            case CommandType::CreateUser:
                return QString("CreateUser");
            break;
            case CommandType::GetVersion:
                return QString("GetVersion");
            break;
            case CommandType::GetUserInfo:
                return QString("GetUserInfo");
            break;
            case CommandType::ChangeUserPrivacy:
                return QString("ChangeUserPrivacy");
            break;
        }
    }
}
