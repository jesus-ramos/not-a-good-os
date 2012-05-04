#ifndef _CTYPE_H
#define _CTYPE_H

static inline int isdigit(char c)
{
    return c >= '0' && c <= '9';
}

static inline int isalpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static inline int isalnum(char c)
{
    return isdigit(c) || isalpha(c);
}

static inline char toupper(char c)
{
    return c & ~(1 << 5);
}

static inline char tolower(char c)
{
    return c | (1 << 5);
}

static inline int isupper(char c)
{
    return !(c & ~(1 << 5));
}

static inline int islower(char c)
{
    return c & (1 << 5);
}

static inline int isspace(char c)
{
    return c == ' ';
}

static inline int isblank(char c)
{
    return isspace(c) || c == '\t';
}

#endif /* _CTYPE_H */
