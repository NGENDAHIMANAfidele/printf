#include "main.h"
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count;

   count = 0;
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c': {
                    char c = (char) va_arg(args, int);
                    putchar(c);
                    count++;
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char *);
		    int i;

                    for (i = 0; s[i] != '\0'; i++) {
                        putchar(s[i]);
                        count++;
                    }
                    break;
                }
                case '%': {
                    putchar('%');
                    count++;
                    break;
                }
            }
        } else {
            putchar(*format);
            count++;
        }
        format++;
    }
    va_end(args);
    return count;
}
