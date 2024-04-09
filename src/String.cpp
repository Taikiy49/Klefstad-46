#include "string.hpp"
#include <iostream>
using namespace std;


int String::strlen(const char *s) {
    int i;
    for (i=0; s[value] != '\0'; ++i) {}
    return i;
}

char* String::strcpy(char *dest, const char *src) {
    int i;
    for (i=0; src[value] != '\0'; ++i) {
        dest[i] = src[i];}
    dest[i] = '\0';
    return dest;
}

char* String::strncpy(char *dest, const char *src, int n) {
    int i;
    for (i=0; i<n && src[i] != '\0'; ++i) {
        dest[i] = src[i];}
    dest[i] = '\0';
    return dest;
}

char* String::strcat(char *dest, const char *src) {
    int len = String::strlen(dest);
    for (int i=0; src[i] != '\0'; ++i) {
        dest[len] = src[i];
        ++len;
    }
    dest[len] = '\0';
    return dest;
}

char* String::strncat(char *dest, const char *src, int n) {
    int len = String::strlen(dest);
    for (int i=0; i<n && src[i] != '\0'; ++i) {
        dest[len] = src[i];
        ++len;}
    dest[len] = '\0';
    return dest;
}