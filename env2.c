#include "shell.h"

/**
 * get_environment - returns the string array copy of our environment
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 * Return: Always 0
 */
char **get_environment(shell_info_t *shell_info)
{
if (!shell_info->environment || shell_info->env_changed)
{
shell_info->environment = list_to_strings(shell_info->env_list);
shell_info->env_changed = 0;
}
return (shell_info->environment);
}
/**
 * unset_env_variable - Remove an environment variable
 * @shell_info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * @variable: the string env variable property
 * Return: 1 on delete, 0 otherwise
 */
int unset_env_variable(shell_info_t *shell_info, char *variable)
{
list_t *node = shell_info->env_list;
size_t index = 0;
char *p;
if (!node || !variable)
{
return (0);
}
while (node)
{
p = starts_with(node->str, variable);
if (p && *p == '=')
{
shell_info->env_changed = delete_node_at_index(&(shell_info->env_list), index);
index = 0;
node = shell_info->env_list;
continue;
}
node = node->next;
index++;
}
return (shell_info->env_changed);
}
/**
 * set_environment_variable - Initialize a new environment variable,
 *                            or modify an existing one
 * @shell_info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * @variable: the string env variable property
 * @value: the string env variable value
 * Return: Always 0
 */
int set_env_variable(shell_info_t *shell_info, char *variable, char *value)
{
char *buffer = NULL;
list_t *node;
char *p;
if (!variable || !value)
{
return (0);
}
buffer = malloc(_strlen(variable) + _strlen(value) + 2);
if (!buffer)
{
return (1);
}
_strcpy(buffer, variable);
_strcat(buffer, "=");
_strcat(buffer, value);
node = shell_info->env_list;
while (node)
{
p = starts_with(node->str, variable);
if (p && *p == '=')
{
free(node->str);
node->str = buffer;
shell_info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(shell_info->env_list), buffer, 0);
free(buffer);
shell_info->env_changed = 1;
return (0);
}
