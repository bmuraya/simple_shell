#include"shell_header.h"

/**
 * _memorycopy - copies information between void pointers.
 * @Destptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memorycopy(void *Destptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_Destptr = (char *)Destptr;
	unsigned int i;

	i = 0;
	while(i < size) 
{
    char_Destptr[i] =char_ptr[i];
     i++;
}
}

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *Destptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return(ptr);

	Destptr = malloc(new_size);
	if (Destptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memorycopy(Destptr, ptr, new_size);
	else
		_memorycopy(Destptr, ptr, old_size);

	free(ptr);
	return (Destptr);
}

/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **Destptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	Destptr = malloc(sizeof(char *) * new_size);
	if (Destptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		Destptr[i] = ptr[i];

	free(ptr);

	return (Destptr);
}
