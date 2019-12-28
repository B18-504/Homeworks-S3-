#pragma once

String::String(String &&a)
{
    body = a.body;
    len = a.len;
    a.body = 0;
}

String::String(const String &a)
{
    bool err;
    len = a.len;
    copy(body, a.body, err);
}

String::String(char *a)
{
    bool err;
    len = 0;
    char *b = a;
    while(*a)
    {
        a++;
        len++;
    }
    copy(body, b, err);
}

bool operator>(const String &a, const String &b)
{
    char *ap = a.body, *bp = b.body;
    while(*ap == *bp)
    {
        if(*ap == 0)
        {
            return 0;
        }
        ap++;
        bp++;
    }
    return *ap > *bp;
}

bool operator<(const String &a, const String &b)
{
    char *ap = a.body, *bp = b.body;
    while(*ap == *bp)
    {
        if(*ap == 0)
        {
            return 0;
        }
        ap++;
        bp++;
    }
    return *ap < *bp;
}

bool operator==(const String &a, const String &b)
{
    char *ap = a.body, *bp = b.body;
    while(*ap == *bp)
    {
        if(*ap == 0)
        {
            return 1;
        }
        ap++;
        bp++;
    }
    return 0;
}