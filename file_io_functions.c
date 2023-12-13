#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_hist_file(info_t *info)
{
char *homeDir, *historyFilePath;
homeDir = _getenv(info, "HOME=");
if (!homeDir)
{
return (NULL);
}
historyFilePath = malloc(sizeof(char) * (_strlen(homeDir) + _strlen(HIST_FILE) + 2));
if (!historyFilePath)
{
return (NULL);
}
historyFilePath[0] = 0;
_strcpy(historyFilePath, homeDir);
_strcat(historyFilePath, "/");
_strcat(historyFilePath, HIST_FILE);
return (historyFilePath);
}
/**
 * write_hist - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(info_t *info)
{
ssize_t fileDescriptor;
char *filename = get_history_file(info);
list_t *currentNode = NULL;
if (!filename)
{
return (-1);
}
fileDescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fileDescriptor == -1)
{
return (-1);
}
for (currentNode = info->history; currentNode; currentNode = currentNode->next)
{
_putsfd(currentNode->str, fileDescriptor);
_putfd('\n', fileDescriptor);
}
_putfd(BUF_FLUSH, fileDescriptor);
close(fileDescriptor);
return (1);
}
/**
 * read_hist - reads history from file
 * @info: the parameter struct
 *
 * Return: histCount on success, 0 otherwise
 */
int read_hist(info_t *info)
{
int i, last = 0, lineCount = 0;
ssize_t fileDescriptor, readLength, fileSize = 0;
struct stat fileStat;
char *buffer = NULL, *filename = get_history_file(info);
if (!filename)
{
return (0);
}
fileDescriptor = open(filename, O_RDONLY);
free(filename);
if (fileDescriptor == -1)
{
return (0);
}
if (!fstat(fileDescriptor, &fileStat))
{
fileSize = fileStat.st_size;
}
if (fileSize < 2)
{
return (0);
}
buffer = malloc(sizeof(char) * (fileSize + 1));
if (!buffer)
{
return (0);
}
readLength = read(fileDescriptor, buffer, fileSize);
buffer[fileSize] = 0;
if (readLength <= 0)
{
return (free(buffer), 0);
}
close(fileDescriptor);
for (i = 0; i < fileSize; i++)
{
if (buffer[i] == '\n')
{
buffer[i] = 0;
build_history_list(info, buffer + last, lineCount++);
last = i + 1;
}
}
if (last != i)
{
build_history_list(info, buffer + last, lineCount++);
}
free(buffer);
info->histCount = lineCount;
while (info->histCount-- >= HIST_MAX)
{
delete_node_at_index(&(info->history), 0);
}
renumber_history(info);
return (info->histCount);
}
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @lineCount: the history lineCount, histCount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buffer, int lineCount)
{
list_t *currentNode = NULL;
if (info->history)
{
currentNode = info->history;
}
add_node_end(&currentNode, buffer, lineCount);
if (!info->history)
{
info->history = currentNode;
}
return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histCount
 */
int renumber_history(info_t *info)
{
list_t *currentNode = info->history;
int i = 0;
while (currentNode)
{
currentNode->num = i++;
currentNode = currentNode->next;
}
return (info->histCount = i);
}
