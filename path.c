#include "shell.h"

/**
 * is_executable_command - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable_command(info_t *info, char *path)
{
struct stat file_stat;
(void)info;
if (!path || stat(path, &file_stat))
{
return (0);
}
if (file_stat.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
 * duplicate_characters - duplicates characters
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_characters(char *path_str, int start, int stop)
{
static char buffer[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
{
if (path_str[i] != ':')
{
buffer[k++] = path_str[i];
}
}
buffer[k] = 0;
}
/**
 * find_command_path - finds the command in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of the command if found or NULL
 */
char *find_command_path(info_t *info, char *path_str, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!path_str)
{
return (NULL);
}
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_executable_command(info, cmd))
{
return (cmd);
}
}
while (1)
{
if (!path_str[i] || path_str[i] == ':')
{
path = duplicate_characters(path_str, curr_pos, i);
if (!*path)
{
_strcat(path, cmd);
}
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_executable_command(info, path))
{
return (path);
}
if (!path_str[i])
{
break;
}
curr_pos = i;
}
i++;
}
return (NULL);
}
