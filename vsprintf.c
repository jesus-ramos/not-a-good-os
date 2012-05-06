#include <kernel/ctype.h>
#include <kernel/stdio.h>
#include <kernel/string.h>

#include <asm/div.h>

#define PAD_ZEROES     (1)
#define SIGNED         (1 << 1)
#define PLUS           (1 << 2)
#define SPACE          (1 << 3)
#define LEFT_JUSTIFIED (1 << 4)
#define SPECIAL        (1 << 5)
#define LOWER_CASE     (1 << 6)

const char *digits_large = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *digits_small = "0123456789abcdefghijklmnopqrstuvwxyz";

static char *num_to_base(char *str, int num, int base, int size,
                         int precision, int type)
{
    char c;
    char sign;
    char tmp[36];
    int i;
    const char *digits;

    /* Who uses base 37? */
    if (base < 2 || base > 36)
        return 0;
    
    digits = (type & LOWER_CASE) ? digits_small : digits_large;
    
    if (type & LEFT_JUSTIFIED)
        type &= ~PAD_ZEROES;
    
    c = (type & PAD_ZEROES) ? '0' : ' ';
    
    if (type & SIGNED && num < 0)
    {
        sign = '-';
        num = -num;
    }
    else
        sign = (type & PLUS) ? '+' : ((type & SPACE) ? ' ' : 0);

    if (sign)
        size--;
    if (type & SPECIAL)
        size = (base == 16) ? (size - 2) : ((base == 8) ? (size - 1) : size);

    i = 0;
    if (num == 0)
        tmp[i++] = '0';
    else
        while (num != 0)
            tmp[i++] = digits[do_div(num, base)];

    precision = (i > precision) ? i : precision;
    size -= precision;

    if (!(type & (PAD_ZEROES + LEFT_JUSTIFIED)))
        while (size-- > 0)
            *str++ = ' ';
    if (sign)
        *str++ = sign;
    if (type & SPECIAL)
    {
        if (base == 8 || base == 16)
            *str++ = '0';
        if (base == 16)
            *str++ = digits[33];
    }
    if (!(type & LEFT_JUSTIFIED))
        while (size-- > 0)
            *str++ = c;

    while (i < precision--)
        *str++ = '0';
    while (i-- > 0)
        *str++ = tmp[i];
    while (size-- > 0)
        *str++ = ' ';

    return str;
}

static int skip_atoi(const char **s)
{
    int i;

    i = 0;
    while (isdigit(**s))
        i = i * 10 + *((*s)++) - '0';

    return i;
}

int vsprintf(char *buf, const char *fmt, va_list args)
{
    int len;
    int i;
    int flags;
    int field_width;
    int precision;
    int *ip;
    char *str;
    char *s;

    for (str = buf; *fmt; fmt++)
    {
        /* No format character, carry on */
        if (*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }

        flags = 0;
    get_flags:
        fmt++;
        switch (*fmt)
        {
            case '-': flags |= LEFT_JUSTIFIED; goto get_flags;
            case '+': flags |= PLUS; goto get_flags;
            case ' ': flags |= SPACE; goto get_flags;
            case '#': flags |= SPECIAL; goto get_flags;
            case '0': flags |= PAD_ZEROES; goto get_flags;
        }

        field_width = -1;
        if (isdigit(*fmt))
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT_JUSTIFIED;
            }
        }

        precision = -1;
        if (*fmt == '.')
        {
            fmt++;
            if (isdigit(*fmt))
                precision = skip_atoi(&fmt);
            else if (*fmt == '*')
                precision = va_arg(args, int);
            precision = (precision < 0) ? 0 : precision;
        }

        switch (*fmt)
        {
            case 'c':
                if (!(flags & LEFT_JUSTIFIED))
                    while (--field_width > 0)
                        *str++ = ' ';
                *str++ = (unsigned char)va_arg(args, int);
                while (--field_width > 0)
                    *str++ = ' ';
                break;
                
            case 's':
                s = va_arg(args, char *);
                if (!s)
                    s = "NULL";
                
                len = strlen(s);
                if (precision < 0)
                    precision = len;
                else if (len > precision)
                    len = precision;

                if (!(flags & LEFT_JUSTIFIED))
                    while (len < field_width--)
                        *str++ = ' ';
                for (i = 0; i < len; i++)
                    *str++ = *s++;
                while (len < field_width--)
                    *str++ = ' ';
                break;
                
            case 'o':
                str = num_to_base(str, va_arg(args, unsigned long),
                                  8, field_width, precision, flags);
                break;
                
            case 'p':
                if (field_width == -1)
                {
                    field_width = 8;
                    flags |= PAD_ZEROES;
                }
                str = num_to_base(str, (unsigned long)va_arg(args, void *),
                                  16, field_width, precision, flags);
                break;
                
            case 'x':
                flags |= LOWER_CASE;
            case 'X':
                str = num_to_base(str, va_arg(args, unsigned long),
                                  16, field_width, precision, flags);
                break;
                
            case 'd':
            case 'i':
                flags |= SIGNED;
            case 'u':
                str = num_to_base(str, va_arg(args, unsigned long),
                                  10, field_width, precision, flags);
                break;
                
            case 'n':
                ip = va_arg(args, int *);
                *ip = (str - buf);
                break;
                
            default:
                if (*fmt != '%')
                    *str++ = '%';
                if (*fmt)
                    *str++ = *fmt;
                else
                    fmt--;
                break;
        }
    }
    
    *str = '\0';

    return str - buf;
}

int sprintf(char *buf, const char *fmt, ...)
{
    va_list args;
    int i;

    va_start(args, fmt);
    i = vsprintf(buf, fmt, args);
    va_end(args);

    return i;
}
