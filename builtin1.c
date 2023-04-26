
#include "shell.h"

/**
 * exit_shell - exits the shell
 * @shell_info: Pointer to a structure containing potential arguments. Used to
 *              maintain constant function prototype.
 *
 * Return: exits with a given exit status
 *         (0) if shell_info->argv[0] != "exit"
 */

int exit_shell(shell_info_t *shell_info)
{
int exit_code;

if (shell_info->argv[1])
{
exit_code = str_to_int(shell_info->argv[1]);
if (exit_code == -1)
{
shell_info->status = 2;
print_error(shell_info, "Illegal number: ");
print_string(shell_info->argv[1]);
print_string("\n");
return 1;
}
shell_info->err_num = exit_code;
return -2;
}
shell_info->err_num = -1;
return -2;
}

/**
 * change_directory - changes the current directory of the process
 * @shell_info: Pointer to a structure containing potential arguments. Used to
 *              maintain constant function prototype.
 *
 * Return: Always 0
 */
int change_directory(shell_info_t *shell_info)
{
char *dir, *s, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
print_string("TODO: >>getcwd failure emsg here<<\n");

if (!shell_info->argv[1])
{
dir = get_env(shell_info, "HOME=");

if (!dir)
chdir_ret = /* TODO: what should this be? */
chdir((dir = get_env(shell_info, "PWD=")) ? dir : "/");

else
chdir_ret = chdir(dir);
}
    
else if (strcmp(shell_info->argv[1], "-") == 0)
{
if (!get_env(shell_info, "OLDPWD="))
{
print_string(s);
print_char('\n');
return 1;
}
print_string(get_env(shell_info, "OLDPWD="));
print_char('\n');
chdir_ret = /* TODO: what should this be? */
chdir((dir = get_env(shell_info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(shell_info->argv[1]);

if (chdir_ret == -1)
{
print_error(shell_info, "can't cd to ");
print_string(shell_info->argv[1]);
print_char('\n');
}
else
{
set_env(shell_info, "OLDPWD", get_env(shell_info, "PWD="));
set_env(shell_info, "PWD", getcwd(buffer, 1024));
}
return 0;
}

/**
 * help_shell - displays information about built-in shell commands
 * @shell_info: Pointer to a structure containing potential arguments. Used to
 *              maintain constant function prototype.
 *
 * Return: Always 0
 */

int help_shell(shell_info_t *shell_info)
{
char **arg_array;

arg_array = shell_info->argv;
print_string("help call works. Function not yet implemented \n");
if (0)
print_string(*arg_array); /* temp att_unused workaround */
return 0;
}

