#include "main.h"
#include <stdio.h>

int print_char(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char c = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

int print_string(va_list types, char buffer[], int flags, int width,
                int precision, int size)
{
	int length, i;
	char *str = va_arg(types, char *);

	length = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "   ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision <length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
					return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}
int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(size);
        UNUSED(precision);
	UNUSED(types);
	return (write(1, "%%", 1));
}
int print_int(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i, is_negative;
	long int n;
	unsigned long int num;

	i = BUFF_SIZE - 2;
	is_negative = 0;
	n = va_arg(types, long int);
	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

int print_binary(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(size);
        UNUSED(precision);

	n = va_arg(types, unsigned int);
	m = 2147483648;
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z;
			z = '0' + a[i];
			write(1, &z, 1);
			count ++;
		}
	}
	return (count);
}




