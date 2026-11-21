This project has been created as part of the 42 curriculum by dalinein.

ft_printf
Description

ft_printf() is a reimplementation of the C printf() function. It writes the formatted output to the standard output and returns the number of characters printed, or -1 if a write() fails.

Supported conversions:

Conversion	Prints
%c	a single character
%s	a string ((null) if the pointer is NULL)
%p	a pointer in hexadecimal, prefixed by 0x ((nil) for NULL)
%d, %i	a signed decimal integer
%u	an unsigned decimal integer
%x, %X	an unsigned integer in lowercase / uppercase hexadecimal
%%	a percent sign

The project is built as a static library, libftprintf.a.

Instructions

Build the library:

make

Other rules: make clean (remove the object files), make fclean (also remove the library), make re (rebuild from scratch).

Use it in a program:

c
#include "ft_printf.h"

int	main(void)
{
	int	n;

	n = ft_printf("Hello %s, you are %d years old (0x%x)\n", "Sara", 25, 255);
	ft_printf("%d characters were printed\n", n);
	return (0);
}
cc main.c -I. -L. -lftprintf -o test

Source files are in printf_src/ and the header ft_printf.h is at the root of the repository.

Algorithm

ft_printf() makes a single pass over the format string with a va_list:

A normal character is written directly with write().
When a % is found, the next character is given to ft_handle_format(), which picks the right function for the conversion and reads the matching argument with va_arg. The va_list is passed by pointer, so each argument is consumed exactly once.
Every function returns the number of characters it printed, or -1 on error. ft_printf() adds the counts, and stops immediately and returns -1 as soon as one call fails.

Number printing is recursive: to print n in a base, the function first prints n / base (the more significant digits) and then the last digit, n % base. This prints the digits in the right order without a buffer or any dynamic allocation. The same function structure is used for decimal (%d, %i, %u) and hexadecimal (%x, %X, %p). For %d, the value is converted to long long first so that INT_MIN can be negated safely.

Why this approach:

No malloc, so no memory to free and no leak is possible.
Each conversion lives in its own small function, which keeps the code short and easy to test.
Passing errors up through the return values makes the function behave like the real printf() when write() fails.
Trade-off: one write() call per character is slower than filling a buffer and writing once, but it keeps the code simple and the output order always correct.
Resources
man 3 printf, man 3 stdarg, man 2 write
The 42 subject for ft_printf
How AI was used

### How AI was used

AI  was used only as a learning and debugging assistant. It helped me break down functions into smaller parts, understand the requirements and responsibilities of each function, and debug the project by tracing and identifying errors. No code was written by AI; all code was implemented by me.