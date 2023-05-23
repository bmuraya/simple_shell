#include"shell_header.h"

/**
 * addseparator_node_end - adds a separator found at the end
 * of a separatorlist.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
separatorlist *addseparator_node_end(separatorlist **head, char sep) {
    separatorlist *new, *temp;

    new = malloc(sizeof(separatorlist));
    if (new == NULL)
        return NULL;

    new->separator = sep;
    new->next = NULL;
    temp = *head;

    if (temp == NULL) {
        *head = new;
    } else {
        for (; temp->next != NULL; temp = temp->next)
            ;

        temp->next = new;
    }

    return *head;
}

/**
 * free_separatorlist - frees a separatorlist
 * @head: head of the linked list.
 * Return: no return.
 */
void free_separatorlist(separatorlist **head)
{
	
if (head != NULL) {
    separatorlist *curr, *temp;

    for (curr = *head; curr != NULL; curr = curr->next) {
        temp = curr;
        free(temp);
    }

    *head = NULL;
}

}

/**
 * addline_node_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *addline_node_end(line_list **head, char *line) {
    line_list *new, *temp;

    new = malloc(sizeof(line_list));
    if (new == NULL)
        return NULL;

    new->line = line;
    new->next = NULL;
    temp = *head;

    if (temp == NULL) {
        *head = new;
    } else {
        for (; temp->next != NULL; temp = temp->next)
            ;

        temp->next = new;
    }

    return *head;
}

/**
 * free_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **head) {
    line_list *temp;
    line_list *curr;

    if (head != NULL) {
        for (curr = *head; curr != NULL; curr = curr->next) {
            temp = curr;
            free(temp);
        }
        *head = NULL;
    }
}


/**
 * list two
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
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
 * free_rvar_list - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

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

