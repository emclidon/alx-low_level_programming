@@ -0,0 +1,37 @@
#include "lists.h"

/**
 * delete_nodeint_at_index - deletes a new node at a given position
 * @head: the list
 * @index: the index to insert
 *
 * Return: 1 if successful and -1 if not
 */
int delete_nodeint_at_index(listint_t **head, unsigned int index)
{
	listint_t *temp = *head, *temp2;
	unsigned int i;

	if (!(*head))
		return (-1);

	if (index == 0)
	{
		*head = (*head)->next;
		free(temp);
		return (1);
	}

	for (i = 0; i < index - 1; i++)
	{
		if (!temp->next)
			return (-1);
		temp = temp->next;
	}
	temp2 = temp->next;
	temp->next = temp->next->next;

	free(temp2);

	return (1);
}
5
0x13-more_singly_linked_lists/7-getnodeint.c
@@ -10,11 +10,14 @@
listint_t *get_nodeint_at_index(listint_t *head, unsigned int index)
{
	listint_t *temp = head;
	int i;
	unsigned int i;

	if (!temp)
		return (NULL);

	if (index == 0)
		return (temp);

	for (i = 0; i < index - 1; i++)
	{
		if (!temp->next)
24
0x13-more_singly_linked_lists/9-insert_nodeint.c
@@ -11,7 +11,7 @@
listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n)
{
	listint_t *temp = *head, *new_node, *temp2;
	int i;
	unsigned int i;

	new_node = malloc(sizeof(listint_t));

@@ -20,6 +20,28 @@ listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n)
	new_node->n = n;
	new_node->next = NULL;

	if (!(*head))
	{
		if (idx == 0)
		{
			*head = new_node;
			return (new_node);
		}
		else
		{
			return (NULL);
		}
	}
	else
	{
		if (idx == 0)
		{
			temp2 = temp->next;
			*head = new_node;
			new_node->next = temp2;
		}
	}

	for (i = 0; i < idx - 1; i++)
	{
		if (!temp->next)
1
0x13-more_singly_linked_lists/lists.h
@@ -30,5 +30,6 @@ int pop_listint(listint_t **head);
listint_t *get_nodeint_at_index(listint_t *head, unsigned int index);
int sum_listint(listint_t *head);
listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n);
int delete_nodeint_at_index(listint_t **head, unsigned int index);

#endif
