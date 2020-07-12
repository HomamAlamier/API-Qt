#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <qdatetime.h>
#include <ostream>
#include <fstream>
#include <std/property.hpp>

namespace std {
    class Logger
    {
    private:
    public:
        Prop<std::ofstream*> Stream;
        Logger(QString className)
        {
            qDebug() << QDir::currentPath() << (className + "_log.txt");
            Stream.set(new std::ofstream((className + "_log.txt").toStdString(), std::ios::out));
            auto stream = Stream.get();
            if (stream->is_open())
            {
                QDateTime x = QDateTime::currentDateTime();
                *stream << "[" << x.toString().toStdString() << "] Started !" << std::endl;
            }
        }
        void Write(QString line)
        {
            auto stream = Stream.get();
            if (stream->is_open())
            {
                QDateTime x = QDateTime::currentDateTime();
                *stream << "[" << x.toString().toStdString() << "] " << line.toStdString() << std::endl;
            }
        }
    };
}

#endif // LOGGER_HPP
