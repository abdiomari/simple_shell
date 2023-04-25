#include "shell.h"

/**
 * get_hist_file - returns a string containing the path
 * to the history file
 * @info: of type info_t* pointer to a struct containing 
 * about the shells current state
 *
 *
 * Return: returns buf which contains the full path
 * to the history file 
 */

char* get_hist_file(info_t* info)
{
	char* buf, * dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist_file - writes the contents of a linked list of commands 
 * to a history file
 * @info: of type  info_t* which is a pointer to a struct containing 
 * information about the shells current state
 *
 * Return: '1' on success, otherwise '-1'
 */
int write_hist_file(info_t* info)
{
	ssize_t fd;
	char* filename = get_history_file(info);
	list_t* node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist_file - reads history from file
 * and builds a linked list of commands in memory
 * @info: pointer to a struct containing info 
 *about the shells current state
 *
 * Return: final value of histcount
 */
int read_hist_file(info_t* info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char* buf = NULL, * filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_hist_file - adds an entry to a linked list 
 * that represents the comand history 
 * @info: of type info_t* pointer to a structure
 * @buf: of type char* buffer to update history
 * @linecount: of type int the history linecount
 *
 * Return: 0
 */
int build_hist_file(info_t* info, char* buf, int linecount)
{
	list_t* node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_hist_file - updates the line numbers the 
 * of each node in the history linked list after any changes
 * have been made
 * @info: of type info_t* a structure containing 
 * potential arguments
 *
 * Return: the value of info-> histcount
 */
int renumber_hist_file(info_t* info)
{
	list_t* node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

