#include "shell.h"

/**
 * initialize_info - initializes info_t struct
 * @info: struct pointer
 */
void initialize_info(info_t* info)
{
    info->argument_string = NULL;
    info->argument_array = NULL;
    info->path_string = NULL;
    info->argument_count = 0;
}

/**
 * set_info - sets the values in info_t struct
 * @info: struct pointer
 * @arguments: argument vector
 */
void set_info(info_t* info, char** arguments)
{
    int i = 0;

    info->file_name = arguments[0];
    if (info->argument_string)
    {
        info->argument_array = strtow(info->argument_string, " \t");
        if (!info->argument_array)
        {
            info->argument_array = malloc(sizeof(char*) * 2);
            if (info->argument_array)
            {
                info->argument_array[0] = _strdup(info->argument_string);
                info->argument_array[1] = NULL;
            }
        }
        for (i = 0; info->argument_array && info->argument_array[i]; i++)
            ;
        info->argument_count = i;

        replace_alias(info);
        replace_variables(info);
    }
}

/**
 * free_info - frees info_t struct fields
 * @info: struct pointer
 * @free_all: true if freeing all fields
 */
void free_info(info_t* info, int free_all)
{
    ffree(info->argument_array);
    info->argument_array = NULL;
    info->path_string = NULL;
    if (free_all)
    {
        if (!info->command_buffer)
            free(info->argument_string);
        if (info->environment_list)
            free_list(&(info->environment_list));
        if (info->history_list)
            free_list(&(info->history_list));
        if (info->alias_list)
            free_list(&(info->alias_list));
        ffree(info->environment_array);
        info->environment_array = NULL;
        bfree((void**)info->command_buffer);
        if (info->read_file_descriptor > 2)
            close(info->read_file_descriptor);
        _putchar(BUFFER_FLUSH);
    }
}

