#include "shell.h"

/**
 * _myexit - exits the shell
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if shell_info.argv[0] != "exit"
 */
int _myexit(shell_info_t *shell_info)
{
int exit_check;
if (shell_info->argv[1])
{
exit_check = _erratoi(shell_info->argv[1]);
if (exit_check == -1)
{
shell_info->status = 2;
print_error(shell_info, "Illegal number: ");
_eputs(shell_info->argv[1]);
_eputchar('\n');
return (1);
}
shell_info->err_num = _erratoi(shell_info->argv[1]);
return (-2);
}
shell_info->err_num = -1;
return (-2);
}
/**
 * _mycd - changes the current directory of the process
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 *  Return: Always 0
 */
int _mycd(shell_info_t *shell_info)
{
char *current_dir, *target_dir, buffer[1024];
int chdir_ret;
current_dir = getcwd(buffer, 1024);
if (!current_dir)
{
_puts("TODO: >>getcwd failure emsg here<<\n");
}
if (!shell_info->argv[1])
{
target_dir = _getenv(shell_info, "HOME=");
if (!target_dir)
{
chdir_ret = chdir((target_dir = _getenv(shell_info, "PWD=")) ? target_dir : "/");
}
else
{
chdir_ret = chdir(target_dir);
}
}
else if (_strcmp(shell_info->argv[1], "-") == 0)
{
if (!_getenv(shell_info, "OLDPWD="))
{
_puts(current_dir);
_putchar('\n');
return (1);
}
_puts(_getenv(shell_info, "OLDPWD=")), _putchar('\n');
chdir_ret = chdir((target_dir = _getenv(shell_info, "OLDPWD=")) ? target_dir : "/");
}
else
{    
chdir_ret = chdir(shell_info->argv[1]);
}
if (chdir_ret == -1)
{
print_error(shell_info, "can't cd to ");
_eputs(shell_info->argv[1]), _eputchar('\n');
}
else
{
_setenv(shell_info, "OLDPWD", _getenv(shell_info, "PWD="));
_setenv(shell_info, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
 * _myhelp - changes the current directory of the process
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 *  Return: Always 0
 */
int _myhelp(shell_info_t *shell_info)
{
char **arg_array;
arg_array = shell_info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
{
_puts(*arg_array);
}
return (0);
}
