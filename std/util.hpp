#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP
#include <QCoreApplication>

typedef unsigned long long uulong;
#define INT_MAXVALUE 2147483647

class utils {
public:
    static void catoqa(QByteArray& array, char* data, int size)
    {
        for (int i = 0; i < size; ++i) {
            array.push_back(data[i]);
        }
    }
    static void catoqa(QByteArray& array, const char* data, int size)
    {
        for (int i = 0; i < size; ++i) {
            array.push_back(data[i]);
        }
    }
    static void intToqa(QByteArray& array, int value)
    {
        char tmp[4];
        memcpy_s(tmp, 4, &value, 4);
        catoqa(array, tmp, 4);
    }
    static void uulongToqa(QByteArray& array, uulong value)
    {
        char tmp[8];
        memcpy_s(tmp, 8, &value, 8);
        catoqa(array, tmp, 8);
    }
    static uulong caTo_uulong(const char* data)
    {
        char tmp[8];
        uulong out;
        memcpy_s(tmp, 8, data, 8);
        memcpy_s(&out, 8, tmp, 8);
        return out;
    }
    static uulong caTo_int(const char* data)
    {
        char tmp[4];
        uulong out;
        memcpy_s(tmp, 4, data, 4);
        memcpy_s(&out, 4, tmp, 4);
        return out;
    }
    static char* emptyca()
    {
        char* tmp = new char[1];
        tmp[0] = 0;
        return tmp;
    }
};

#endif // UTILS_HPP
