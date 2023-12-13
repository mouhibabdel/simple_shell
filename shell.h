#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
extern char **environ;
/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;
/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **cmd_buf;
int cmd_buf_type;
int readfd;
int histcount;
} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;
int shell_loop(info_t *, char **);
int find_builtin_command(info_t *);
void find_command(info_t *);
void fork_exec_command(info_t *);
int is_executable_command(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *find_command_path(info_t *, char *, char *);
int loophsh(char **);
void _put(char *);
int _eptchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int fin_strlen(char *);
int fin_strcmp(char *, char *);
char *fin_starts_with(const char *, const char *);
char *fin_strcat(char *, char *);
char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int print_character(char);
char *_custom_strncpy(char *, char *, int);
char *_custom_strncat(char *, char *, int);
char *_custom_strchr(char *, char);
char **splitString(char *, char *);
char **splitString2(char *, char);
char *_custom_memset(char *, char, unsigned int);
void custom_free(char **);
void *custom_realloc(void *, unsigned int, unsigned int);
int costum_bfree(void **);
int isInteractiveMode(info_t *);
int isDelimiter(char, char *);
int isAlpha(int);
int stringToInteger(char *);
int covtStrToInt(char *);
void printError(info_t *, char *);
int printDecimal(int, int);
char *convertNumber(long int, int, int);
void removeComments(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int display_history(info_t *);
int manage_alias(info_t *);
ssize_t bufferInput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void clr_info(info_t *);
void set_inf(info_t *, char **);
void free_inf(info_t *, int);
char *_getEnvValue(info_t *, const char *);
int _displayEnvironment(info_t *);
int _setEnviVariable(info_t *);
int _unsetEnvVariable(info_t *);
int populate_env_list(info_t *);
char **get_environment(info_t *);
int unset_env_variable(info_t *, char *);
int set_env_variable(info_t *, char *, char *);
char *get_hist_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t free_list_length(const list_t *);
char **lst_to_strings(list_t *);
size_t print_lst(const list_t *);
list_t *node_star_with(list_t *, char *, char);
ssize_t get_node_ind(list_t *, list_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
