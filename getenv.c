#include "shell.h"

/**
 * get_env_strings - Returns a copy of our environment variables as an array of strings
 * @info: A pointer to a struct containing potential arguments
 * Return: A copy of our environment variables as an array of strings
 */
char **get_env_strings(info_t *info)
{
    if (!info->env_strings || info->env_changed)
    {
        info->env_strings = list_to_string_array(info->env_list);
        info->env_changed = 0;
    }
    return (info->env_strings);
}

/**
 * remove_env_var - Removes an environment variable
 * @info: A pointer to a struct containing potential arguments
 * @var_name: The name of the environment variable to remove
 * Return: 1 if the variable was removed, 0 otherwise
 */
int remove_env_var(info_t *info, char *var_name)
{
    list_t *node = info->env_list;
    size_t i = 0;
    char *p;

    if (!node || !var_name)
        return (0);

    while (node)
    {
        p = starts_with(node->str, var_name);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env_list), i);
            i = 0;
            node = info->env_list;
            continue;
        }
        node = node->next;
        i++;
    }
    return (info->env_changed);
}

/**
 * set_env_var - Initializes a new environment variable or modifies an existing one
 * @info: A pointer to a struct containing potential arguments
 * @var_name: The name of the environment variable to initialize or modify
 * @value: The value of the environment variable to set or modify
 * Return: Always 0
 */
int set_env_var(info_t *info, char *var_name, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var_name || !value)
        return (0);

    buf = malloc(_strlen(var_name) + _strlen(value) + 2);
    if (!buf)
        return (1);

    _strcpy(buf, var_name);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env_list;

    while (node)
    {
        p = starts_with(node->str, var_name);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }

    add_node_end(&(info->env_list), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}

