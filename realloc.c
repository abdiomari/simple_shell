#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: pointer to the memory area
 * @b: the byte to fill the memory with
 * @n: the amount of bytes to be filled
 *
 * Return: a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
 * free_str_arr - frees a null-terminated array of strings
 * @str_arr: the array of strings to free
 */
void free_str_arr(char **str_arr)
{
char **arr = str_arr;

if (!str_arr)
return;
while (*str_arr)
free(*str_arr++);
free(arr);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous allocated block
 * @old_size: size of previous block in bytes
 * @new_size: size of new block in bytes
 *
 * Return: pointer to the newly reallocated block of memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;

if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);

p = malloc(new_size);
if (!p)
return (NULL);

old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (p);
}

