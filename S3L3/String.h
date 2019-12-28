#pragma once

#include "CmdMgr/Str.cpp"   //to be replaced

struct String               //how interesting. I love 0 PnP abillity of STL
{
    char *body;
    int len;

    String() = delete;         //copying does not handle errors!
    String(char *a);
    String(const String &a);
    String(String &&a);
    ~String() = default;
};

bool operator<(const String&, const String&);
bool operator>(const String&, const String&);
bool operator==(const String&, const String&);

#include "String.cpp"