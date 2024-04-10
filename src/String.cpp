
#include "string.hpp"
#include <iostream>

// buf is private variable in the hpp file.

using namespace std;

int String::strlen(const char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; ++i)
    {
    }
    return i;
}

char *String::strcpy(char *dest, const char *src)
{
    int i;
    for (i = 0; src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

void String::reverse_cpy(char *dest, const char *src)
{
    int end = String::strlen(src) - 1;
    for (int i = 0; i <= end; ++i)
    {
        dest[i] = src[end - i];
    }
    dest[end + 1] = '\0';
}

char *String::strncpy(char *dest, const char *src, int n)
{
    int i;
    for (i = 0; src[i] != '\0' && i < n; ++i)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *String::strdup(const char *src)
{
    int l = String::strlen(src) + 1;
    char *heapstr{new char[l]};
    String::strcpy(heapstr, src);
    return heapstr;
}

char *String::reverse_strdup(const char *src)
{
    int l = String::strlen(src) + 1;
    char *heapstr{new char[l]};
    String::reverse_cpy(heapstr, src);
    return heapstr;
}

char *String::strcat(char *dest, const char *src)
{
    int l = String::strlen(dest);
    for (int i = 0; src[i] != '\0'; ++i)
    {
        dest[l] = src[i];
        ++l;
    }
    dest[l] = '\0';
    return dest;
}

char *String::strncat(char *dest, const char *src, int n)
{
    int l = String::strlen(dest);
    for (int i = 0; src[i] != '\0' && i < n; ++i)
    {
        dest[l] = src[i];
        ++l;
    }
    dest[l] = '\0';
    return dest;
}

char *String::double_strdup(const char *str1, const char *str2)
{
    int l = String::strlen(str1) + String::strlen(str2) + 1;
    char *heapstr{new char[l]{'\0'}};
    String::strcat(heapstr, str1);
    String::strcat(heapstr, str2);
    return heapstr;
}

int String::strcmp(const char *left, const char *right)
{
    int i;
    for (i = 0; left[i] != '\0'; ++i)
        if (left[i] != right[i])
            return (left[i] - right[i]);
    return (left[i] - right[i]);
}

int String::strncmp(const char *left, const char *right, int n)
{
    int i;
    for (i = 0; left[i] != '\0' && i < n; ++i)
        if (left[i] != right[i])
            return (left[i] - right[i]);
    if (i == n)
        return 0;
    return (left[i] - right[i]);
}

const char *String::strchr(const char *str, char c)
{
    const char *ptr = nullptr;
    int i;
    for (i = 0; str[i] != '\0'; ++i)
        if (str[i] == c)
        {
            ptr = &str[i];
            break;
        }
    if (c == '\0')
        ptr = &str[i];
    return ptr;
}

const char *String::strstr(const char *haystack, const char *needle)
{
    const char *ptr = nullptr;
    int needleLength = String::strlen(needle);

    if (needleLength == 0)
        return haystack;

    int cycle = String::strlen(haystack) - needleLength + 1;
    for (int i = 0; i < cycle; ++i)
    {
        int step = 0;
        for (; step < needleLength; ++step)
            if (haystack[i + step] != needle[step])
                break;
        if (step == needleLength)
        {
            ptr = &haystack[i];
            break;
        }
    }
    return ptr;
}

String::String(int length)
{
    buf = new char[length];
    buf[length - 1] = '\0';
}

String::String(const char *s) : buf{strdup(s)}
{
}

String::String(const String &s) : buf{strdup(s.buf)}
{
}

String::~String()
{
    delete[] buf;
}

int String::size() const
{
    return String::strlen(buf);
}

void String::print(std::ostream &out) const
{
    for (int i = 0; buf[i] != '\0'; ++i)
    {
        out << buf[i];
    }
}

bool String::operator==(const String &s) const
{
    return (String::strcmp(buf, s.buf) == 0);
}

bool String::operator!=(const String &s) const
{
    return (!(String::strcmp(buf, s.buf) == 0));
}

bool String::operator>(const String &s) const
{
    return ((String::strcmp(buf, s.buf)) > 0);
}

bool String::operator<(const String &s) const
{
    return ((String::strcmp(buf, s.buf)) < 0);
}

bool String::operator<=(const String &s) const
{
    return ((String::strcmp(buf, s.buf)) <= 0);
}

bool String::operator>=(const String &s) const
{
    return ((String::strcmp(buf, s.buf)) >= 0);
}

String &String::operator=(const String &s)
{
    if (this == &s)
        return *this;
    if (buf)
        delete[] buf;

    buf = strdup(s.buf);
    return *this;
}

char &String::operator[](int index)
{
    int n = String::strlen(buf);
    if (0 < index && index < n)
        return buf[index];
    else
    {
        cout << "ERROR" << endl;
        return buf[0];
    }
}

const char &String::operator[](int index) const
{
    int n = String::strlen(buf);
    if (0 < index && index < n)
        return buf[index];
    else
        cout << "ERROR" << endl;
    return buf[0];
}

String String::reverse() const
{
    String reversed(String::strlen(buf) + 1);
    reverse_cpy(reversed.buf, buf);
    return reversed;
}

int String::indexOf(char c) const
{
    char *foundptr = (char *)String::strchr(buf, c);

    if (foundptr == nullptr)
        return -1;

    int index = foundptr - buf;
    return index;
}

int String::indexOf(const String &s) const
{
    char *otherbuf = (char *)s.buf;
    char *foundptr = (char *)String::strstr(buf, otherbuf);

    if (foundptr == nullptr)
        return -1;
    int index = foundptr - buf;

    return index;
}

String String::operator+(const String &s) const
{
    int l = String::strlen(buf) + String::strlen(s.buf) + 1;
    String con(l);
    con.buf[0] = '\0';
    String::strcat(con.buf, buf);
    String::strcat(con.buf, s.buf);
    return con;
}

String &String::operator+=(const String &s)
{
    char *concatstr = double_strdup(buf, s.buf);
    delete[] buf;
    buf = concatstr;
    return *this;
}

void String::read(std::istream &in)
{
    char tempbuf[1024];
    in >> tempbuf;

    char *concatstr = double_strdup(buf, tempbuf);
    delete[] buf;

    buf = concatstr;
}

std::ostream &operator<<(std::ostream &out, String s)
{
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s)
{
    s.read(in);
    return in;
}

String::String(String &&s)
{
    buf = s.buf;
    s.buf = nullptr;
}

String &String::operator=(String &&s)
{
    delete[] buf;
    buf = s.buf;
    s.buf = nullptr;
    return *this;
}

void String::swap(String &s)
{
    char *temp = buf;
    buf = s.buf;
    s.buf = temp;
}
