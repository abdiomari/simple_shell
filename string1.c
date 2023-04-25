#include "shell.h"

/**
 * _copy_string - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */

char *_copy_string(char *dest, char *src)
{
int i = 0;

if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}

/**
 * _duplicate_string - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_duplicate_string(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
 * _print_string - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _print_string(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_put_character(str[i]);
i++;
}
}

/**
 * _put_character - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _put_character(char c)
{
static int i;
static char buffer[WRITE_BUFFER_SIZE];

if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
{
write(1, buffer, i);
i = 0;
}
if (c != BUFFER_FLUSH)
buffer[i++] = c;
return (1);
}

