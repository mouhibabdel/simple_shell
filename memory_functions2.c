#include "shell.h"

/**
 * costum_bfree - frees a pointer and NULLs the address
 * @poitr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int costum_bfree(void **poitr)
{
if (poitr && *poitr)
{
free(*poitr);
*poitr = NULL;
return (1);
}
return (0);
}
