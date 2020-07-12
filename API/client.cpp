#include "client.h"

#define API_CLIENT_NOVERIFY
namespace API {
    void READALL(QSslSocket* socket);
    Client::Client(const char* ip)
    {
        this->ip = ip;
        OnConnect.set(NULL);
        OnCreateUser.set(NULL);
        CurrentUser.set(NULL);
        OnUserInfoReceive.set(NULL);
        log = new std::Logger("Client");
    }
    void Client::Connect()
    {
        log->Write("Creating Connection ..");
        socket = new QSslSocket();
        if (!socket->supportsSsl())
            qDebug() << "ERROR:: System does not support ssl or some librarys not found !";
            //throw new std::exception("ERROR:: System does not support ssl or some librarys not found !");
#ifdef API_CLIENT_NOVERIFY
        log->Write("API_CLIENT_NOVERIFY Defined ! set PeerVerifyMode To VerifyNone.");
        socket->setPeerVerifyMode(QSslSocket::VerifyNone);
#endif
        socket->setProtocol(QSsl::TlsV1_2);
        socket->modeChanged(QSslSocket::SslClientMode);
        socket->connectToHostEncrypted(QString(ip), MAINPORT);
        if (!socket->waitForEncrypted())
        {
            //throw new std::exception(socket->errorString().toStdString().c_str());
            qDebug() << socket->errorString();
            log->Write(socket->errorString());
        }
        if (OnConnect.get() != NULL && socket->isOpen() && socket->isEncrypted())
            OnConnect.get()(this, new EventArgs());

    }
    void Client::READ()
    {
        while (socket->waitForReadyRead())
        {
            auto rec = socket->readAll();
            DataTypes::Command cmd =  DataTypes::Command::Parse(&rec);
            qDebug() << cmd.ToString();
            switch (cmd.CommandType()) {
                case DataTypes::CommandType::Ping:
                {
                    QByteArray qba;
                    qba.push_back((char)0);
                    DataTypes::Command tmp(DataTypes::CommandType::Ping, &qba);
                    QByteArray btmp = tmp.Serialize();
                    socket->write(btmp);
                    socket->flush();
                }
                break;
                case DataTypes::CommandType::CreateUser:
                {
                    int errcode = -1;
                    char* d = cmd.Data()->data();
                    memcpy_s(&errcode, 4, d, 4);
                    *log->Stream.get() << "[" << QDateTime::currentDateTime().toString().toStdString() << "] Received CreateUser Command Result ( 0x" << std::hex << errcode << " )." << std::endl;
                    if (errcode == (int)DataTypes::CreateUserError::Success)
                    {
                        auto bts = CurrentUser.get()->Tag.get()->toStdString();
                        DataTypes::Command tmp(DataTypes::CommandType::GetUserInfo
                                               , new QByteArray(bts.c_str(), bts.size()));
                        QByteArray btmp = tmp.Serialize();
                        socket->write(btmp);
                        socket->flush();
                    }

                    if (OnCreateUser.get() != NULL)
                    {
                        OnCreateUser.get()(this, new CreateUserEventArgs((DataTypes::CreateUserError)errcode));
                    }
                }
                break;
                case DataTypes::CommandType::GetUserInfo:
                {
                    DataTypes::User* usr = DataTypes::User::Parse(*cmd.Data());
                    if (*usr->Tag.get() == *CurrentUser.get()->Tag.get())
                    {
                        CurrentUser.set(usr);
                    }
                    log->Write(QString("Received GetUserInfo Command Result (") + usr->Tag.get() + ")");
                    if (OnUserInfoReceive != NULL)
                    {
                        OnUserInfoReceive.get()(this, new UserInfoReceiveEventArgs(usr));
                    }
                }
                break;
                case DataTypes::CommandType::Message:
                {
                    DataTypes::Message* msg = DataTypes::Message::Parse(cmd.Data());
                    if (OnMessageReceive != NULL)
                    {
                        OnMessageReceive.get()(this, new MessageReceiveEventArgs(msg));
                    }
                }
                break;
            }
        }
    }
    void Client::CreateUser(DataTypes::User& usr)
    {
        auto bts = usr.Serialize();
        DataTypes::Command cmd(DataTypes::CommandType::CreateUser, &bts);
        socket->write(cmd.Serialize());
        socket->flush();
        CurrentUser.set(&usr);
    }
    void Client::GetUserInfo(QString tag)
    {
        auto str = tag.toStdString();
        QByteArray array;
        utils::catoqa(array, str.c_str(), str.size());
        DataTypes::Command cmd(DataTypes::CommandType::GetUserInfo, &array);
        socket->write(cmd.Serialize());
        socket->flush();
    }
    void Client::SendMessage(DataTypes::Message& msg)
    {
        auto bts = msg.Serialize();
        DataTypes::Command cmd(DataTypes::CommandType::Message, &bts);
        socket->write(cmd.Serialize());
        socket->flush();
    }
}
