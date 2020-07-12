#include "user.h"
#include <iostream>
#include <sstream>
namespace DataTypes {
    void catoqa(QByteArray& array, char* data, int size)
    {
        for (int i = 0; i < size; ++i) {
            array.push_back(data[i]);
        }
    }
    void catoqa(QByteArray& array, const char* data, int size)
    {
        for (int i = 0; i < size; ++i) {
            array.push_back(data[i]);
        }
    }
    void intToqa(QByteArray& array, int value)
    {
        char tmp[4];
        memcpy_s(tmp, 4, &value, 4);
        catoqa(array, tmp, 4);
    }
    char* emptyca()
    {
        char* tmp = new char[1];
        tmp[0] = 0;
        return tmp;
    }
    User::User()
    {
        Privacy.set(NULL);
        Name.set(NULL);
        Email.set(NULL);
        Password.set(NULL);
        Tag.set(NULL);
        ProfilePictureID.set(NULL);
    }
    User* User::Parse(QByteArray data)
    {
        int cind = 0;
        char bID[8];
        char intB[4];
        User* usr = new User();
        ulong id = 0;
        memcpy_s(bID, 8, &data.data()[cind], 8);
        memcpy_s(&id, 8, bID, 8);
        usr->ID.set(id);
        cind += 8;
        int perm1 = -1;
        memcpy_s(intB, 4, &data.data()[cind], 4);
        memcpy_s(&perm1, 4, intB, 4);
        if (perm1 != INT_MAXVALUE)
        {
            usr->Privacy.set(new UserPrivacy());
            usr->Privacy.get()->CanGetInfo.set((Perm)perm1);
            cind += 4;
            memcpy_s(intB, 4, &data.data()[cind], 4);
            memcpy_s(&perm1, 4, intB, 4);
            usr->Privacy.get()->CanSeePicture.set((Perm)perm1);
            cind += 4;
            memcpy_s(intB, 4, &data.data()[cind], 4);
            memcpy_s(&perm1, 4, intB, 4);
            usr->Privacy.get()->CanSeeBio.set((Perm)perm1);
            cind += 4;
        }
        else
        {
            cind += 12;
        }

        //Email
        perm1 = -1;
        memcpy_s(intB, 4, &data.data()[cind], 4);
        memcpy_s(&perm1, 4, intB, 4);
        cind += 4;
        char* email = new char[perm1 + 1];
        email[perm1] = 0;
        memcpy_s(email, perm1, &data.data()[cind], perm1);
        usr->Email.set(new QString(email));
        cind += perm1;

        //Password
        perm1 = -1;
        memcpy_s(intB, 4, &data.data()[cind], 4);
        memcpy_s(&perm1, 4, intB, 4);
        cind += 4;
        char* pass = new char[perm1 + 1];
        pass[perm1] = 0;
        memcpy_s(pass, perm1, &data.data()[cind], perm1);
        usr->Password.set(new QString(pass));
        cind += perm1;

        //Name
        perm1 = -1;
        memcpy_s(intB, 4, &data.data()[cind], 4);
        memcpy_s(&perm1, 4, intB, 4);
        cind += 4;
        char* nm = new char[perm1 + 1];
        nm[perm1] = 0;
        memcpy_s(nm, perm1, &data.data()[cind], perm1);
        usr->Name.set(new QString(nm));
        cind += perm1;

        //PPID
        perm1 = -1;
        memcpy_s(intB, 4, &data.data()[cind], 4);
        memcpy_s(&perm1, 4, intB, 4);
        cind += 4;
        char* ppid = new char[perm1 + 1];
        ppid[perm1] = 0;
        memcpy_s(ppid, perm1, &data.data()[cind], perm1);
        usr->ProfilePictureID.set(new QString(ppid));
        cind += perm1;

        //Tag
        perm1 = -1;
        memcpy_s(intB, 4, &data.data()[cind], 4);
        memcpy_s(&perm1, 4, intB, 4);
        cind += 4;
        char* tag = new char[perm1 + 1];
        tag[perm1] = 0;
        memcpy_s(tag, perm1, &data.data()[cind], perm1);
        usr->Tag.set(new QString(tag));
        cind += perm1;

        return usr;
    }
    QByteArray User::Serialize()
    {
        QByteArray array;
        char id[8];
        uulong idt = ID.get();
        memcpy_s(id, 8, &idt, 8);
        catoqa(array, id, 8);
        if (Privacy != NULL)
        {
            intToqa(array, (int)Privacy.get()->CanGetInfo.get());
            intToqa(array, (int)Privacy.get()->CanSeePicture.get());
            intToqa(array, (int)Privacy.get()->CanSeeBio.get());
        }
        else
        {
            intToqa(array, INT_MAXVALUE);
            intToqa(array, 0);
            intToqa(array, 0);
        }

        if (Email != NULL)
        {
            int sz = Email.get()->toStdString().size();
            intToqa(array, sz);
            catoqa(array, Email.get()->toStdString().c_str(), sz);
        }
        else
        {
            intToqa(array, 1);
            catoqa(array, emptyca(), 1);
        }

        if (Password != NULL)
        {
            int sz = Password.get()->toStdString().size();
            intToqa(array, sz);
            catoqa(array, Password.get()->toStdString().c_str(), sz);
        }
        else
        {
            intToqa(array, 1);
            catoqa(array, emptyca(), 1);
        }

        if (Name != NULL)
        {
            int sz = Name.get()->toStdString().size();
            intToqa(array, sz);
            catoqa(array, Name.get()->toStdString().c_str(), sz);
        }
        else
        {
            intToqa(array, 1);
            catoqa(array, emptyca(), 1);
        }

        if (ProfilePictureID != NULL)
        {
            int sz = ProfilePictureID.get()->toStdString().size();
            intToqa(array, sz);
            catoqa(array, ProfilePictureID.get()->toStdString().c_str(), sz);
        }
        else
        {
            intToqa(array, 1);
            catoqa(array, emptyca(), 1);
        }

        if (Tag != NULL)
        {
            int sz = Tag.get()->toStdString().size();
            intToqa(array, sz);
            catoqa(array, Tag.get()->toStdString().c_str(), sz);
        }
        else
        {
            intToqa(array, 1);
            catoqa(array, emptyca(), 1);
        }

        return array;
    }
    std::string User::StdOut()
    {
        std::ostringstream os;
        os << "Name: " << (Name.get() != NULL ? Name.get()->toStdString() : std::string("NULL"));
        os << std::endl;
        os << "Email: " << (Email.get() != NULL ? Email.get()->toStdString() : std::string("NULL"));
        os << std::endl;
        os << "Password: " << (Password.get() != NULL ? Password.get()->toStdString() : std::string("NULL"));
        os << std::endl;
        os << "Tag: " << (Tag.get() != NULL ? Tag.get()->toStdString() : std::string("NULL"));
        os << std::endl;
        os << "ProfilePictureID: " << (ProfilePictureID.get() != NULL ? ProfilePictureID.get()->toStdString() : std::string("NULL"));
        os << std::endl;
        os << "ID: " << ID.get();
        std::string str = os.str();
        return str;
    }
}
