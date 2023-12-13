#include "shell.h"

/**
 * copy_string - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *copy_string(char *destination, char *source)
{
int index = 0;
if (destination == source || source == NULL)
{
return (destination);
}
while (source[index])
{
destination[index] = source[index];
index++;
}
destination[index] = 0;
return (destination);
}
/**
 * duplicate_string - duplicates a string
 * @str_to_duplicate: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *duplicate_string(const char *str_to_duplicate)
{
int length = 0;
char *result;
if (str_to_duplicate == NULL)
{
return (NULL);
}
while (*str_to_duplicate++)
{
length++;
}
result = malloc(sizeof(char) * (length + 1));
if (!result)
{
return (NULL);
}
for (length++; length--;)
{
result[length] = *--str_to_duplicate;
}
return (result);
}
/**
 * print_string - prints an input string
 * @str_to_print: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str_to_print)
{
int index = 0;
if (!str_to_print)
{
return;
}
while (str_to_print[index] != '\0')
{
print_character(str_to_print[index]);
index++;
}
}
/**
 * print_character - writes the character c to stdout
 * @character_to_print: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_character(char character_to_print)
{
static int i;
static char buffer[WRITE_BUFFER_SIZE];
if (character_to_print == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
{
write(1, buffer, i);
i = 0;
}
if (character_to_print != BUFFER_FLUSH)
{
buffer[i++] = character_to_print;
}
return (1);
}
