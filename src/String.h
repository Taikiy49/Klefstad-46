#ifndef STRING_HPP
#define STRING_HPP

#include <iosfwd>

class String
{
public:
    explicit String(const char *s = "");

    String(const String &s);

    String(String &&s);

    void swap(String &s);

    String &operator=(const String &s);

    String &operator=(String &&s);

    char &operator[](int index);

    const char &operator[](int index) const;

    int size() const;
    String reverse() const;
    int indexOf(char c) const;
    int indexOf(const String &s) const;
    bool operator==(const String &s) const;
    bool operator!=(const String &s) const;
    bool operator>(const String &s) const;
    bool operator<(const String &s) const;
    bool operator<=(const String &s) const;
    bool operator>=(const String &s) const;
    String operator+(const String &s) const;
    String &operator+=(const String &s);
    void print(std::ostream &out) const;
    void read(std::istream &in);

    ~String();

    bool in_bounds(int i) const
    {
        return i >= 0 && i < strlen(buf);
    }
    static int strlen(const char *s);
    static char *strcpy(char *dest, const char *src);
    static char *strncpy(char *dest, const char *src, int n);
    static char *strdup(const char *src);
    static char *reverse_strdup(const char *src);
    static char *double_strdup(const char *str1, const char *str2);
    static char *strcat(char *dest, const char *src);
    static char *strncat(char *dest, const char *src, int n);
    static int strcmp(const char *left, const char *right);
    static int strncmp(const char *left, const char *right, int n);
    static void reverse_cpy(char *dest, const char *src);
    static const char *strchr(const char *str, char c);
    static const char *strstr(const char *haystack, const char *needle);

private:
    char *buf;
    explicit String(int length);
};

std::ostream &operator<<(std::ostream &out, String s);

std::istream &operator>>(std::istream &in, String &s);

#endif