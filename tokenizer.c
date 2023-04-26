#include "shell.h"

/**
 * split_string - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @delimiter: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **split_string(char *str, char *delimiter)
{
int i, j, k, m, num_words = 0;
char **words;

if (str == NULL || str[0] == 0)
return (NULL);
if (!delimiter)
delimiter = " ";
for (i = 0; str[i] != '\0'; i++)
if (!is_delimiter(str[i], delimiter) &&
(is_delimiter(str[i + 1], delimiter) || !str[i + 1]))
num_words++;
if (num_words == 0)
return (NULL);

words = malloc((1 + num_words) *sizeof(char *));
if (!words)
return (NULL);

for (i = 0, j = 0; j < num_words; j++)
{
while (is_delimiter(str[i], delimiter))
i++;
k = 0;
while (!is_delimiter(str[i + k], delimiter) && str[i + k])
k++;
words[j] = malloc((k + 1) * sizeof(char));
if (!words[j])
{
for (k = 0; k < j; k++)
free(words[k]);
free(words);
return (NULL);
}
for (m = 0; m < k; m++)
words[j][m] = str[i++];
words[j][m] = 0;
}
words[j] = NULL;
return (words);
}

/**
 * split_string - Splits the input string into an array of words
 * @input_string: The input string to be split
 * @delimiter: The character used to delimit the words
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */

char **split_string(char *input_string, char delimiter)
{
int i, j, k, m, num_words = 0;
char **words_array;

if (input_string == NULL || input_string[0] == '\0')
return (NULL);

for (i = 0; input_string[i] != '\0'; i++)
if ((input_string[i] != delimiter && input_string[i + 1] == delimiter) ||
(input_string[i] != delimiter && !input_string[i + 1]) ||
input_string[i + 1] == delimiter)
num_words++;

if (num_words == 0)
return (NULL);

words_array = malloc((1 + num_words) *sizeof(char *));
if (!words_array)
return (NULL);
for (i = 0, j = 0; j < num_words; j++)
{
while (input_string[i] == delimiter && input_string[i] != delimiter)
i++;
k = 0;
while (input_string[i + k] != delimiter && input_string[i + k] &&
input_string[i + k] != delimiter)
k++;
words_array[j] = malloc((k + 1) * sizeof(char));
if (!words_array[j])
{
for (k = 0; k < j; k++)
free(words_array[k]);
free(words_array);
return (NULL);
}
for (m = 0; m < k; m++)
words_array[j][m] = input_string[i++];
words_array[j][m] = '\0';
}
words_array[j] = NULL;
return (words_array);
}

