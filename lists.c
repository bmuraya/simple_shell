#include "shell_header.h"

/**
 * addseparator_node_end - adds a separator
 * found at the end of a sp_list.
 *
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
sp_list *addseparator_node_end(sp_list **head, char sep)
{
	sp_list *new, *temp;

	new = malloc(sizeof(sp_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 *  freeline_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void freeline_list(line_list **head)
{
	line_list *temp, *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 *  addlinenode - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *addlinenode(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

