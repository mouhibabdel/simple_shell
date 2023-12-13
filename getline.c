#include "shell.h"

/**
 * bufferInput - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: bytes read
 */
ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
{
ssize_t bytesRead = 0;
size_t bufferLength = 0;
if (!*length)
{
free(*buffer);
*buffer = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
#else
bytesRead = _getline(info, buffer, &bufferLength);
#endif
if (bytesRead > 0)
{
if ((*buffer)[bytesRead - 1] == '\n')
{
(*buffer)[bytesRead - 1] = '\0';
bytesRead--;
}
info->linecountFlag = 1;
removeComments(*buffer);
buildHistoryList(info, *buffer, info->histcount++);
{
*length = bytesRead;
info->cmdBuffer = buffer;
}
}
}
return (bytesRead);
}
/**
 * getInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(info_t *info)
{
static char *buffer;
static size_t i, j, length;
ssize_t bytesRead = 0;
char **bufferPointer = &(info->arg), *p;
_putchar(BUF_FLUSH);
bytesRead = bufferInput(info, &buffer, &length);
if (bytesRead == -1)
{
return (-1);
}
if (length)
{
j = i;
p = buffer + i;
checkChain(info, buffer, &j, i, length);
while (j < length)
{
if (isChain(info, buffer, &j))
{
break;
}
j++;
}
i = j + 1;
if (i >= length)
{
i = length = 0;
info->cmdBufferType = CMD_NORM;
}
*bufferPointer = p;
return (_strlen(p));
}
*bufferPointer = buffer;
return bytesRead;
}
/**
 * readBuffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *i)
{
ssize_t bytesRead = 0;
if (*i)
{
return (0);
}
bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
if (bytesRead >= 0)
*i = bytesRead;
return bytesRead;
}
/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buffer[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t bytesRead = 0, size = 0;
char *p = NULL, *newP = NULL, *c;
p = *ptr;
if (p && length)
{
size = *length;
}
if (i == len)
{
i = len = 0;
}
bytesRead = readBuffer(info, buffer, &len);
if (bytesRead == -1 || (bytesRead == 0 && len == 0))
{
return (-1);
}
c = _strchr(buffer + i, '\n');
k = c ? 1 + (unsigned int)(c - buffer) : len;
newP = _realloc(p, size, size ? size + k : k + 1);
if (!newP)
{
return (p ? free(p), -1 : -1);
}
if (size)
{
_strncat(newP, buffer + i, k - i);
}
else
{
_strncpy(newP, buffer + i, k - i + 1);
}
size += k - i;
i = k;
p = newP;
if (length)
{
*length = size;
}
*ptr = p;
return (size);
}
/**
 * sigintHandler - blocks ctrl-C
 * @sigNum: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sigNum)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
