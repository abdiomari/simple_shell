#include "shell.h"

/**
*is_executable - determines if a file is an executable command
*@info: a pointer to the info struct
*@path: a string containing the path to the file
*Return: 1 if true, 0 otherwise
*/

int is_executable(info_t *info, char *path)
{
struct stat st;

(void)info;

if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
return (1);

return (0);
}

/**
*duplicate_chars - duplicates characters in a given range of a string
*@str: the string to duplicate characters from
*@start: the starting index of the range
*@stop: the stopping index of the range
*Return: pointer to new buffer containing the duplicated characters
*/

char *duplicate_chars(char *str, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (str[i] != ':')
buf[k++] = str[i];
buf[k] = 0;
return (buf);
}

/**
*find_cmd_path - finds the path to a command in the PATH environment variable
*@info: a pointer to the info struct
*@pathstr: the PATH environment variable string
*@cmd: the command to find
*Return: a pointer to a string containing the full path of the
*command if found, or NULL
*/

char *find_cmd_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);

/* check if cmd is in the current directory */
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_executable(info, cmd))
return (cmd);
}

while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = duplicate_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_executable(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
