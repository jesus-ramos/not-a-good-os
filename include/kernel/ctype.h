/**
 * @file
 *
 * Definitions for basic functions for checking characters in strings for
 * properties (ISO C standard ctype.h). Unlike the ISO C standard these take
 * char type not int
 */

#ifndef _CTYPE_H
#define _CTYPE_H

/**
 * @brief Checks if a character is a number
 *
 * @param c character to check
 *
 * @return 1 if c is a digit, 0 otherwise
 */
static inline int isdigit(char c)
{
    return c >= '0' && c <= '9';
}

/**
 * @brief Checks if a character is a letter
 *
 * @param c character to check
 *
 * @return 1 if c is a letter, 0 otherwise
 */
static inline int isalpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

/**
 * @brief Checks if a character is either a letter or a number
 *
 * @param c character to check
 *
 * @return 1 if character is either a letter or number, 0 otherwise
 */
static inline int isalnum(char c)
{
    return isdigit(c) || isalpha(c);
}

/**
 * @brief Converts a character to its uppercase representation
 *
 * @param c character which you want the uppercase version of
 *
 * @return uppercase version of c
 */
static inline char toupper(char c)
{
    return c & ~(1 << 5);
}

/**
 * @brief Converts a character to its lowercase representation
 *
 * @param c the character which you want the lowercase version of
 *
 * @return lowercase version of c
 */
static inline char tolower(char c)
{
    return c | (1 << 5);
}

/**
 * @brief Checks if a character is uppercase
 *
 * @param c character to check
 *
 * @return 1 if c is uppercase, 0 otherwise
 */
static inline int isupper(char c)
{
    return !(c & ~(1 << 5));
}

/**
 * @brief Checks if a character is lowercase
 *
 * @param c character to check
 *
 * @return 1 if c is lowercase, 0 otherwise
 */
static inline int islower(char c)
{
    return c & (1 << 5);
}

/**
 * @brief Checks if a character is a space
 *
 * @param c character to check
 *
 * @return 1 if c is a space, 0 otherwise
 */
static inline int isspace(char c)
{
    return c == ' ';
}

/**
 * @brief Checks if a character is a blank character
 *
 * @param c character to check
 *
 * @return 1 if c is a blank character (space or tab), 0 otherwise
 */
static inline int isblank(char c)
{
    return isspace(c) || c == '\t';
}

#endif /* _CTYPE_H */
