#include "shell.h"

/**
 * _custom_memset - fills memory with a constant byte
 * @dest: the pointer to the memory area
 * @byte: the byte to fill *dest with
 * @size: the amount of bytes to be filled
 * Return: (dest) a pointer to the memory area dest
 */
char *_custom_memset(char *dest, char byte, unsigned int size)
{
unsigned int i;
for (i = 0; i < size; i++)
{
dest[i] = byte;
}
return (dest);
}
/**
 * custom_free - frees a string of strings
 * @str_arr: string of strings
 */
void custom_free(char **str_arr)
{
char **temp = str_arr;
if (!str_arr)
{
return;
}
while (*str_arr)
{
free(*str_arr++);
}
free(temp);
}

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 * Return: pointer to the old block
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *new_ptr;
if (!ptr)
{
return (malloc(new_size));
}
if (!new_size)
{
free(ptr);
return (NULL);
}
if (new_size == old_size)
{
return (ptr);
}
new_ptr = malloc(new_size);
if (!new_ptr)
{
return (NULL);
}
old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
{
new_ptr[old_size] = ((char *)ptr)[old_size];
}
free(ptr);
return (new_ptr);
}
