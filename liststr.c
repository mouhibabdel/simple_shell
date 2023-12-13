#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @listHead: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **listHead, const char *str, int num)
{
list_t *newNode;
if (!listHead)
{
return (NULL);
}
newNode = malloc(sizeof(list_t));
if (!newNode)
{
return (NULL);
}
_memset((void *)newNode, 0, sizeof(list_t));
newNode->num = num;
if (str)
{
newNode->str = _strdup(str);
if (!newNode->str)
{
free(newNode);
return (NULL);
}
}
newNode->next = *listHead;
*listHead = newNode;
return (newNode);
}
/**
 * add_node_end - adds a node to the end of the list
 * @listHead: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **listHead, const char *str, int num)
{
list_t *newNode, *node;
if (!listHead)
{
return (NULL);
}
node = *listHead;
newNode = malloc(sizeof(list_t));
if (!newNode)
{
return (NULL);
}
_memset((void *)newNode, 0, sizeof(list_t));
newNode->num = num;
if (str)
{
newNode->str = _strdup(str);
if (!newNode->str)
{
free(newNode);
return (NULL);
}
}
if (node)
{
while (node->next)
{
node = node->next;
}
node->next = newNode;
}
else
{
*listHead = newNode;
}
return (newNode);
}
/**
 * print_list_str - prints only the str element of a list_t linked list
 * @currentNode: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *currentNode)
{
size_t count = 0;
while (currentNode)
{
_puts(currentNode->str ? currentNode->str : "(nil)");
_puts("\n");
currentNode = currentNode->next;
count++;
}
return (count);
}
/**
 * delete_node_at_index - deletes node at given index
 * @listHead: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **listHead, unsigned int index)
{
list_t *node, *prevNode;
unsigned int currentIndex = 0;
if (!listHead || !*listHead)
{
return (0);
}
if (!index)
{
node = *listHead;
*listHead = (*listHead)->next;
free(node->str);
free(node);
return (1);
}
node = *listHead;
while (node)
{
if (currentIndex == index)
{
prevNode->next = node->next;
free(node->str);
free(node);
return (1);
}
currentIndex++;
prevNode = node;
node = node->next;
}
return (0);
}
/**
 * free_list - frees all nodes of a list
 * @listHead: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **listHead)
{
list_t *node, *nextNode, *head;
if (!listHead || !*listHead)
{
return;
}
head = *listHead;
node = head;
while (node)
{
nextNode = node->next;
free(node->str);
free(node);
node = nextNode;
}
*listHead = NULL;
}
