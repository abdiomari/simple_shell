
/**
 * _sstrncpy - copies a string
 *
 * @dest: pointer to the destination buffer
 * @src: pointer to the source string
 * @n: maximum number of characters to copy
 *
 * Return: pointer to the destination buffer
 */
char *_sstrncpy(char *dest, const char *src, size_t n)
{
    char *dest_start = dest;
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    for (; i < n; i++)
    {
        dest[i] = '\0';
    }

    return dest_start;
}

/**
 * _sstrncat - concatenates two strings
 *
 * @dest: pointer to the destination buffer
 * @src: pointer to the source string
 * @n: maximum number of characters to concatenate
 *
 * Return: pointer to the destination buffer
 */
char *_sstrncat(char *dest, const char *src, size_t n)
{
    char *dest_start = dest;
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';

    return dest_start;
}

/**
 * _sstrchr - locates a character in a string
 *
 * @s: pointer to the string to search
 * @c: the character to search for
 *
 * Return: pointer to the first occurrence of @c in @s, or NULL if not found
 */
char *_sstrchr(const char *s, int c)
{
    for (; *s != '\0'; s++)
    {
        if (*s == c)
        {
            return (char *)s;
        }
    }

    return NULL;
}

