#ifndef USER_H
#define USER_H

#include <QCoreApplication>
#include <property.hpp>

namespace DataTypes {

    enum class CreateUserError
    {
        EmailIsNotValid = 0x1,
        TagIsNotValid = 0x10,
        Success = 0x0
    };
    enum class LoginUserError
    {
        AccountNotFound = 0x1,
        IncorrectPassword = 0x10,
        Success = 0x0
    };
    enum class Perm
    {
        NoBody = 0x0,
        FriendOnly = 0x1,
        All = 0x10
    };
    enum class PrivacySetting
    {
        CanGetInfo = 0x0,
        CanSeeProfilePicture = 0x1,
        CanSeeBio = 0x10
    };
    struct UserPrivacy
    {
    public:
        std::Prop<Perm> CanSeeBio;
        std::Prop<Perm> CanGetInfo;
        std::Prop<Perm> CanSeePicture;
        UserPrivacy()
        {
            CanSeeBio.set(Perm::All);
            CanGetInfo.set(Perm::All);
            CanSeePicture.set(Perm::All);
        }
    };
    class User
    {
    private:
    public:
        std::Prop<UserPrivacy*> Privacy;
        std::Prop<QString*> Name;
        std::Prop<QString*> Tag;
        std::Prop<QString*> Email;
        std::Prop<QString*> Password;
        std::Prop<QString*> ProfilePictureID;
        std::Prop<uulong> ID;
        User();
        QByteArray Serialize();
        static User* Parse(QByteArray data);
        std::string StdOut();
    };
}

#endif // USER_H
