#include <QCoreApplication>
#include <QtNetwork>
#include <API/client.h>
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
    cli->CreateUser(*usr);
}
void UICB(void* ptr, API::EventArgs* e)
{
    API::Client* cli = (API::Client*)ptr;
    API::UserInfoReceiveEventArgs* e2 = (API::UserInfoReceiveEventArgs*)e;
    qDebug() << e2->UserData.get()->StdOut().c_str();
    if (*e2->UserData.get()->Tag.get() != *cli->CurrentUser.get()->Tag.get())
    {
        DataTypes::Message tmp;
        tmp.To.set(e2->UserData.get()->ID.get());
        tmp.From.set(cli->CurrentUser.get()->ID.get());
        tmp.Content.set(new QString("HAHAHHAHAHAHAHAHAHH"));
        tmp.MessageID.set(400);
        cli->SendMessage(tmp);
    }
}
void CUCB(void* ptr, API::EventArgs* e)
{
    API::Client* cli = (API::Client*)ptr;
    API::CreateUserEventArgs* e2 = (API::CreateUserEventArgs*)e;
    if (e2->Error == DataTypes::CreateUserError::Success)
    {
        qDebug() << "Success !";
        cli->GetUserInfo("@test123");
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
void MRCB(void* ptr, API::EventArgs e)
{
    API::Client* cli = (API::Client*)ptr;
    //API::MessageReceiveEventArgs* e2 = (API::MessageReceiveEventArgs*)e;

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
    /*DataTypes::Message tmp;
    tmp.To.set(1);
    tmp.From.set(2);
    tmp.Content.set(new QString("HAHAHHAHAHAHAHAHAHH"));
    tmp.MessageID.set(400);
    std::cout << tmp.StdOut() << std::endl;

    auto bts = tmp.Serialize();
    auto mm = DataTypes::Message::Parse(&bts);
    std::cout << mm->StdOut() << std::endl;*/
}
