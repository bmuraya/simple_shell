#include "shell_header.h"

/**
 * _memorycopy - copies information between void pointers.
 * @dstptr:  destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memorycopy(void *dstptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_dstptr = (char *)dstptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_dstptr[i] = char_ptr[i];
}

/**
 * relc_mem - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **relc_mem(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **dstptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	dstptr = malloc(sizeof(char *) * new_size);
	if (dstptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		dstptr[i] = ptr[i];

	free(ptr);

	return (dstptr);
}

/**
 * realloc_mem_blc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *realloc_mem_blc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *dstptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	dstptr = malloc(new_size);
	if (dstptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memorycopy(dstptr, ptr, new_size);
	else
		_memorycopy(dstptr, ptr, old_size);

	free(ptr);
	return (dstptr);
}
