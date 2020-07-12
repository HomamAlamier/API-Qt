#include "message.h"
namespace DataTypes {

    Message::Message()
    {
        Content.set(NULL);
        Time.set(new QDateTime(QDateTime::currentDateTime()));
        MessageID.set(0);
        ReplayMessageID.set(0);
        From.set(0);
        To.set(0);
    }
    QByteArray Message::Serialize()
    {
        QByteArray array;
        utils::uulongToqa(array, MessageID.get());
        utils::uulongToqa(array, ReplayMessageID.get());
        utils::uulongToqa(array, From.get());
        utils::uulongToqa(array, To.get());

        auto tstr = Time.get()->toString("ddMMyyyyhhmmss").toStdString();
        utils::intToqa(array, tstr.size());
        utils::catoqa(array, tstr.c_str(), tstr.size());
        if (Content.get() == NULL)
        {
            utils::intToqa(array, 1);
            utils::catoqa(array, utils::emptyca(), 1);
        }
        else
        {
            auto str = Content.get()->toStdString();
            utils::intToqa(array, str.size());
            utils::catoqa(array, str.c_str(), str.size());
        }

        return array;
    }
    Message* Message::Parse(QByteArray *data)
    {
        int cind = 0;
        Message* msg = new Message();
        msg->MessageID.set(utils::caTo_uulong(&data->data()[cind]));
        cind += 8;
        msg->ReplayMessageID.set(utils::caTo_uulong(&data->data()[cind]));
        cind += 8;
        msg->From.set(utils::caTo_uulong(&data->data()[cind]));
        cind += 8;
        msg->To.set(utils::caTo_uulong(&data->data()[cind]));
        cind += 8;


        int tlen = utils::caTo_int(&data->data()[cind]);
        cind += 4;
        char* tmc = new char[tlen + 1];
        tmc[tlen] = 0;
        memcpy_s(tmc, tlen, &data->data()[cind], tlen);
        msg->Time.set(new QDateTime(QDateTime::fromString(QString(tmc), "ddMMyyyyhhmmss")));
        cind += tlen;

        int clen = utils::caTo_int(&data->data()[cind]);
        cind += 4;
        char* cmc = new char[clen + 1];
        cmc[clen] = 0;
        memcpy_s(cmc, clen, &data->data()[cind], clen);
        msg->Content.set(new QString(cmc));
        cind += clen;

        return msg;
    }

    std::string Message::StdOut()
    {
        std::ostringstream os;
        os << "{" << std::endl;
        os << "\tMessageID: " << MessageID.get() << std::endl;
        os << "\tReplayMessageID: " << ReplayMessageID.get() << std::endl;
        os << "\tFrom: " << From.get() << std::endl;
        os << "\tTo: " << To.get() << std::endl;
        os << "\tTime: " << Time.get()->toString().toStdString() << std::endl;
        os << "\tContent: " << Content.get()->toStdString() << std::endl;
        os << "}" << std::endl;
        return os.str();
    }
}
