#include "shell.h"

/**
 * display_history - displays the history list, one command by line, preceded
 *                   with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info)
{
print_list(info->history);
return (0);
}
/**
 * remove_alias - removes an alias based on string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *str)
{
char *equal_sign_pos, temp_char;
int ret;
equal_sign_pos = _strchr(str, '=');
if (!equal_sign_pos)
{
return (1);
temp_char = *equal_sign_pos;
*equal_sign_pos = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*equal_sign_pos = temp_char;
return (ret);
}
/**
 * set_alias - sets an alias to a string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
char *equal_sign_pos;
equal_sign_pos = _strchr(str, '=');
if (!equal_sign_pos)
{
return (1);
if (!*++equal_sign_pos)
{
return (remove_alias(info, str));
}
remove_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
char *equal_sign_pos = NULL, *alias_string = NULL;
if (node)
{
equal_sign_pos = _strchr(node->str, '=');
for (alias_string = node->str; alias_string <= equal_sign_pos; alias_string++)
{
_putchar(*alias_string);
}
_putchar('\'');
_puts(equal_sign_pos + 1);
_puts("'\n");
return (0);
}
return (1);
}
/**
 * manage_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int manage_alias(info_t *info)
{
int i = 0;
char *equal_sign_pos = NULL;
list_t *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
equal_sign_pos = _strchr(info->argv[i], '=');
if (equal_sign_pos)
{
set_alias(info, info->argv[i]);
}
else
{
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}
}
return (0);
}
