#include "shell_header.h"
/**
 * free_sp_list - frees a sp_list
 *
 * @head: head of the linked list.
 * Return: no return.
 */

void free_sp_list(sp_list **head)
{
	sp_list *curr, *temp;

	if (head != NULL)
	{
		curr = *head;
		while (curr != NULL)
		{
			temp = curr;
			curr = curr->next;
			free(temp);
		}

		*head = NULL;
	}
}


/**
 * addVar_node - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_var *addVar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

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
 *  free_Var_node - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_Var_node(r_var **head)
{
	r_var *temp, *curr;

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
