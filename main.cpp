#include <QCoreApplication>
#include <QtNetwork>
#include <Command.h>
#include <client.h>
#include <user.h>
#include <thread>
QT_REQUIRE_CONFIG(ssl);
void Connected(void* ptr, API::EventArgs* e)
{
    qDebug() << "Connected !";
    API::Client* cli = (API::Client*)ptr;
    DataTypes::User* usr = new DataTypes::User();
    usr->Name.set(new QString("Test1"));
    usr->Email.set(new QString("test@dev.com"));
    usr->Password.set(new QString("12345"));
    usr->Tag.set(new QString("@devtest"));
    cli->CreateUser(usr);
}
void UICB(void* ptr, API::EventArgs* e)
{
    API::Client* cli = (API::Client*)ptr;
    API::UserInfoReceiveEventArgs* e2 = (API::UserInfoReceiveEventArgs*)e;
    qDebug() << e2->UserData.get()->StdOut().c_str();
}
void CUCB(void* ptr, API::EventArgs* e)
{
    API::Client* cli = (API::Client*)ptr;
    API::CreateUserEventArgs* e2 = (API::CreateUserEventArgs*)e;
    if (e2->Error == DataTypes::CreateUserError::Success)
    {
        qDebug() << "Success !";
    }
    else if (e2->Error == DataTypes::CreateUserError::TagIsNotValid)
    {
        qDebug() << "TagIsNotValid !";
    }
    else if (e2->Error == DataTypes::CreateUserError::EmailIsNotValid)
    {
        qDebug() << "EmailIsNotValid !";
    }
}
void cliThread()
{
    API::Client c("127.0.0.1");
    c.OnConnect.set(Connected);
    c.OnCreateUser.set(CUCB);
    c.OnUserInfoReceive.set(UICB);
    c.Connect();
    c.READ();
}
int main(int argc, char *argv[])
{
    std::thread t(cliThread);
    while (true) {
    }
}
