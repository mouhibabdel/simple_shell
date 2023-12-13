#include "shell.h"
/**
 * free_list_length - determines the length of a linked list
 * @current_node: pointer to the first node
 *
 * Return: size of the list
 */
size_t free_list_length(const list_t *current_node)
{
size_t size = 0;
while (current_node)
{
current_node = current_node->next;
size++;
}
return (size);
}
/**
 * lst_to_strings - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **lst_to_strings(list_t *head)
{
list_t *current_node = head;
size_t size = list_length(head), index;
char **strings_array;
char *current_str;
if (!head || !size)
{
return (NULL);
}
strings_array = malloc(sizeof(char *) * (size + 1));
if (!strings_array)
{
return (NULL);
}
for (index = 0; current_node; current_node = current_node->next, index++)
{
current_str = malloc(_strlen(current_node->str) + 1);
if (!current_str)
{
for (size_t j = 0; j < index; j++)
{
free(strings_array[j]);
}
free(strings_array);
return (NULL);
}
current_str = _strcpy(current_str, current_node->str);
strings_array[index] = current_str;
}
strings_array[index] = NULL;
return (strings_array);
}
/**
 * print_lst - prints all elements of a list_t linked list
 * @current_node: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_lst(const list_t *current_node)
{
size_t size = 0;
while (current_node)
{
_puts(convert_number(current_node->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(current_node->str ? current_node->str : "(nil)");
_puts("\n");
current_node = current_node->next;
size++;
}
return (size);
}
/**
 * node_star_with - returns a node whose string starts with a prefix
 * @current_node: pointer to the list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or null
 */
list_t *node_star_with(list_t *current_node, char *prefix, char c)
{
char *p = NULL;
while (current_node)
{
p = starts_with(current_node->str, prefix);
if (p && ((c == -1) || (*p == c)))
{
return (current_node);
}
current_node = current_node->next;
}
return (NULL);
}
/**
 * get_node_ind - gets the index of a node
 * @head: pointer to the list head
 * @current_node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_ind(list_t *head, list_t *current_node)
{
size_t index = 0;
while (head)
{
if (head == current_node)
{
return index;
}
head = head->next;
index++;
}
return (-1);
}
