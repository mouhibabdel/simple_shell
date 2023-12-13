#include "shell.h"

/**
 * _put - prints an input string
 * @input_str: the string to be printed
 *
 * Return: Nothing
 */
void _put(char *input_str)
{
int index = 0;
if (!input_str)
{
return;
}
while (input_str[index] != '\0')
{
_eputchar(input_str[index]);
index++;
}
}
/**
 * _eptchar - writes the character c to stderr
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eptchar(char character)
{
static int buffer_index;
static char write_buffer[WRITE_BUF_SIZE];
if (character == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
{
write(2, write_buffer, buffer_index);
buffer_index = 0;
}
if (character != BUF_FLUSH)
{
write_buffer[buffer_index++] = character;
}
return (1);    
}
/**
 * _putfd - writes the character c to given fd
 * @character: The character to print
 * @file_descriptor: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char character, int file_descriptor)
{
static int buffer_index;
static char write_buffer[WRITE_BUF_SIZE];
if (character == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
{
write(file_descriptor, write_buffer, buffer_index);
buffer_index = 0;
}
if (character != BUF_FLUSH)
{
write_buffer[buffer_index++] = character;
}
return (1);
}
/**
 * _putsfd - prints an input string
 * @input_str: the string to be printed
 * @file_descriptor: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int _putsfd(char *input_str, int file_descriptor)
{
int index = 0;
if (!input_str)
{
return (0);
}
while (*input_str)
{
index += _putfd(*input_str++, file_descriptor);
}
return (index);
}
